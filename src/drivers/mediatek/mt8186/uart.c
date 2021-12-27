// SPDX-License-Identifier: BSD-3-Clause
//
// Copyright(c) 2021 Mediatek
//
// Author: Yuchen Huang <yuchen.huang@mediatek.com>

#include <sof/common.h>
#include <sof/drivers/uart.h>
#include <sof/lib/cpu.h>
#include <sof/lib/io.h>
#include <sof/lib/memory.h>
#include <sof/lib/uuid.h>
#include <sof/list.h>
#include <sof/spinlock.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define INVAL_UART_BASE 	0xFFFFFFFF
static unsigned int uart_base = INVAL_UART_BASE;

#define DIV_ROUND_CLOSEST(x, div)	(((x) + ((div) / 2)) / (div))

static void __uart_baudrate_config(unsigned int addr, unsigned int baudrate, unsigned int uartclk)
{
	int highspeed, quot;
	int sample, sample_count, sample_point;
	int dll, dlh;

	/* set baud rate */
	if (baudrate <= 115200) {
		highspeed = 0;
		quot = DIV_ROUND_CLOSEST(uartclk, 16 * baudrate);
	} else if (baudrate <= 576000) {
		highspeed = 2;
		if ((baudrate == 500000) || (baudrate == 576000))
			baudrate = 460800;
		quot = DIV_ROUND_UP(uartclk, 4 * baudrate);
	} else {
		highspeed = 3;
		quot = DIV_ROUND_UP(uartclk, 256 * baudrate);
	}

	sample = DIV_ROUND_CLOSEST(uartclk, quot * baudrate);
	sample_count = sample - 1;
	sample_point = (sample - 2) >> 1;
	dll = quot & 0xff;
	dlh = quot >> 8;

#if UART_NEW_FEATURE_SWITCH_OPTION
	io_reg_write(UART_FEATURE_SEL(addr), UART_FEATURE_SEL_NEW_MAP|UART_FEATURE_SEL_NO_DOWNLOAD);
#else
	io_reg_write(UART_FEATURE_SEL(addr), UART_FEATURE_SEL_NO_DOWNLOAD); //Disable download mode
#endif
	io_reg_write(UART_HIGHSPEED(addr), highspeed);

	io_reg_write(UART_LCR(addr), 0xbf);
	io_reg_write(UART_IIR(addr), 0x40);

	io_reg_write(UART_LCR(addr), UART_LCR_DLAB); // set LCR to DLAB to set DLL,DLH
	io_reg_write(UART_DLL(addr), dll);
	io_reg_write(UART_DLH(addr), dlh);
	io_reg_write(UART_LCR(addr), UART_WLS_8); //word length 8
	io_reg_write(UART_SAMPLE_COUNT(addr), sample_count);
	io_reg_write(UART_SAMPLE_POINT(addr), sample_point);

	io_reg_write(UART_FCR(addr), UART_FCR_FIFOINI); //Enable FIFO

	/* no_print("dump baudrate config, baud:%d, HIGHSPEED:%d, DLL:%d, DLH:%d, sample_count:%d, sample_point:%d, fcr:%d\n",
		baudrate, highspeed, dll, dlh, sample_count, sample_point, io_reg_read(UART_FCR_RD(addr))); */
}

void InitDebugSerial(void)
{
	unsigned int uart_clock = UART_CLOCK_RATE;
	unsigned int baudrate = UART_CONSOLE_BAUD_RATE;

	uart_base = UART_CONSOLE_PORT_ADDR;

	__uart_baudrate_config(uart_base, baudrate, uart_clock);
}

void WriteDebugByte(unsigned char ch)
{
	unsigned int LSR;

	if (uart_base == INVAL_UART_BASE) {
		return;
	}

	while (1) {
		LSR = io_reg_read(UART_LSR(uart_base));
		if ((LSR & UART_LSR_TX_READY) == UART_LSR_TX_READY) {
			io_reg_write(UART_THR(uart_base), ch);
			break;
		}
	}
}

int ReadDebugByte(void)
{
	unsigned int ch;
	unsigned int LSR;

	if (uart_base == INVAL_UART_BASE) {
		return DEBUG_SERIAL_READ_NODATA;
	}

	LSR = io_reg_read(UART_LSR(uart_base));
	if (LSR & UART_LSR_DR) {
		ch = (unsigned int)io_reg_read(UART_RBR(uart_base));
	} else {
		ch = DEBUG_SERIAL_READ_NODATA;
	}

	return (int)ch;
}

