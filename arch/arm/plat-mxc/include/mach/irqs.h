/*
 *  Copyright (C) 2004-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ASM_ARCH_MXC_IRQS_H__
#define __ASM_ARCH_MXC_IRQS_H__

/*
 * SoCs with TZIC interrupt controller have 128 IRQs, those with AVIC have 64
 */
#ifdef CONFIG_MXC_TZIC
#define MXC_INTERNAL_IRQS	128
#else
#define MXC_INTERNAL_IRQS	64
#endif

#define MXC_GPIO_IRQ_START	MXC_INTERNAL_IRQS

/* these are ordered by size to support multi-SoC kernels */
#if defined CONFIG_ARCH_MX53
#define MXC_GPIO_IRQS		(32 * 7)
#elif defined CONFIG_ARCH_MX2
#define MXC_GPIO_IRQS		(32 * 6)
#elif defined CONFIG_ARCH_MX1
#define MXC_GPIO_IRQS		(32 * 4)
#elif defined CONFIG_ARCH_MX25
#define MXC_GPIO_IRQS		(32 * 4)
#elif defined CONFIG_ARCH_MX5
#define MXC_GPIO_IRQS		(32 * 4)
#elif defined CONFIG_ARCH_MXC91231
#define MXC_GPIO_IRQS		(32 * 4)
#elif defined CONFIG_ARCH_MX3
#define MXC_GPIO_IRQS		(32 * 3)
#elif defined CONFIG_ARCH_MX37
#define MXC_GPIO_IRQS		(32 * 3)
#endif

/*
 * The next 16 interrupts are for board specific purposes.  Since
 * the kernel can only run on one machine at a time, we can re-use
 * these.  If you need more, increase MXC_BOARD_IRQS, but keep it
 * within sensible limits.
 */
#define MXC_BOARD_IRQ_START	(MXC_INTERNAL_IRQS + MXC_GPIO_IRQS)

#ifdef CONFIG_MACH_MX31ADS_WM1133_EV1
#define MXC_BOARD_IRQS  80
#elif defined CONFIG_MACH_MX35_3DS
#define MXC_BOARD_IRQS	32
#else
#define MXC_BOARD_IRQS	16
#endif

#ifdef CONFIG_MACH_MX35_3DS
#define MXC_PSEUDO_IO_BASE	(MXC_BOARD_IRQ_START + 16)
#endif


#define MXC_IPU_IRQ_START	(MXC_BOARD_IRQ_START + MXC_BOARD_IRQS)

#ifdef CONFIG_MX3_IPU_IRQS
#define MX3_IPU_IRQS CONFIG_MX3_IPU_IRQS
#else
#define MX3_IPU_IRQS 0
#endif
/* REVISIT: Add IPU irqs on IMX51 */

#ifdef CONFIG_MACH_TS48XX
#define NR_IRQS                 (MXC_IPU_IRQ_START + MX3_IPU_IRQS + 8)
#else
#define NR_IRQS                 (MXC_IPU_IRQ_START + MX3_IPU_IRQS)
#endif

extern int imx_irq_set_priority(unsigned char irq, unsigned char prio);

/* all normal IRQs can be FIQs */
#define FIQ_START	0
/* switch betwean IRQ and FIQ */
extern int mxc_set_irq_fiq(unsigned int irq, unsigned int type);

/*
 * This function is used to get the AVIC Lo and Hi interrupts
 * that are enabled as wake up sources to wake up the core from suspend
 */
void mxc_get_wake_irq(u32 *wake_src[]);

#endif /* __ASM_ARCH_MXC_IRQS_H__ */
