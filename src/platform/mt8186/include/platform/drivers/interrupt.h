// SPDX-License-Identifier: BSD-3-Clause
//
// Copyright(c) 2021 Mediatek
//
// Author: Hailong Fan <hailong.fan@mediatek.com>
//         Allen-KH Cheng <allen-kh.cheng@mediatek.com>

#ifdef __SOF_DRIVERS_INTERRUPT_H__

#ifndef __PLATFORM_DRIVERS_INTERRUPT_H__
#define __PLATFORM_DRIVERS_INTERRUPT_H__

#include <stdint.h>
#include <platform/drivers/mt_reg_base.h>

#define PLATFORM_IRQ_HW_NUM		XCHAL_NUM_INTERRUPTS
#define PLATFORM_IRQ_FIRST_CHILD	PLATFORM_IRQ_HW_NUM
#define PLATFORM_IRQ_CHILDREN		32

/* platform irq information */
/* #define IRQ_TYPE_EDGE_RISING		0x00000001 */
/* #define IRQ_TYPE_EDGE_FALLING		0x00000002 */
/* #define IRQ_TYPE_LEVEL_HIGH		0x00000004 */
/* #define IRQ_TYPE_LEVEL_LOW		0x00000008 */

/* MTK_ADSP_IRQ_MASK */
#define MTK_DSP_OUT_IRQ_MASK		0x3FF

/* int level */
// #define IRQ_INVALID			0xFF
// #define IRQ_MASK			0xFF
/* #define IRQ_EXT_DOMAIN1_MASK		0x3FFFFFF0 */
/* #define IRQ_EXT_DOMAIN2_MASK		0xFFFF */
// #define GET_INTERRUPT_ID(n)		((n) & IRQ_MASK)
// #define LEVEL_SHFIT			8
// #define LEVEL_MASK			0xFF
// #define INT_LEVEL(n)			((n) << LEVEL_SHFIT)
// #define GET_INTLEVEL(irq)		(((irq) >> LEVEL_SHFIT) & LEVEL_MASK)
// #define IRQ_LEVEL0			0
// #define IRQ_LEVEL1			1

/* interrupt table */
#define MTK_DSP_IRQ_UART		0
#define MTK_DSP_IRQ_SPM			1
#define MTK_DSP_IRQ_MAILBOX		2
#define MTK_DSP_IRQ_DSP_TIMER0		3
#define MTK_DSP_IRQ_DSP_TIMER1		4
#define MTK_DSP_IRQ_CORE0		5
#define MTK_DSP_IRQ_RSV0		6
#define MTK_DSP_IRQ_RSV1		7
#define MTK_DSP_IRQ_CONNSYS1		8
#define MTK_DSP_IRQ_CONNSYS2		9
#define MTK_DSP_IRQ_CONNSYS3		10
#define MTK_DSP_IRQ_NNA0		11
#define MTK_DSP_IRQ_NNA1		12
#define MTK_DSP_IRQ_OSTIMER64		13
#define MTK_DSP_IRQ_DMA			14
#define MTK_DSP_IRQ_WDT			16
#define MTK_DSP_IRQ_MDLA		17
#define MTK_DSP_IRQ_OSTIMER32		18
#define MTK_DSP_IRQ_NNA2		19
#define MTK_DSP_IRQ_SCP			20
#define MTK_DSP_IRQ_LATENCT_MON		21
#define MTK_DSP_IRQ_BUS_TRACKER		22
#define MTK_DSP_IRQ_WAKEUP_SRC		23
#define MTK_DSP_IRQ_INFRA_HANG		24
#define MTK_DSP_IRQ_NMI			25
#define MTK_DSP_IRQ_TIMER0		26
#define MTK_DSP_IRQ_TIMER1		27
#define MTK_DSP_IRQ_TIMER2		28
#define MTK_DSP_IRQ_PMU			29
#define MTK_DSP_IRQ_WERR		30
#define MTK_DSP_IRQ_SW			31

#define MTK_MAX_IRQ_NUM			32

/* grouped mailbox IRQ */
#define MTK_DSP_IRQ_MBOX0		32
#define MTK_DSP_IRQ_MBOX1		33
#define MTK_DSP_IRQ_MBOX2		34
#define MTK_DSP_IRQ_MBOX3		35
#define MTK_DSP_IRQ_MBOX4		36

#define	MTK_DSP_MBOX_MASK		0xF

uint32_t mtk_irq_group_id(uint32_t irq);

#endif /* __PLATFORM_DRIVERS_INTERRUPT_H__ */

#else

#error "This file shouldn't be included from outside of sof/drivers/interrupt.h"

#endif /* __SOF_DRIVERS_INTERRUPT_H__ */
