# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include Makefile.inc
include ../rules.mk
include $(ADK_TOPDIR)/mk/buildhlp.mk

ifeq ($(ADK_TOOLCHAIN_BINUTILS_GIT),y)
BINUTILS_VERSION:=	git
BFDLIB:=		.libs/libbfd.a
endif
ifeq ($(ADK_TOOLCHAIN_BINUTILS_2_41),y)
BINUTILS_VERSION:=	2.41
BFDLIB:=		.libs/libbfd.a
endif
ifeq ($(ADK_TOOLCHAIN_BINUTILS_2_40),y)
BINUTILS_VERSION:=	2.40
BFDLIB:=		libbfd.a
endif
ifeq ($(ADK_TOOLCHAIN_BINUTILS_2_39),y)
BINUTILS_VERSION:=	2.39
BFDLIB:=		libbfd.a
endif
ifeq ($(ADK_TOOLCHAIN_BINUTILS_2_28),y)
BINUTILS_VERSION:=	2.28
BFDLIB:=		libbfd.a
endif

$(WRKBUILD)/.configured:
	(cd $(WRKBUILD); autoreconf -vif;)
	(cd $(WRKBUILD); \
	CPPFLAGS="-idirafter $(ADK_TOPDIR)/adk/include" \
	./configure --prefix=$(STAGING_HOST_DIR)/usr \
		--target=$(GNU_TARGET_NAME) \
		--with-bfd-include-dir=$(TOOLCHAIN_BUILD_DIR)/w-binutils-$(BINUTILS_VERSION)-1/binutils-$(BINUTILS_VERSION)/bfd \
		--with-binutils-include-dir=$(TOOLCHAIN_BUILD_DIR)/w-binutils-$(BINUTILS_VERSION)-1/binutils-$(BINUTILS_VERSION)/include \
		--with-libbfd=$(TOOLCHAIN_BUILD_DIR)/w-binutils-$(BINUTILS_VERSION)-1/binutils-$(BINUTILS_VERSION)/bfd/$(BFDLIB) \
		--with-libiberty=$(TOOLCHAIN_BUILD_DIR)/w-binutils-$(BINUTILS_VERSION)-1/binutils-$(BINUTILS_VERSION)/libiberty/libiberty.a )
	touch $@

$(WRKBUILD)/.compiled: $(WRKBUILD)/.configured
	$(MAKE) -C $(WRKBUILD) all
	touch $@

$(WRKBUILD)/.installed: $(WRKBUILD)/.compiled
	$(INSTALL_BIN) $(WRKBUILD)/elf2flt $(TOOLCHAIN_DIR)/usr/$(GNU_TARGET_NAME)/bin
	$(INSTALL_BIN) $(WRKBUILD)/flthdr $(TOOLCHAIN_DIR)/usr/$(GNU_TARGET_NAME)/bin
	$(INSTALL_BIN) $(WRKBUILD)/ld-elf2flt $(TOOLCHAIN_DIR)/usr/$(GNU_TARGET_NAME)/bin
	$(INSTALL_DATA) $(WRKBUILD)/elf2flt.ld $(TOOLCHAIN_DIR)/usr/$(GNU_TARGET_NAME)/lib
	rm $(TOOLCHAIN_DIR)/usr/bin/$(GNU_TARGET_NAME)-ld $(TOOLCHAIN_DIR)/usr/$(GNU_TARGET_NAME)/bin/ld
	(cd $(TOOLCHAIN_DIR)/usr/$(GNU_TARGET_NAME)/bin \
		&& ln -sf ld.bfd ld.real \
		&& ln -sf ld-elf2flt ld \
	)
	(cd $(TOOLCHAIN_DIR)/usr/bin && \
		ln -sf ../$(GNU_TARGET_NAME)/bin/elf2flt $(GNU_TARGET_NAME)-elf2flt && \
		ln -sf ../$(GNU_TARGET_NAME)/bin/flthdr $(GNU_TARGET_NAME)-flthdr && \
		ln -sf ../$(GNU_TARGET_NAME)/bin/ld-elf2flt $(GNU_TARGET_NAME)-ld-elf2flt && \
		ln -sf ../$(GNU_TARGET_NAME)/bin/ld-elf2flt $(GNU_TARGET_NAME)-ld )
	(cd $(TOOLCHAIN_DIR)/usr/bin/ && ln -sf $(GNU_TARGET_NAME)-ld.bfd $(GNU_TARGET_NAME)-ld.real )
	touch $@

include $(ADK_TOPDIR)/mk/toolchain.mk
