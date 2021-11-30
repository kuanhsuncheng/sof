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

#define PLATFORM_IRQ_HW_NUM XCHAL_NUM_INTERRUPTS
#define PLATFORM_IRQ_FIRST_CHILD PLATFORM_IRQ_HW_NUM
#define PLATFORM_IRQ_CHILDREN 32

/* IRQ numbers - wrt Tensilica DSP */
#if CONFIG_XT_INTERRUPT_LEVEL_1
#define IRQ_NUM_TIMER0 0
#define IRQ_NUM_SOFTWARE0 21
#define IRQ_NUM_EXT_LEVEL01 1
#define IRQ_NUM_EXT_LEVEL23 23
#define IRQ_EXT_DOMAIN0 IRQ_NUM_EXT_LEVEL01
#define IRQ_EXT_DOMAIN1 IRQ_NUM_EXT_LEVEL23
#define IRQ_EXT_DOMAIN0_OFFSET	4
#define IRQ_MASK_SOFTWARE0 BIT(IRQ_NUM_SOFTWARE0)
#define IRQ_MASK_TIMER0 BIT(IRQ_NUM_TIMER0)
#define IRQ_MASK_GROUP16 BIT(IRQ_NUM_GROUP16)
#endif

#if CONFIG_XT_INTERRUPT_LEVEL_2
#define IRQ_NUM_SOFTWARE1 22 /* level 2 */
#define IRQ_NUM_EXT_LEVEL09 9 /* Level 2 */
#define IRQ_NUM_EXT_LEVEL24 24 /* Level 2 */
#define IRQ_MASK_SOFTWARE1 BIT(IRQ_NUM_SOFTWARE1)
#define IRQ_MASK_GROUP17 BIT(IRQ_NUM_GROUP17)
#endif

/* platform irq information */
#define IRQ_TYPE_EDGE_RISING 0x00000001
#define IRQ_TYPE_EDGE_FALLING 0x00000002
#define IRQ_TYPE_LEVEL_HIGH 0x00000004
#define IRQ_TYPE_LEVEL_LOW 0x00000008

/* int level */
#define IRQ_INVALID 0xff
#define IRQ_MASK 0xff
#define IRQ_EXT_DOMAIN1_MASK 0x3FFFFFF0
#define IRQ_EXT_DOMAIN2_MASK 0xFFFF
#define GET_INTERRUPT_ID(n) ((n) & IRQ_MASK)
#define LEVEL_SHFIT 8
#define LEVEL_MASK 0xff
#define INT_LEVEL(n) ((n) << LEVEL_SHFIT)
#define GET_INTLEVEL(irq) (((irq) >> LEVEL_SHFIT) & LEVEL_MASK)
#define IRQ_LEVEL0 0
#define IRQ_LEVEL1 1

/*
 *		interrupt table
 *
 */
#define MTK_DSP_INT_UART                    0
#define MTK_DSP_INT_SPM                     1
#define MTK_DSP_INT_MAILBOX                 2
#define MTK_DSP_INT_TIMER0                  3
#define MTK_DSP_INT_TIMER1                  4
#define MTK_DSP_INT_AFE                     5
#define MTK_DSP_INT_SW1                     6
#define MTK_DSP_INT_SW2                     7
#define MTK_DSP_INT_CONNSYS1                8
#define MTK_DSP_INT_CONNSYS2                9
#define MTK_DSP_INT_CONNSYS3                10
#define MTK_DSP_INT_NNA0                    11
#define MTK_DSP_INT_NNA1                    12
#define MTK_DSP_INT_OSTIMER64               13
#define MTK_DSP_INT_DMA                     14
#define MTK_DSP_INT_WDT                     16
#define MTK_DSP_INT_MDLA                    17
#define MTK_DSP_INT_OSTIMER32               18
#define MTK_DSP_INT_NNA2                    19
#define MTK_DSP_INT_SCP                     20
#define MTK_DSP_INT_LATENCT_MON             21
#define MTK_DSP_INT_BUS_TRACKER             22
#define MTK_DSP_INT_WAKEUP_SRC              23
#define MTK_DSP_INT_INFRA_HANG              24
#define MTK_DSP_INT_NMI                     25
/* 26 ~ 31 is Cadence internal Module */
#define MTK_MAX_IRQ_NUM                     26

#define MAX_IRQ_NUM 64
#define DOMAIN1_MAX_IRQ_NUM 32
#define MAX_INT_LEVEL 24
#define AUDIO_IRQn LX_AFE_IRQ_B

#define	MTK_DSP_IRQ_EN  MTK_ADSP_IRQ_EN_C0
#define	MTK_DSP_IRQ_MASK    MTK_ADSP_IRQ_MASK

#endif /* __PLATFORM_DRIVERS_INTERRUPT_H__ */

#else

#error "This file shouldn't be included from outside of sof/drivers/interrupt.h"

#endif /* __SOF_DRIVERS_INTERRUPT_H__ */
