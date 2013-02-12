#ifndef __ASM_ARCH_MXC_MX51_H__
#define __ASM_ARCH_MXC_MX51_H__

/*
 * MX51 memory map:
 *
 *
 * Virt		Phys		Size	What
 * ---------------------------------------------------------------------------
 * FA3E0000	1FFE0000	128K	IRAM (SCCv2 RAM)
 *         	30000000	256M	GPU
 *         	40000000	512M	IPU
 * FA200000	60000000	1M	DEBUG
 * FB100000	70000000	1M	SPBA 0
 * FB000000	73F00000	1M	AIPS 1
 * FB200000	83F00000	1M	AIPS 2
 *		8FFFC000	16K	TZIC (interrupt controller)
 *         	90000000	256M	CSD0 SDRAM/DDR
 *         	A0000000	256M	CSD1 SDRAM/DDR
 *         	B0000000	128M	CS0 Flash
 *         	B8000000	128M	CS1 Flash
 *         	C0000000	128M	CS2 Flash
 *         	C8000000	64M	CS3 Flash
 *         	CC000000	32M	CS4 SRAM
 *         	CE000000	32M	CS5 SRAM
 *		CFFF0000	64K	NFC (NAND Flash AXI)
 *
 */

/*
 * IROM
 */
#define MX51_IROM_BASE_ADDR		0x0
#define MX51_IROM_SIZE			SZ_64K

/*
 * IRAM
 */
#define MX51_IRAM_BASE_ADDR		0x1FFE0000	/* internal ram */
#define MX51_IRAM_BASE_ADDR_VIRT	0xFA3E0000
#define MX51_IRAM_PARTITIONS		16
#define MX51_IRAM_PARTITIONS_TO1	12
#define MX51_IRAM_SIZE		(MX51_IRAM_PARTITIONS * SZ_8K)	/* 128KB */

/*
 * NFC
 */
#define MX51_NFC_AXI_BASE_ADDR		0xCFFF0000	/* NAND flash AXI */
#define MX51_NFC_AXI_SIZE		SZ_64K

/*
 * Graphics Memory of GPU
 */
#define MX51_GPU_BASE_ADDR		0x20000000
#define MX51_GPU2D_BASE_ADDR		0xD0000000

#define MX51_TZIC_BASE_ADDR_TO1		0x8FFFC000
#define MX51_TZIC_BASE_ADDR		0xE0000000

#define MX51_DEBUG_BASE_ADDR		0x60000000
#define MX51_DEBUG_BASE_ADDR_VIRT	0xFA200000
#define MX51_DEBUG_SIZE			SZ_1M
#define MX51_ETB_BASE_ADDR		(MX51_DEBUG_BASE_ADDR + 0x00001000)
#define MX51_ETM_BASE_ADDR		(MX51_DEBUG_BASE_ADDR + 0x00002000)
#define MX51_TPIU_BASE_ADDR		(MX51_DEBUG_BASE_ADDR + 0x00003000)
#define MX51_CTI0_BASE_ADDR		(MX51_DEBUG_BASE_ADDR + 0x00004000)
#define MX51_CTI1_BASE_ADDR		(MX51_DEBUG_BASE_ADDR + 0x00005000)
#define MX51_CTI2_BASE_ADDR		(MX51_DEBUG_BASE_ADDR + 0x00006000)
#define MX51_CTI3_BASE_ADDR		(MX51_DEBUG_BASE_ADDR + 0x00007000)
#define MX51_CORTEX_DBG_BASE_ADDR	(MX51_DEBUG_BASE_ADDR + 0x00008000)

/*
 * SPBA global module enabled #0
 */
#define MX51_SPBA0_BASE_ADDR 		0x70000000
#define MX51_SPBA0_BASE_ADDR_VIRT	0xFB100000
#define MX51_SPBA0_SIZE			SZ_1M

