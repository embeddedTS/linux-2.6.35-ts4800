# $Id: Makefile,v 1.1.1.1 2011/08/19 02:09:28 ronald Exp $
#
# Makefile for the linux kernel.
#

obj-y   := dma.o pinmux.o io.o arbiter.o
obj-$(CONFIG_ETRAX_VCS_SIM) += vcs_hook.o
obj-$(CONFIG_CPU_FREQ)   += cpufreq.o

clean:

