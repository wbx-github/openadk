# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include Makefile.inc
include ../rules.mk
include ${ADK_TOPDIR}/mk/buildhlp.mk

ifeq (${ADK_MAKE_PARALLEL},y)
GMP_MAKEOPTS+=		-j${ADK_MAKE_JOBS}
endif

ifeq (${ARCH_FOR_BUILD},x32)
GMP_CONFOPTS+=		ABI=x32
endif

$(WRKBUILD)/.configured:
	(cd $(WRKBUILD); \
		PATH="$(STAGING_HOST_DIR)/usr/bin:$$PATH" \
		./configure ${GMP_CONFOPTS} \
		--prefix=$(STAGING_HOST_DIR)/usr \
		--with-pic \
		--disable-shared \
		--enable-static \
		CFLAGS="-std=gnu17" \
	)
	touch $@

$(WRKBUILD)/.compiled: $(WRKBUILD)/.configured
	env PATH="$(STAGING_HOST_DIR)/usr/bin:$$PATH" \
		$(MAKE) ${GMP_MAKEOPTS} -C $(WRKBUILD) all
	touch $@

$(WRKBUILD)/.installed: $(WRKBUILD)/.compiled
	$(MAKE) -C $(WRKBUILD) install
	touch $@

include ${ADK_TOPDIR}/mk/toolchain.mk
