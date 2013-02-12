/*
 * Copyright (C) 2008-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 */
/*
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */

#include <linux/linkage.h>

#define ARM_CTRL_DCACHE  1 << 2
#define ARM_CTRL_ICACHE  1 << 12
#define ARM_AUXCR_L2EN   1 << 1


/*
 *	cpu_do_suspend_workaround()
 *
 *	Suspend the processor (eg, wait for interrupt).
 *
 *	IRQs are already disabled.
 */
ENTRY(cpu_do_suspend_workaround)
    stmfd   sp!, {r4,r5,r6,r7,r9,r10,r11}     @ Save registers

   mov    r6, r0                       @save iomux address
    /* Disable L1 caches */
    mrc     p15, 0, r0, c1, c0, 0    @ R0 = system control reg
    bic     r0, r0, #ARM_CTRL_ICACHE @ Disable ICache
    bic     r0, r0, #ARM_CTRL_DCACHE @ Disable DCache
    mcr     p15, 0, r0, c1, c0, 0    @ Update system control reg

    mrc     p15, 1, r0, c0, c0, 1   @ Read CLIDR
    ands    r3, r0, #0x7000000       @ Isolate level of coherency
    mov     r3, r3, lsr #23         @ Cache level value (naturally aligned)
    beq     FinishedClean
    mov     r10, #0
Loop1Clean:
    add     r2, r10, r10, lsr #1    @ Work out cache level
    mov     r1, r0, lsr r2          @ R0 bottom 3 bits = Cache Type for this level
    and     r1, r1, #7              @ Get those 3 bits alone
    cmp     r1, #2
    blt     SkipClean                @ No cache or only instruction cache at this level
    mcr     p15, 2, r10, c0, c0, 0  @ Write the Cache Size selection register
    mov     r1, #0
    .long   0xF57FF06F              @ ISB
    mrc     p15, 1, r1, c0, c0, 0   @ Reads current Cache Size ID register
    and     r2, r1, #7             @ Extract the line length field
    add     r2, r2, #4              @ Add 4 for the line length offset (log2 16 bytes)
    ldr     r4, =0x3FF
    ands    r4, r4, r1, lsr #3      @ R4 is the max number on the way size (right aligned)
    clz     r5, r4                  @ R5 is the bit position of the way size increment
    ldr     r7, =0x00007FFF
    ands    r7, r7, r1, lsr #13     @ R7 is the max number of the index size (right aligned)
Loop2Clean:
    mov     r9, r4                  @ R9 working copy of the max way size (right aligned)
Loop3Clean:
    orr     r11, r10, r9, lsl r5    @ Factor in the way number and cache number into R11
    orr     r11, r11, r7, lsl r2    @ Factor in the index number
    mcr     p15, 0, r11, c7, c14, 2 @ Clean and invalidate by set/way
    subs    r9, r9, #1              @ Decrement the way number
    bge     Loop3Clean
    subs    r7, r7, #1              @ Decrement the index
    bge     Loop2Clean
SkipClean:
    add     r10, r10, #2            @ Increment the cache number
    cmp     r3, r10
    bgt     Loop1Clean

FinishedClean:

    /* Disable L2 cache */
    mrc     p15, 0, r0, c1, c0, 1   @ R0 = auxiliary control reg
    bic     r0, r0, #ARM_AUXCR_L2EN @ Disable L2 cache
    mcr     p15, 0, r0, c1, c0, 1   @ Update aux control reg

	/*Set the DDR drive strength to low */
	ldr        r10, [r6]
	and       r10, r10, #0xF1        @ clear bits 2-1
	str        r10, [r6]

    /*
     * PLL1 workaround as the following
     * Before enter WFI
     *      (1) switch DDR and ARM off PLL1
     *      (2) Disable AREN bit to avoid PLL1 restart during MFN change)
     *      (3) set PLL1 to 864Mhz with MFI = 8, MFN = 180, MFD = 179
     *      (4) Manual restart PLL1
     * After CPU out of WFI
     *      (5) Set PLL1 to 800Mhz with only change MFN to 60, others keep
     *      (6) Wait MFN change complete by delay more than 4us,
     *      (7) Switch DDR and ARM back to PLL1
     */

	ldr r3, =g_pll1_base
	ldr r3, [r3]
	ldr r4, =g_ccm_base
	ldr r4, [r4]

	/* step 1 */
	ldr     r0, [r4, #0x14]
	tst     r0, #(1 << 30)
	beq     2f

	bic     r0, r0, #(1 << 30)
	str     r0, [r4, #0x14]
	mov     r5, #1  /* r5 DDR from PLL1 flag, Reserved */

1:
	ldr     r0, [r4, #0x48]
	ands    r0, r0, #(1 << 8)
	bne     1b
2:
	/* Make sure Step-clk is sourced from 24MHz. */
	ldr     r0, [r4, #0x0c]
	bic     r0, r0, #(0x3 << 7)
	str     r0, [r4, #0x0c]

	/* Set ARM to be sourced from Step-clk. */
	orr     r0, r0, #( 1 << 2)
	str     r0, [r4, #0x0c]

	/* step 2 */
	ldr r0, [r3, #0x4]
	bic r0, r0, #0x2
	str r0, [r3, #0x4] /* disable auto-restart AREN bit */

	/* step 3 */
	mov r0, #0x80
	mov r1, #179
	mov r2, #180
	str r0, [r3, #0x08]
	str r0, [r3, #0x1c]

	str r1, [r3, #0x0c]
	str r1, [r3, #0x20]

	str r2, [r3, #0x10]
	str r2, [r3, #0x24]

	/* step 4 */
	ldr r0, =0x00001236 /* Set PLM =1, manual restart and enable PLL*/
	str r0, [r3, #0x0]

    .long     0xe320f003              @ Opcode for WFI

	/* step 5 */
	ldr     r0, =60
	str     r0, [r3, #0x10]

	/* step 6 */
	ldr     r0, [r3, #0x04]
	orr     r0, r0, #0x1
	str     r0, [r3, #0x04]

      /* Wait for LDREQ bit to clear. */
2:
	ldr     r0, [r3, #0x4]
	tst     r0, #1
	bne     2b

	mov r0, #100 /* delay more than 4us */
3:
	subs r0, r0, #1
	bge 3b

	/* step 7 */
	ldr     r0, [r4, #0x0c]
	bic     r0, r0, #(1 << 2)
	str     r0, [r4, #0x0c]

	cmp     r5, #1
	bne     wfi_done

	ldr     r0, [r4, #0x14]
	orr     r0, r0, #(1 << 30)
	str     r0, [r4, #0x14]

4:
	ldr     r0, [r4, #0x48]
	ands    r0, r0, #(1 << 8)
	bne     4b

wfi_done:
	/*Set the DDR drive strength to max */
	orr       r10, r10, #0x06        @ set bits 2-1
	str        r10, [r6]

    mov     r0, #0
    mcr     p15, 0, r0, c7, c5, 0   @ Invalidate inst cache

    /* Invalidate data caches */
    mrc     p15, 1, r0, c0, c0, 1   @ Read CLIDR
    ands    r3, r0, #0x7000000      @ Isolate level of coherency
    mov     r3, r3, lsr #23         @ Cache level value (naturally aligned)
    beq     FinishedInvalidate
    mov     r10, #0
Loop1Invalidate:
    add     r2, r10, r10, lsr #1    @ Work out cache level
    mov     r1, r0, lsr r2          @ R0 bottom 3 bits = Cache Type for this level
    and     r1, r1, #7              @ Get those 3 bits alone
    cmp     r1, #2
    blt     SkipInvalidate          @ No cache or only instruction cache at this level
    mcr     p15, 2, r10, c0, c0, 0  @ Write the Cache Size selection register
    mov     r1, #0
    .long   0xF57FF06F              @ ISB
    mrc     p15, 1, r1, c0, c0, 0   @ Reads current Cache Size ID register
    and     r2, r1, #7              @ Extract the line length field
    add     r2, r2, #4              @ Add 4 for the line length offset (log2 16 bytes)
    ldr     r4, =0x3FF
    ands    r4, r4, r1, lsr #3      @ R4 is the max number on the way size (right aligned)
    clz     r5, r4                  @ R5 is the bit position of the way size increment
    ldr     r7, =0x00007FFF
    ands    r7, r7, r1, lsr #13     @ R7 is the max number of the index size (right aligned)
Loop2Invalidate:
    mov     r9, r4                  @ R9 working copy of the max way size (right aligned)
Loop3Invalidate:
    orr     r11, r10, r9, lsl r5    @ Factor in the way number and cache number into R11
    orr     r11, r11, r7, lsl r2    @ Factor in the index number
    mcr     p15, 0, r11, c7, c6, 2  @ Invalidate by set/way
    subs    r9, r9, #1              @ Decrement the way number
    bge     Loop3Invalidate
    subs    r7, r7, #1              @ Decrement the index
    bge     Loop2Invalidate
SkipInvalidate:
    add     r10, r10, #2            @ Increment the cache number
    cmp     r3, r10
    bgt     Loop1Invalidate

FinishedInvalidate:

    /* Enable L2 cache */
    mrc     p15, 0, r0, c1, c0, 1   @ R0 = auxiliary control reg
    orr     r0, r0, #ARM_AUXCR_L2EN @ Enable L2 cache
    mcr     p15, 0, r0, c1, c0, 1   @ Update aux control reg

    /* Enable L1 caches */
    mrc     p15, 0, r0, c1, c0, 0    @ R0 = system control reg
    orr     r0, r0, #ARM_CTRL_ICACHE @ Enable ICache
    orr     r0, r0, #ARM_CTRL_DCACHE @ Enable DCache
    mcr     p15, 0, r0, c1, c0, 0    @ Update system control reg

    /* Restore registers */
    ldmfd sp!, {r4,r5,r6,r7,r9,r10,r11}
    mov		pc, lr

	.type	cpu_do_suspend, #object
ENTRY(cpu_do_suspend)
	.word	cpu_do_suspend_workaround
	.size	cpu_do_suspend_workaround, . - cpu_do_suspend_workaround
