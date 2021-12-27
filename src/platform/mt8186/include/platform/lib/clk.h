// SPDX-License-Identifier: BSD-3-Clause
//
// Copyright(c) 2021 Mediatek
//
// Author: YC Hung <yc.hung@mediatek.com>

#ifdef __SOF_LIB_CLK_H__

#ifndef __PLATFORM_LIB_CLK_H__
#define __PLATFORM_LIB_CLK_H__

#include <stdint.h>

struct sof;

#define CLK_CPU(x) (x)

#define CPU_DEFAULT_IDX 4

#define CLK_DEFAULT_CPU_HZ 800000000
#define CLK_MAX_CPU_HZ 800000000

#define NUM_CLOCKS 1

#define NUM_CPU_FREQ 5

#define CLK_DSP_SEL_26M               0
#define CLK_DSP_SEL_ULPOSC_D_10       1
#define CLK_DSP_SEL_DSPPLL            2
#define CLK_DSP_SEL_DSPPLL_D_2        3
#define CLK_DSP_SEL_DSPPLL_D_4        4
#define CLK_DSP_SEL_DSPPLL_D_8        5

#define CLK_DSP_BUS_SEL_26M               0
#define CLK_DSP_BUS_SEL_ULPOSC_D_2        1
#define CLK_DSP_BUS_SEL_MAINPLL_D_5       2
#define CLK_DSP_BUS_SEL_MAINPLL_D_2_D_2   3
#define CLK_DSP_BUS_SEL_MAINPLL_D_3       4
#define CLK_DSP_BUS_SEL_RESERVE           5
#define CLK_DSP_BUS_SEL_UNIVPLL_D_3       6

#define ADSP_CLK_BUS_SEL                  (0x1068F140)
#define ADSP_CLK_BUS_UPDATE               (0x106804C0)

#define ADSP_CLK_BUS_SEL_EMI              0
#define ADSP_CLK_BUS_SEL_LOCAL            1

enum mux_id_t {
    MUX_CLK_DSP_SEL = 0,
    MUX_CLK_DSP_BUS_SEL,
    MUX_CLK_DSP_BUS_DRAM_SEL,
    HIFI5DSP_MUX_NUM,
};

/* List resource from low to high request */
/* 0 is the lowest request */
enum DSP_HW_DSP_CLK {
    DSP_CLK_26M = 0,
    DSP_CLK_PLL_300M_D_8,
    DSP_CLK_PLL_300M_D_4,
    DSP_CLK_PLL_300M_D_2,
    DSP_CLK_PLL_300M,

    DSP_CLK_PLL_400M_D_8,
    DSP_CLK_PLL_400M_D_4,
    DSP_CLK_PLL_400M_D_2,
    DSP_CLK_PLL_400M,

    DSP_CLK_PLL_800M_D_8,
    DSP_CLK_PLL_800M_D_4,
    DSP_CLK_PLL_800M_D_2,
    DSP_CLK_PLL_800M,
};

/* List resource from low to high request */
/* 0 is the lowest request */
enum DSP_SYS_HW_REQ {
    DSP_SYS_HW_NONE = 0,
    DSP_SYS_HW_26M,
    DSP_SYS_HW_INFRA,
    DSP_SYS_HW_PLL,
    DSP_SYS_HW_DRAM,
    DSP_SYS_HW_REQ_NUM,
};

/* List resource from low to high request */
/* 0 is the lowest request */
enum DSP_SYS_DVFSRC_REQ {
    DSP_SYS_DVFSRC_REQ_V0P60V = 0,
    DSP_SYS_DVFSRC_REQ_V0P65V,
    DSP_SYS_DVFSRC_REQ_V0P70V,
    DSP_SYS_DVFSRC_REQ_V0P80V,
};

void platform_clock_init(struct sof *sof);

#endif /* __PLATFORM_LIB_CLK_H__ */

#else

#error "This file shouldn't be included from outside of sof/lib/clk.h"

#endif /* __SOF_LIB_CLK_H__ */
