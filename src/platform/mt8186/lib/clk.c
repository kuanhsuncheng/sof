// SPDX-License-Identifier: BSD-3-Clause
//
// Copyright(c) 2021 Mediatek
//
// Author: Allen-KH Cheng <allen-kh.cheng@mediatek.com>

#include <sof/common.h>
#include <sof/lib/clk.h>
#include <sof/lib/cpu.h>
#include <sof/lib/memory.h>
#include <sof/lib/notifier.h>
#include <sof/sof.h>
#include <sof/spinlock.h>

#include <sof/drivers/uart.h>
#include <platform/printf.h>

/*Use external Ostimer*/
const struct freq_table platform_cpu_freq[] = {
	{ 800000000, 26000},
	{ 800000000, 26000},
	{ 800000000, 26000},
	{ 800000000, 26000},
	{ 800000000, 26000},
};

STATIC_ASSERT(ARRAY_SIZE(platform_cpu_freq) == NUM_CPU_FREQ,
	      invalid_number_of_cpu_frequencies);

static SHARED_DATA struct clock_info platform_clocks_info[NUM_CLOCKS];

static int clock_platform_set_dsp_freq(int clock, int freq_idx)
{
	DBG("Allen trace clock %d freq_idx %d \n",clock,freq_idx);
	return 0;
}

void platform_clock_init(struct sof *sof)
{
	int i;

	sof->clocks = platform_clocks_info;

	for (i = 0; i < CONFIG_CORE_COUNT; i++) {
		sof->clocks[i] = (struct clock_info){
			.freqs_num = NUM_CPU_FREQ,
			.freqs = platform_cpu_freq,
			.default_freq_idx = CPU_DEFAULT_IDX,
			.current_freq_idx = CPU_DEFAULT_IDX,
			.notification_id = NOTIFIER_ID_CPU_FREQ,
			.notification_mask = NOTIFIER_TARGET_CORE_MASK(i),
			.set_freq = clock_platform_set_dsp_freq,
		};

		spinlock_init(&sof->clocks[i].lock);
	}
}
