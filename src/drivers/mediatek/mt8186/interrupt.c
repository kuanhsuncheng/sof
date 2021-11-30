// SPDX-License-Identifier: BSD-3-Clause
//
// Copyright(c) 2021 Mediatek
//
// Author: Allen-KH Cheng <allen-kh.cheng@mediatek.com>

#include <sof/common.h>
#include <sof/bit.h>
#include <sof/drivers/interrupt.h>
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

/* fa00558c-d653-4851-a03a-b21f125a9524 */
DECLARE_SOF_UUID("irq-mt8186", irq_mt8186_uuid, 0xfa00558c, 0xd653, 0x4851,
		 0xa0, 0x3a, 0xb2, 0x1f, 0x12, 0x5a, 0x95, 0x24);

DECLARE_TR_CTX(int_tr, SOF_UUID(irq_mt8186_uuid), LOG_LEVEL_INFO);


/* TO-DO*/

static void irq_mask_all(void)
{
	io_reg_update_bits(MTK_DSP_IRQ_EN, 0xffffffff, 0x0);
	io_reg_update_bits(MTK_DSP_IRQ_MASK, 0x3ff, 0x0);
}

static void mtk_irq_mask(struct irq_desc *desc, uint32_t irq, unsigned int core)
{
	// int32_t in_irq, level;

	// if (!desc) {
	// 	level = GET_INTLEVEL(irq);
	// 	in_irq = GET_INTERRUPT_ID(irq);
	// 	if (level > MAX_IRQ_NUM) {
	// 		tr_err(&int_tr, "Invalid interrupt %d", irq);
	// 		return;
	// 	}

	// 	io_reg_update_bits(RG_DSP_IRQ_EN, BIT(in_irq), 0x0);
	// } else {
	// 	switch (desc->irq) {
	// 	case IRQ_EXT_DOMAIN0:
	// 		io_reg_update_bits(RG_DSP_IRQ_EN, BIT(irq + IRQ_EXT_DOMAIN0_OFFSET), 0x0);
	// 		break;
	// 	case IRQ_EXT_DOMAIN1:
	// 		io_reg_update_bits(DSP_IRQ_EN, BIT(irq), 0x0);
	// 		break;
	// 	default:
	// 		tr_err(&int_tr, "Invalid interrupt %d", desc->irq);
	// 		return;
	// 	}
	// }
}

static void mtk_irq_unmask(struct irq_desc *desc, uint32_t irq, unsigned int core)
{
	// int32_t in_irq, level;

	// if (!desc) {
	// 	level = GET_INTLEVEL(irq);
	// 	in_irq = GET_INTERRUPT_ID(irq);
	// 	if (level > MAX_IRQ_NUM) {
	// 		tr_err(&int_tr, "Invalid interrupt %d", irq);
	// 		return;
	// 	}

	// 	io_reg_update_bits(RG_DSP_IRQ_EN, BIT(in_irq), BIT(in_irq));
	// } else {
	// 	switch (desc->irq) {
	// 	case IRQ_EXT_DOMAIN0:
	// 		io_reg_update_bits(RG_DSP_IRQ_EN, BIT(irq + IRQ_EXT_DOMAIN0_OFFSET),
	// 				   BIT(irq + IRQ_EXT_DOMAIN0_OFFSET));
	// 		break;
	// 	case IRQ_EXT_DOMAIN1:
	// 		io_reg_update_bits(DSP_IRQ_EN, BIT(irq), BIT(irq));
	// 		break;
	// 	default:
	// 		tr_err(&int_tr, "Invalid interrupt %d", desc->irq);
	// 		return;
	// 	}
	// }
}

static uint64_t mtk_get_irq_interrupts(uint32_t irq)
{
	// uint32_t irq_status;

	// switch (irq) {
	// case IRQ_NUM_EXT_LEVEL23:
	// 	irq_status = io_reg_read(DSP_IRQ_STATUS);
	// 	irq_status &= IRQ_EXT_DOMAIN2_MASK;
	// 	break;
	// default:
	// 	irq_status = io_reg_read(RG_DSP_IRQ_STATUS);
	// 	irq_status &= IRQ_EXT_DOMAIN1_MASK;
	// 	break;
	// }
	// return irq_status;
	return 0;
}

static int get_first_irq(uint64_t ints)
{
	return ffs(ints) - 1;
}

static inline void mtk_handle_irq(struct irq_cascade_desc *cascade,
				  uint32_t line_index, uint64_t status)
{
	int core = cpu_get_id();
	struct list_item *clist;
	struct irq_desc *child = NULL;
	int bit;
	bool handled;

	while (status) {
		bit = get_first_irq(status);
		handled = false;
		status &= ~(1ull << bit);

		spin_lock(&cascade->lock);

		list_for_item(clist, &cascade->child[bit].list) {
			child = container_of(clist, struct irq_desc, irq_list);

			if (child->handler && (child->cpu_mask & 1 << core)) {
				child->handler(child->handler_arg);
				handled = true;
			}
		}

		spin_unlock(&cascade->lock);

		if (!handled) {
			tr_err(&int_tr, "irq_handler(): not handled, bit %d", bit);
		}
	}
}

static inline void irq_handler(void *data, uint32_t line_index)
{
	struct irq_desc *parent = data;
	struct irq_cascade_desc *cascade =
		container_of(parent, struct irq_cascade_desc, desc);
	uint64_t status;

	status = mtk_get_irq_interrupts(line_index);

	if (status)
		/* Handle current interrupts */
		mtk_handle_irq(cascade, line_index, status);
	else
		tr_err(&int_tr, "invalid interrupt status");
}


static const struct irq_cascade_ops irq_ops = {
	.mask = mtk_irq_mask,
	.unmask = mtk_irq_unmask,
};

void platform_interrupt_init(void)
{
	irq_mask_all();
}

void platform_interrupt_set(uint32_t irq)
{
	if (interrupt_is_dsp_direct(irq))
		arch_interrupt_set(irq);
}

void platform_interrupt_clear(uint32_t irq, uint32_t mask)
{
	if (interrupt_is_dsp_direct(irq))
		arch_interrupt_clear(irq);
}

uint32_t platform_interrupt_get_enabled(void)
{
	return 0;
}

void interrupt_mask(uint32_t irq, unsigned int cpu)
{
	struct irq_cascade_desc *cascade = interrupt_get_parent(irq);

	if (cascade && cascade->ops->mask)
		cascade->ops->mask(&cascade->desc, irq - cascade->irq_base,
				   cpu);
	else
		mtk_irq_mask(NULL, irq, 0);
}

void interrupt_unmask(uint32_t irq, unsigned int cpu)
{
	struct irq_cascade_desc *cascade = interrupt_get_parent(irq);

	if (cascade && cascade->ops->unmask)
		cascade->ops->unmask(&cascade->desc, irq - cascade->irq_base,
				     cpu);
	else
		mtk_irq_unmask(NULL, irq, 0);
}