#define MX51_MMC_SDHC1_BASE_ADDR	(MX51_SPBA0_BASE_ADDR + 0x00004000)
#define MX51_MMC_SDHC2_BASE_ADDR	(MX51_SPBA0_BASE_ADDR + 0x00008000)
#define MX51_UART3_BASE_ADDR 		(MX51_SPBA0_BASE_ADDR + 0x0000C000)
#define MX51_CSPI1_BASE_ADDR 		(MX51_SPBA0_BASE_ADDR + 0x00010000)
#define MX51_SSI2_BASE_ADDR		(MX51_SPBA0_BASE_ADDR + 0x00014000)
#define MX51_MMC_SDHC3_BASE_ADDR	(MX51_SPBA0_BASE_ADDR + 0x00020000)
#define MX51_MMC_SDHC4_BASE_ADDR	(MX51_SPBA0_BASE_ADDR + 0x00024000)
#define MX51_SPDIF_BASE_ADDR		(MX51_SPBA0_BASE_ADDR + 0x00028000)
#define MX51_ATA_DMA_BASE_ADDR		(MX51_SPBA0_BASE_ADDR + 0x00030000)
#define MX51_SLIM_DMA_BASE_ADDR		(MX51_SPBA0_BASE_ADDR + 0x00034000)
#define MX51_HSI2C_DMA_BASE_ADDR	(MX51_SPBA0_BASE_ADDR + 0x00038000)
#define MX51_SPBA_CTRL_BASE_ADDR	(MX51_SPBA0_BASE_ADDR + 0x0003C000)

/*
 * defines for SPBA modules
 */
#define MX51_SPBA_SDHC1	0x04
#define MX51_SPBA_SDHC2	0x08
#define MX51_SPBA_UART3	0x0C
#define MX51_SPBA_CSPI1	0x10
#define MX51_SPBA_SSI2	0x14
#define MX51_SPBA_SDHC3	0x20
#define MX51_SPBA_SDHC4	0x24
#define MX51_SPBA_SPDIF	0x28
#define MX51_SPBA_ATA	0x30
#define MX51_SPBA_SLIM	0x34
#define MX51_SPBA_HSI2C	0x38
#define MX51_SPBA_CTRL	0x3C

/*
 * AIPS 1
 */
#define MX51_AIPS1_BASE_ADDR 	0x73F00000
#define MX51_AIPS1_BASE_ADDR_VIRT	0xFB000000
#define MX51_AIPS1_SIZE		SZ_1M

#define MX51_OTG_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x00080000)
#define MX51_GPIO1_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x00084000)
#define MX51_GPIO2_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x00088000)
#define MX51_GPIO3_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x0008C000)
#define MX51_GPIO4_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x00090000)
#define MX51_KPP_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x00094000)
#define MX51_WDOG_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x00098000)
#define MX51_WDOG2_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x0009C000)
#define MX51_GPT1_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x000A0000)
#define MX51_SRTC_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x000A4000)
#define MX51_IOMUXC_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x000A8000)
#define MX51_EPIT1_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x000AC000)
#define MX51_EPIT2_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x000B0000)
#define MX51_PWM1_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x000B4000)
#define MX51_PWM2_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x000B8000)
#define MX51_UART1_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x000BC000)
#define MX51_UART2_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x000C0000)
#define MX51_SRC_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x000D0000)
#define MX51_CCM_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x000D4000)
#define MX51_GPC_BASE_ADDR	(MX51_AIPS1_BASE_ADDR + 0x000D8000)

/*
 * Defines for modules using static and dynamic DMA channels
 */
