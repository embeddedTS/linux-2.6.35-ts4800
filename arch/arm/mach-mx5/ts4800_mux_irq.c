#include <linux/irq.h>
#include <linux/gfp.h>
#include <linux/seq_file.h>
#include <linux/interrupt.h>
#include <linux/sysdev.h>
#include <mach/gpio.h>


#define FPGA_REGS_BASE FPGA_BASE_ADDR_VIRT
#define FPGA_REG(x) (*((volatile u16 *)(FPGA_REGS_BASE + (x))))
#define FPGA_IRQ_OFFSET       0x5008     /* IRQ cause */
#define FPGA_IRQ_MASK_OFFSET  0x5004     /* IRQ mask (1=masked) */
#define FPGA_CONTROL_REG_OFFSET 0x10
#define MIN_FPGA_IRQ    272
#define MAX_FPGA_IRQ    (MIN_FPGA_IRQ + 15)
#define IS_BAD_FPGA_IRQ(x) ((x) < MIN_FPGA_IRQ || (x) > MAX_FPGA_IRQ)

static void mask_muxed_irq(unsigned int irq);
static void unmask_muxed_irq(unsigned int irq);
static volatile unsigned long *gpioregs;

void mux_irq_handler(unsigned int irq, struct irq_desc *desc)
{
   unsigned int bit, n;
   unsigned short fpga_irq_reg;
   unsigned long pins;

   /*
    * On the TS-4800, the FPGA IRQ line (pin #50) is connected to the
    * MX515 EIM_27, which is IRQ #169.  This handler is installed on
    * the IRQ down below in ts4800_init_mux_irq().
    *
    * When the FPGA asserts its IRQ line, we end up here.  Now we need
    * to read the FPGA's IRQ register to determine what peripheral(s) need to be serviced.
    */

   /*    Read the IRQ register from the FPGA...
    *
    *    BIT 0: XUART            (IRQ #272)
    *    BIT 1: CAN              (IRQ #273)
    *    BIT 2: CAN2             (IRQ #274)
    *    BIT 3: PC/104 IRQ 5     (IRQ #275)
    *    BIT 4: PC/104 IRQ 6     (IRQ #276)
    *    BIT 5: PC/104 IRQ 7     (IRQ #277)
    *    BITS 6-15: Reserved     (IRQ #278-288)
    */

   gpioregs[0x18 / 4] = (1<<9);     // clear status for irq 169

   while((fpga_irq_reg = 0xFFFF & FPGA_REG(FPGA_IRQ_OFFSET)))   {
      for(n=0,bit=1; bit < 0x8000; bit <<= 1, n++)  {
         if(fpga_irq_reg & bit) {
            mask_muxed_irq(MIN_FPGA_IRQ + n);
            generic_handle_irq(MIN_FPGA_IRQ + n);
         }
      }
   }
}


static void unmask_muxed_irq(unsigned int irq)
{
   int bit = irq - MIN_FPGA_IRQ;
   if IS_BAD_FPGA_IRQ(irq)
      return;

   FPGA_REG(FPGA_IRQ_MASK_OFFSET) &= ~BIT(bit);
}

static void mask_muxed_irq(unsigned int irq)
{
   int bit = irq - MIN_FPGA_IRQ;
   if IS_BAD_FPGA_IRQ(irq)
      return;

   FPGA_REG(FPGA_IRQ_MASK_OFFSET) |= BIT(bit);
}

static void ack_muxed_irq(unsigned int irq)
{
#if (0)
   /* temp hack for test... */
   int bit = irq - MIN_FPGA_IRQ;
   if IS_BAD_FPGA_IRQ(irq)
      return;

   printk("ack %d\n", irq);
   FPGA_REG(0x10) = 0;
#endif
}

static struct irq_chip muxed_irq_chip = {
   .name    = "MUXIRQ",
   .mask    = mask_muxed_irq,
   .unmask  = unmask_muxed_irq,
   .ack     = ack_muxed_irq
};


void __init ts4800_init_mux_irq(void)
{
   int n;
   volatile unsigned long x;
   volatile unsigned long *iomuxregs = (volatile unsigned long *)(AIPS1_BASE_ADDR_VIRT + 0x000A8000);
   gpioregs = (volatile unsigned long *)(AIPS1_BASE_ADDR_VIRT + 0x00088000);

   FPGA_REG(FPGA_IRQ_MASK_OFFSET) = 0xFFFF;  /* mask all */

    /*
    * On the TS-4800, the FPGA interrupt is connected to EIM_D27 on
    * the MX515. This pin must be configured as a GPIO pin, by writing
    * 001b to the MUX_MODE bits of the IOMUXC_SW_MUX_CTL_PAD_EIM_D27
    * register.  Doing so makes this pin EIM_GPIO2_9.
    */
   iomuxregs[0x88 / 4] = 1;

   gpioregs[0x18 / 4] = (1<<9);              // clr status for irq 169

   for(n=272; n < 280; n++)   {
      set_irq_chip(n, &muxed_irq_chip);
      set_irq_handler(n, handle_simple_irq);
      set_irq_flags(n, IRQF_VALID);
   }

   /* Install mux handler on GPIO2_9, which is IRQ #169 */
   set_irq_chained_handler(169, mux_irq_handler);

}

