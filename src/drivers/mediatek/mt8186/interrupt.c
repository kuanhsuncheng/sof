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


#include <sof/drivers/uart.h>
#include <platform/printf.h>

/* fa00558c-d653-4851-a03a-b21f125a9524 */
DECLARE_SOF_UUID("irq-mt8186", irq_mt8186_uuid, 0xfa00558c, 0xd653, 0x4851,
		 0xa0, 0x3a, 0xb2, 0x1f, 0x12, 0x5a, 0x95, 0x24);

DECLARE_TR_CTX(int_tr, SOF_UUID(irq_mt8186_uuid), LOG_LEVEL_INFO);


static void mtk_irq_irq_init(void)
{
	// hw disable all irq
	io_reg_update_bits(MTK_DSP_IRQ_EN, 0xffffffff, 0xffffffff);
	 // hw unmask irq
	io_reg_update_bits(MTK_DSP_IRQ_MASK, 0x3ff, 0x3ff);
}

static void mtk_irq_mask(struct irq_desc *desc, uint32_t irq, unsigned int core)
{
	if (!desc) {
		io_reg_update_bits(MTK_DSP_IRQ_EN, BIT(irq), 0x0);
	} else {
		switch (desc->irq) {
		case MTK_DSP_INT_MAILBOX:
			io_reg_update_bits(MTK_DSP_IRQ_EN, BIT(desc->irq), 0x0);
			break;
		default:
			tr_err(&int_tr, "Invalid interrupt %d", desc->irq);
			return;
		}
	}
}

static void mtk_irq_unmask(struct irq_desc *desc, uint32_t irq, unsigned int core)
{
	if (!desc) {
		io_reg_update_bits(MTK_DSP_IRQ_EN, BIT(irq), BIT(irq));
	} else {
		switch (desc->irq) {
		case MTK_DSP_INT_MAILBOX:
			io_reg_update_bits(MTK_DSP_IRQ_EN, BIT(desc->irq), BIT(desc->irq));
			break;
		default:
			tr_err(&int_tr, "Invalid interrupt %d", desc->irq);
			return;
		}
	}
}

static uint64_t mtk_get_irq_interrupts(uint32_t irq)
{
	uint32_t irq_status = 0;

	DBG("Allen trace 0x%x \n",io_reg_read(MTK_DSP_IRQ_STATUS));
	if(irq == MTK_DSP_INT_MAILBOX && (io_reg_read(MTK_DSP_IRQ_STATUS) & 0x4)) {
		//B070 ADSP_MBOX_IRQ_IN[0:4]
		irq_status = io_reg_read(MTK_MBOX_IRQ_IN) & MTK_DSP_MBOX_MASK;
		DBG("Allen trace  irq_status  0x%x \n",irq_status);
	}

	return irq_status;
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
	DBG("Allen trace status %d cascade 0x%x \n",(unsigned int)status,cascade);
	while (status) {
		bit = get_first_irq(status);
		handled = false;
		status &= ~(1ull << bit);
		DBG("Allen trace bit %d status %d &cascade->child 0x%x cascade 0x%x \n",bit,(unsigned int)status,&cascade->child,cascade);
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
			io_reg_update_bits(MTK_DSP_IRQ_EN, BIT(bit), 0x0);
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
	DBG("Allen trace status %u cascade 0x%x\n",(unsigned int)status,cascade);
	if (status) {
		DBG("Allen trace status %u cascade 0x%x\n",(unsigned int)status,cascade);

		/* Handle current interrupts */
		mtk_handle_irq(cascade, line_index, status);
	} else
		tr_err(&int_tr, "invalid interrupt status");
}

#define DEFINE_IRQ_HANDLER(n) \
	static void irqhandler_##n(void *arg) \
	{ \
		irq_handler(arg, n); \
	}

DEFINE_IRQ_HANDLER(2)

static const char mtk_irq_mailbox[] = "mtk_irq_mailbox";

static const struct irq_cascade_ops irq_ops = {
	.mask = mtk_irq_mask,
	.unmask = mtk_irq_unmask,
};

static const struct irq_cascade_tmpl dsp_irq[] = {
	{
		.name = mtk_irq_mailbox,
		.irq = MTK_DSP_INT_MAILBOX,
		.handler = irqhandler_2,
		.ops = &irq_ops,
		.global_mask = false,
	},
};

uint32_t mtk_get_irq_domain_id(int32_t irq)
{
	uint32_t in_irq = GET_INTERRUPT_ID(irq);
	uint32_t res;

	if (in_irq >= MTK_MAX_IRQ_NUM)
		in_irq -= MTK_MAX_IRQ_NUM;

	res = interrupt_get_irq(in_irq, dsp_irq[0].name);
	return res;
}

void platform_interrupt_init(void)
{
	int i;
	mtk_irq_irq_init();

	for (i = 0; i < ARRAY_SIZE(dsp_irq); i++)
		interrupt_cascade_register(dsp_irq + i);
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