#define MX51_MXC_DMA_CHANNEL_IRAM	30
#define MX51_MXC_DMA_CHANNEL_SPDIF_TX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_UART1_RX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_UART1_TX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_UART2_RX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_UART2_TX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_UART3_RX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_UART3_TX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_MMC1	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_MMC2	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_SSI1_RX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_SSI1_TX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_SSI2_RX	MXC_DMA_DYNAMIC_CHANNEL
#ifdef CONFIG_SDMA_IRAM
#define MX51_MXC_DMA_CHANNEL_SSI2_TX	(MX51_MXC_DMA_CHANNEL_IRAM + 1)
#else				/*CONFIG_SDMA_IRAM */
#define MX51_MXC_DMA_CHANNEL_SSI2_TX	MXC_DMA_DYNAMIC_CHANNEL
#endif				/*CONFIG_SDMA_IRAM */
#define MX51_MXC_DMA_CHANNEL_CSPI1_RX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_CSPI1_TX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_CSPI2_RX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_CSPI2_TX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_CSPI3_RX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_CSPI3_TX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_ATA_RX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_ATA_TX	MXC_DMA_DYNAMIC_CHANNEL
#define MX51_MXC_DMA_CHANNEL_MEMORY	MXC_DMA_DYNAMIC_CHANNEL

/*
 * AIPS 2
 */
#define MX51_AIPS2_BASE_ADDR		0x83F00000
#define MX51_AIPS2_BASE_ADDR_VIRT	0xFB200000
#define MX51_AIPS2_SIZE			SZ_1M

#define MX51_PLL1_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x00080000)
#define MX51_PLL2_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x00084000)
#define MX51_PLL3_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x00088000)
#define MX51_AHBMAX_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x00094000)
#define MX51_IIM_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x00098000)
#define MX51_CSU_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x0009C000)
#define MX51_ARM_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000A0000)
#define MX51_OWIRE_BASE_ADDR 	(MX51_AIPS2_BASE_ADDR + 0x000A4000)
#define MX51_FIRI_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000A8000)
#define MX51_CSPI2_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000AC000)
#define MX51_SDMA_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000B0000)
#define MX51_SCC_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000B4000)
#define MX51_ROMCP_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000B8000)
#define MX51_RTIC_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000BC000)
#define MX51_CSPI3_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000C0000)
#define MX51_I2C2_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000C4000)
#define MX51_I2C1_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000C8000)
#define MX51_SSI1_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000CC000)
#define MX51_AUDMUX_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000D0000)
#define MX51_M4IF_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000D8000)
#define MX51_ESDCTL_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000D9000)
#define MX51_WEIM_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000DA000)
#define MX51_NFC_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000DB000)
#define MX51_EMI_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000DBF00)
#define MX51_MIPI_HSC_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000DC000)
#define MX51_ATA_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000E0000)
#define MX51_SIM_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000E4000)
#define MX51_SSI3BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000E8000)
#define MX51_MXC_FEC_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000EC000)
#define MX51_TVE_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000F0000)
#define MX51_VPU_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000F4000)
#define MX51_SAHARA_BASE_ADDR	(MX51_AIPS2_BASE_ADDR + 0x000F8000)

/*
 * Memory regions and CS
 */
#define MX51_GPU_CTRL_BASE_ADDR		0x30000000
#define MX51_IPU_CTRL_BASE_ADDR		0x40000000
#define MX51_CSD0_BASE_ADDR		0x90000000
#define MX51_CSD1_BASE_ADDR		0xA0000000
#define MX51_CS0_BASE_ADDR		0xB0000000
#define MX51_CS1_BASE_ADDR		0xB8000000
#define MX51_CS2_BASE_ADDR		0xC0000000
#define MX51_CS3_BASE_ADDR		0xC8000000
#define MX51_CS4_BASE_ADDR		0xCC000000
#define MX51_CS5_BASE_ADDR		0xCE000000

/* Does given address belongs to the specified memory region? */
#define ADDRESS_IN_REGION(addr, start, size)			\
	(((addr) >= (start)) && ((addr) < (start)+(size)))

