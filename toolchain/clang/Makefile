# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include ../rules.mk
include Makefile.inc

WRKDIST=$(WRKDIR)/llvm-project-llvmorg-$(PKG_VERSION)

include ${ADK_TOPDIR}/mk/buildhlp.mk

$(WRKBUILD)/.configured:
	touch $@

$(WRKBUILD)/.compiled: $(WRKBUILD)/.configured
	touch $@

$(WRKBUILD)/.installed: $(WRKBUILD)/.compiled
	touch $@

$(WRKBUILD)/.final:
	touch $@

include ${ADK_TOPDIR}/mk/toolchain.mk
