// SPDX-License-Identifier: BSD-3-Clause
//
// Copyright(c) 2021 Mediatek
//
// Author: YC Hung <yc.hung@mediatek.com>
//         Allen-KH Cheng <allen-kh.cheng@mediatek.com>

#ifndef MT_REG_BASE_H
#define MT_REG_BASE_H

#define MTK_REG_TOPCKGEN_BASE               0x10000000
#define MTK_REG_TOPCKGEN_SIZE               0x1000
#define MTK_REG_APMIXDSYS_BASE              0x1000C000
#define MTK_REG_APMIXDSYS_SIZE              0x1000

#define MTK_DSP_REG_BASE                    0x10680000 /* DSP Register base */
#define MTK_DSP_CFGREG_BASE                 0x10680000
#define MTK_DSP_CFGREG_SIZE                 0x1000
#define MTK_DSP_TIMER_BASE                  0x1068E000
#define MTK_DSP_TIMER_SIZE                  0x1000
#define MTK_DSP_UART0_BASE                  0x10684000
#define MTK_DSP_UART0_SIZE                  0x1000
#define MTK_DSP_CKCTRL_BASE                 0x10681000
#define MTK_DSP_CKCTRL_SIZE                 0x1000
#define MTK_DSP_OS_TIMER_BASE               0x10683000
#define MTK_DSP_OS_TIMER_SIZE               0x1000
#define MTK_DSP_BUS_BASE                    0x1068F000
#define MTK_DSP_BUS_SIZE                    0x1000
#define MTK_DSP_AFE_BASE                    0x11210000
#define MTK_DSP_AFE_SIZE                    0xF000 /* register 8k, compacted sram 52k */

#define MTK_ADSP_CFGREG_SW_RSTN       (MTK_DSP_REG_BASE + 0x0000)
#define MTK_ADSP_HIFI_IO_CONFIG       (MTK_DSP_REG_BASE + 0x000c)
#define MTK_ADSP_HIFI_INTR_Core0      (MTK_DSP_REG_BASE + 0x0010)
#define MTK_ADSP_SW_INT_SET           (MTK_DSP_REG_BASE + 0x0018)
#define MTK_ADSP_SW_INT_CLR           (MTK_DSP_REG_BASE + 0x001c)
#define MTK_ADSP_SW_INT_32A           (MTK_DSP_REG_BASE + 0x0020)
#define MTK_ADSP_IRQ_MASK             (MTK_DSP_REG_BASE + 0x0030)
#define MTK_ADSP_GENERAL_IRQ_SET      (MTK_DSP_REG_BASE + 0x0034)
#define MTK_ADSP_GENERAL_IRQ_CLR      (MTK_DSP_REG_BASE + 0x0038)
#define MTK_ADSP_DVFSRC_STATE         (MTK_DSP_REG_BASE + 0x003c)
#define MTK_ADSP_DVFSRC_REQ           (MTK_DSP_REG_BASE + 0x0040)
#define MTK_ADSP_DDREN_REQ_0          (MTK_DSP_REG_BASE + 0x0044)
#define MTK_ADSP_SPM_ACK              (MTK_DSP_REG_BASE + 0x004c)
#define MTK_ADSP_IRQ_EN_C0            (MTK_DSP_REG_BASE + 0x0050)
#define MTK_ADSP_IRQ_POL_FIX          (MTK_DSP_REG_BASE + 0x0054)
#define MTK_ADSP_SPM_WAKEUPSRC_CORE0  (MTK_DSP_REG_BASE + 0x005c)
#define MTK_ADSP_SEMAPHORE            (MTK_DSP_REG_BASE + 0x0064)
#define MTK_ADSP_DBG_SEL              (MTK_DSP_REG_BASE + 0x0074)
#define MTK_ADSP_DBG_INFO             (MTK_DSP_REG_BASE + 0x0078)
#define MTK_ADSP_WDT_CON_C0           (MTK_DSP_REG_BASE + 0x007c)
#define MTK_ADSP_WDT_INIT_VALUE_C0    (MTK_DSP_REG_BASE + 0x0080)
#define MTK_ADSP_WDT_CNT_C0           (MTK_DSP_REG_BASE + 0x0084)
#define MTK_ADSP_WAKEUPSRC_MASK_C0    (MTK_DSP_REG_BASE + 0x00a0)
#define MTK_ADSP_WAKEUPSRC_IRQ_C0     (MTK_DSP_REG_BASE + 0x00a4)
#define MTK_ADSP2SPM_MBOX             (MTK_DSP_REG_BASE + 0x00bc)
#define MTK_SPM2ADSP_MBOX             (MTK_DSP_REG_BASE + 0x00c0)
#define MTK_GPR_RW_REG0               (MTK_DSP_REG_BASE + 0x0440)
#define MTK_GPR_RW_REG1               (MTK_DSP_REG_BASE + 0x0444)
#define MTK_GPR_RW_REG2               (MTK_DSP_REG_BASE + 0x0448)
#define MTK_GPR_RW_REG3               (MTK_DSP_REG_BASE + 0x044c)
#define MTK_GPR_RW_REG4               (MTK_DSP_REG_BASE + 0x0450)
#define MTK_GPR_RW_REG5               (MTK_DSP_REG_BASE + 0x0454)
#define MTK_GPR_RW_REG6               (MTK_DSP_REG_BASE + 0x0458)
#define MTK_GPR_RW_REG7               (MTK_DSP_REG_BASE + 0x045c)
#define MTK_GPR_RW_REG8               (MTK_DSP_REG_BASE + 0x0460)
#define MTK_GPR_RW_REG9               (MTK_DSP_REG_BASE + 0x0464)
#define MTK_GPR_RW_REG10              (MTK_DSP_REG_BASE + 0x0468)
#define MTK_GPR_RW_REG11              (MTK_DSP_REG_BASE + 0x046c)
#define MTK_GPR_RW_REG12              (MTK_DSP_REG_BASE + 0x0470)
#define MTK_GPR_RW_REG13              (MTK_DSP_REG_BASE + 0x0474)
#define MTK_GPR_RW_REG14              (MTK_DSP_REG_BASE + 0x0478)
#define MTK_GPR_RW_REG15    (MTK_DSP_REG_BASE + 0x047c)
#define MTK_GPR_RW_REG16    (MTK_DSP_REG_BASE + 0x0480)
#define MTK_GPR_RW_REG17            (MTK_DSP_REG_BASE + 0x0484)
#define MTK_GPR_RW_REG18              (MTK_DSP_REG_BASE + 0x0488)
#define MTK_GPR_RW_REG19              (MTK_DSP_REG_BASE + 0x048c)
#define MTK_GPR_RW_REG20              (MTK_DSP_REG_BASE + 0x0490)
#define MTK_GPR_RW_REG21              (MTK_DSP_REG_BASE + 0x0494)
#define MTK_GPR_RW_REG22              (MTK_DSP_REG_BASE + 0x0498)
#define MTK_GPR_RW_REG23              (MTK_DSP_REG_BASE + 0x049c)
#define MTK_GPR_RW_REG24              (MTK_DSP_REG_BASE + 0x04a0)
#define MTK_GPR_RW_REG25              (MTK_DSP_REG_BASE + 0x04a4)
#define MTK_GPR_RW_REG26              (MTK_DSP_REG_BASE + 0x04a8)
#define MTK_GPR_RW_REG27              (MTK_DSP_REG_BASE + 0x04ac)
#define MTK_GPR_RW_REG28              (MTK_DSP_REG_BASE + 0x04b0)  /* use for tickless status */
#define MTK_GPR_RW_REG29              (MTK_DSP_REG_BASE + 0x04b4)
#define ADSP_IRQ_OUT_MASK         (MTK_DSP_REG_BASE + 0x0500)

/* Need to remove*/
#define MTK_DSP_RG_INT_POL_CTL0       MTK_GPR_RW_REG29
#define MTK_DSP_RG_INT_EN_CTL0        MTK_GPR_RW_REG29
#define MTK_DSP_RG_INT_LV_CTL0        MTK_GPR_RW_REG29
#define MTK_DSP_RG_INT_STATUS0        MTK_GPR_RW_REG29
#define MTK_DSP_RG_INT2CIRQ           MTK_GPR_RW_REG29
#define MTK_DSP_RG_INT_POL_CTL0       MTK_GPR_RW_REG29
#define MTK_DSP_RG_INT_EN_CTL0        MTK_GPR_RW_REG29
#define MTK_DSP_RG_INT_LV_CTL0        MTK_GPR_RW_REG29
#define MTK_DSP_RG_INT_STATUS0        MTK_GPR_RW_REG29

/* Redefinition for using Special registers */
#define MTK_TICKLESS_STATUS_REG       GPR_RW_REG28

/*MBOX registers*/
#define MTK_DSP_MBOX_REG_BASE(x) (0x10686000 + (0x1000 * (x)))
#define MTK_DSP_MBOX_REG_SIZE (0x5000)
#define MTK_DSP_MBOX_IN_CMD(x) (MTK_DSP_MBOX_REG_BASE(x) + 0x0)
#define MTK_DSP_MBOX_IN_CMD_CLR(x) (MTK_DSP_MBOX_REG_BASE(x) + 0x04)
#define MTK_DSP_MBOX_OUT_CMD(x) (MTK_DSP_MBOX_REG_BASE(x) + 0x1c)
#define MTK_DSP_MBOX_OUT_CMD_CLR(x) (MTK_DSP_MBOX_REG_BASE(x) + 0x20)
#define MTK_DSP_MBOX_OUT_CMD_MSG0(x) (MTK_DSP_MBOX_REG_BASE(x) + 0x24)
#define MTK_DSP_MBOX_OUT_CMD_MSG1(x) (MTK_DSP_MBOX_REG_BASE(x) + 0x28)
#define MTK_DSP_MBOX_OUT_CMD_MSG2(x) (MTK_DSP_MBOX_REG_BASE(x) + 0x2c)
#define MTK_DSP_MBOX_OUT_CMD_MSG3(x) (MTK_DSP_MBOX_REG_BASE(x) + 0x30)
#define MTK_DSP_MBOX_OUT_CMD_MSG4(x) (MTK_DSP_MBOX_REG_BASE(x) + 0x34)

#endif /* MT_REG_BASE_H */