/* Does given address belongs to the specified named `module'? */
#define MX51_IS_MODULE(addr, module)			       \
	ADDRESS_IN_REGION(addr, MX51_ ## module ## _BASE_ADDR, \
				MX51_ ## module ## _SIZE)
/*
 * This macro defines the physical to virtual address mapping for all the
 * peripheral modules. It is used by passing in the physical address as x
 * and returning the virtual address. If the physical address is not mapped,
 * it returns 0xDEADBEEF
 */

#define MX51_IO_ADDRESS(x)					\
	(void __iomem *)					\
	(MX51_IS_MODULE(x, IRAM) ? MX51_IRAM_IO_ADDRESS(x) :	\
	MX51_IS_MODULE(x, DEBUG) ? MX51_DEBUG_IO_ADDRESS(x) :	\
	MX51_IS_MODULE(x, SPBA0) ? MX51_SPBA0_IO_ADDRESS(x) :	\
	MX51_IS_MODULE(x, AIPS1) ? MX51_AIPS1_IO_ADDRESS(x) :	\
	MX51_IS_MODULE(x, AIPS2) ? MX51_AIPS2_IO_ADDRESS(x) :	\
	0xDEADBEEF)

/*
 * define the address mapping macros: in physical address order
 */
#define MX51_IRAM_IO_ADDRESS(x)  \
	(((x) - MX51_IRAM_BASE_ADDR) + MX51_IRAM_BASE_ADDR_VIRT)

#define MX51_DEBUG_IO_ADDRESS(x)  \
	(((x) - MX51_DEBUG_BASE_ADDR) + MX51_DEBUG_BASE_ADDR_VIRT)

#define MX51_SPBA0_IO_ADDRESS(x)  \
	(((x) - MX51_SPBA0_BASE_ADDR) + MX51_SPBA0_BASE_ADDR_VIRT)

#define MX51_AIPS1_IO_ADDRESS(x)  \
	(((x) - MX51_AIPS1_BASE_ADDR) + MX51_AIPS1_BASE_ADDR_VIRT)

#define MX51_AIPS2_IO_ADDRESS(x)  \
	(((x) - MX51_AIPS2_BASE_ADDR) + MX51_AIPS2_BASE_ADDR_VIRT)

#define MX51_IS_MEM_DEVICE_NONSHARED(x)		0

/*
 * DMA request assignments
 */
#define MX51_DMA_REQ_SSI3_TX1	47
#define MX51_DMA_REQ_SSI3_RX1	46
#define MX51_DMA_REQ_SPDIF	45
#define MX51_DMA_REQ_UART3_TX	44
#define MX51_DMA_REQ_UART3_RX	43
#define MX51_DMA_REQ_SLIM_B_TX	42
#define MX51_DMA_REQ_SDHC4	41
#define MX51_DMA_REQ_SDHC3	40
#define MX51_DMA_REQ_CSPI_TX	39
#define MX51_DMA_REQ_CSPI_RX	38
#define MX51_DMA_REQ_SSI3_TX2	37
#define MX51_DMA_REQ_IPU	36
#define MX51_DMA_REQ_SSI3_RX2	35
#define MX51_DMA_REQ_EPIT2	34
#define MX51_DMA_REQ_CTI2_1	33
#define MX51_DMA_REQ_EMI_WR	32
#define MX51_DMA_REQ_CTI2_0	31
#define MX51_DMA_REQ_EMI_RD	30
#define MX51_DMA_REQ_SSI1_TX1	29
#define MX51_DMA_REQ_SSI1_RX1	28
#define MX51_DMA_REQ_SSI1_TX2	27
#define MX51_DMA_REQ_SSI1_RX2	26
#define MX51_DMA_REQ_SSI2_TX1	25
#define MX51_DMA_REQ_SSI2_RX1	24
#define MX51_DMA_REQ_SSI2_TX2	23
#define MX51_DMA_REQ_SSI2_RX2	22
#define MX51_DMA_REQ_SDHC2	21
#define MX51_DMA_REQ_SDHC1	20
#define MX51_DMA_REQ_UART1_TX	19
#define MX51_DMA_REQ_UART1_RX	18
#define MX51_DMA_REQ_UART2_TX	17
#define MX51_DMA_REQ_UART2_RX	16
#define MX51_DMA_REQ_GPU	15
#define MX51_DMA_REQ_EXTREQ1	14
#define MX51_DMA_REQ_FIRI_TX	13
#define MX51_DMA_REQ_FIRI_RX	12
#define MX51_DMA_REQ_HS_I2C_RX	11
#define MX51_DMA_REQ_HS_I2C_TX	10
#define MX51_DMA_REQ_CSPI2_TX	9
#define MX51_DMA_REQ_CSPI2_RX	8
#define MX51_DMA_REQ_CSPI1_TX	7
#define MX51_DMA_REQ_CSPI1_RX	6
#define MX51_DMA_REQ_SLIM_B	5
#define MX51_DMA_REQ_ATA_TX_END	4
#define MX51_DMA_REQ_ATA_TX	3
#define MX51_DMA_REQ_ATA_RX	2
#define MX51_DMA_REQ_GPC	1
#define MX51_DMA_REQ_VPU	0

/*
 * Interrupt numbers
 */
#define MX51_MXC_INT_BASE	0
#define MX51_MXC_INT_RESV0	0
#define MX51_MXC_INT_MMC_SDHC1	1
#define MX51_MXC_INT_MMC_SDHC2	2
#define MX51_MXC_INT_MMC_SDHC3	3
#define MX51_MXC_INT_MMC_SDHC4	4
#define MX51_MXC_INT_RESV5	5
#define MX51_MXC_INT_SDMA	6
#define MX51_MXC_INT_IOMUX	7
#define MX51_MXC_INT_NFC	8
#define MX51_MXC_INT_VPU	9
#define MX51_MXC_INT_IPU_ERR	10
#define MX51_MXC_INT_IPU_SYN	11
#define MX51_MXC_INT_GPU	12
#define MX51_MXC_INT_RESV13	13
#define MX51_MXC_INT_USB_H1	14
#define MX51_MXC_INT_EMI	15
#define MX51_MXC_INT_USB_H2	16
#define MX51_MXC_INT_USB_H3	17
#define MX51_MXC_INT_USB_OTG	18
#define MX51_MXC_INT_SAHARA_H0	19
#define MX51_MXC_INT_SAHARA_H1	20
#define MX51_MXC_INT_SCC_SMN	21
#define MX51_MXC_INT_SCC_STZ	22
#define MX51_MXC_INT_SCC_SCM	23
#define MX51_MXC_INT_SRTC_NTZ	24
#define MX51_MXC_INT_SRTC_TZ	25
#define MX51_MXC_INT_RTIC	26
#define MX51_MXC_INT_CSU	27
#define MX51_MXC_INT_SLIM_B	28
#define MX51_MXC_INT_SSI1	29
#define MX51_MXC_INT_SSI2	30
#define MX51_MXC_INT_UART1	31
#define MX51_MXC_INT_UART2	32
#define MX51_MXC_INT_UART3	33
#define MX51_MXC_INT_RESV34	34
#define MX51_MXC_INT_RESV35	35
#define MX51_MXC_INT_CSPI1	36
#define MX51_MXC_INT_CSPI2	37
#define MX51_MXC_INT_CSPI	38
#define MX51_MXC_INT_GPT	39
#define MX51_MXC_INT_EPIT1	40
#define MX51_MXC_INT_EPIT2	41
#define MX51_MXC_INT_GPIO1_INT7	42
#define MX51_MXC_INT_GPIO1_INT6	43
#define MX51_MXC_INT_GPIO1_INT5	44
#define MX51_MXC_INT_GPIO1_INT4	45
#define MX51_MXC_INT_GPIO1_INT3	46
#define MX51_MXC_INT_GPIO1_INT2	47
#define MX51_MXC_INT_GPIO1_INT1	48
#define MX51_MXC_INT_GPIO1_INT0	49
#define MX51_MXC_INT_GPIO1_LOW	50
#define MX51_MXC_INT_GPIO1_HIGH	51
#define MX51_MXC_INT_GPIO2_LOW	52
#define MX51_MXC_INT_GPIO2_HIGH	53
#define MX51_MXC_INT_GPIO3_LOW	54
#define MX51_MXC_INT_GPIO3_HIGH	55
#define MX51_MXC_INT_GPIO4_LOW	56
#define MX51_MXC_INT_GPIO4_HIGH	57
#define MX51_MXC_INT_WDOG1	58
#define MX51_MXC_INT_WDOG2	59
#define MX51_MXC_INT_KPP	60
#define MX51_MXC_INT_PWM1	61
#define MX51_MXC_INT_I2C1	62
#define MX51_MXC_INT_I2C2	63
#define MX51_MXC_INT_HS_I2C	64
#define MX51_MXC_INT_RESV65	65
#define MX51_MXC_INT_RESV66	66
#define MX51_MXC_INT_SIM_IPB	67
#define MX51_MXC_INT_SIM_DAT	68
#define MX51_MXC_INT_IIM	69
#define MX51_MXC_INT_ATA	70
#define MX51_MXC_INT_CCM1	71
#define MX51_MXC_INT_CCM2	72
#define MX51_MXC_INT_GPC1	73
#define MX51_MXC_INT_GPC2	74
#define MX51_MXC_INT_SRC	75
#define MX51_MXC_INT_NM		76
#define MX51_MXC_INT_PMU	77
#define MX51_MXC_INT_CTI_IRQ	78
#define MX51_MXC_INT_CTI1_TG0	79
#define MX51_MXC_INT_CTI1_TG1	80
#define MX51_MXC_INT_MCG_ERR	81
#define MX51_MXC_INT_MCG_TMR	82
#define MX51_MXC_INT_MCG_FUNC	83
#define MX51_MXC_INT_GPU2_IRQ	84
#define MX51_MXC_INT_GPU2_BUSY	85
#define MX51_MXC_INT_RESV86	86
#define MX51_MXC_INT_FEC	87
#define MX51_MXC_INT_OWIRE	88
#define MX51_MXC_INT_CTI1_TG2	89
#define MX51_MXC_INT_SJC	90
#define MX51_MXC_INT_SPDIF	91
#define MX51_MXC_INT_TVE	92
#define MX51_MXC_INT_FIRI	93
#define MX51_MXC_INT_PWM2	94
#define MX51_MXC_INT_SLIM_EXP	95
#define MX51_MXC_INT_SSI3	96
#define MX51_MXC_INT_EMI_BOOT	97
#define MX51_MXC_INT_CTI1_TG3	98
#define MX51_MXC_INT_SMC_RX	99
#define MX51_MXC_INT_VPU_IDLE	100
#define MX51_MXC_INT_EMI_NFC	101
#define MX51_MXC_INT_GPU_IDLE	102

/* silicon revisions specific to i.MX51 */
#define MX51_CHIP_REV_1_0	0x10
#define MX51_CHIP_REV_1_1	0x11
#define MX51_CHIP_REV_1_2	0x12
#define MX51_CHIP_REV_1_3	0x13
#define MX51_CHIP_REV_2_0	0x20
#define MX51_CHIP_REV_2_1	0x21
#define MX51_CHIP_REV_2_2	0x22
#define MX51_CHIP_REV_2_3	0x23
#define MX51_CHIP_REV_3_0	0x30
#define MX51_CHIP_REV_3_1	0x31
#define MX51_CHIP_REV_3_2	0x32

/* Mandatory defines used globally */

#if !defined(__ASSEMBLY__) && !defined(__MXC_BOOT_UNCOMPRESS)

extern int mx51_revision(void);
#endif

#endif	/*  __ASM_ARCH_MXC_MX51_H__ */
