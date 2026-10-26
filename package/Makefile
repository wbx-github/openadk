# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

# Main makefile for the packages

include $(ADK_TOPDIR)/rules.mk

ifeq (${ADK_TARGET_LIB_GLIBC},y)
package-$(ADK_PACKAGE_GLIBC) += glibc
gcc-compile: glibc-compile
endif

ifeq (${ADK_TARGET_LIB_MUSL},y)
package-$(ADK_PACKAGE_MUSL) += musl
gcc-compile: musl-compile
endif

ifeq (${ADK_TARGET_LIB_UCLIBC_NG},y)
package-$(ADK_PACKAGE_UCLIBC_NG) += uclibc-ng
gcc-compile: uclibc-ng-compile
endif

include $(ADK_TOPDIR)/package/Depends.mk

ifeq ($(ADK_TARGET_MINIMAL_USERLAND),y)
# without a C library only the mini-init packages can be built
package-y:=$(filter mini-init-%,$(package-y))
endif

COMPILE_PACKAGES:=$(patsubst %,%-compile,$(package-y))
HOST_COMPILE_PACKAGES:=$(patsubst %,%-host-compile,$(hostpackage-y))
INSTALL_PACKAGES:=$(patsubst %,%-install,$(package-y))

ifeq ($(ADK_PACKAGE_LIBICONV),y)
COMPILE_ICONV:=libiconv-compile
INSTALL_ICONV:=libiconv-install
endif

all: compile
download: $(patsubst %,%-download,$(package-y))
clean: $(patsubst %,%-clean,$(package-) $(package-y) base-files)
hostcompile: $(HOST_COMPILE_PACKAGES)
ifneq ($(ADK_APPLIANCE_TOOLCHAIN)$(ADK_TARGET_MINIMAL_USERLAND),)
compile: $(COMPILE_PACKAGES)
install: $(INSTALL_PACKAGES)
else
compile: base-files-compile $(COMPILE_ICONV) $(COMPILE_PACKAGES)
install: base-files-install $(INSTALL_ICONV) $(INSTALL_PACKAGES)
endif

%-download:
	$(START_TRACE) "package/$(patsubst %-download,%,$@)-download.. "
	$(MAKE) -C $(patsubst %-download,%,$@) fetch
	$(CMD_TRACE) " done"
	$(END_TRACE)

%-host-compile:
	$(START_TRACE) "package/$(patsubst %-host-compile,%,$@)-host.. "
	$(MAKE) -C $(patsubst %-host-compile,%,$@) hostpackage
	$(CMD_TRACE) " done"
	$(END_TRACE)

%-compile:
	$(START_TRACE) "package/$(patsubst %-compile,%,$@).. "
	@if test -f $(ADK_TOPDIR)/.rebuild.$(patsubst %-compile,%,$@); then \
		$(MAKE) -C $(patsubst %-compile,%,$@) clean ; \
		rm $(ADK_TOPDIR)/.rebuild.$(patsubst %-compile,%,$@) ; \
	fi
	$(MAKE) -C $(patsubst %-compile,%,$@) fake build-all-pkgs
	$(CMD_TRACE) " done"
	$(END_TRACE)

%-install:
	$(START_TRACE) "package/$(patsubst %-install,%,$@)-install.. "
	$(MAKE) -C $(patsubst %-install,%,$@) install
	$(CMD_TRACE) " done"
	$(END_TRACE)

%-clean:
	$(START_TRACE) "package/$(patsubst %-clean,%,$@)-clean.. "
	$(MAKE) -C $(patsubst %-clean,%,$@) clean
	$(CMD_TRACE) " done"
	$(END_TRACE)
