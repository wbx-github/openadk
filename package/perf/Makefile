# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/$(ADK_TARGET_OS)-ver.mk

PKG_NAME:=		perf
PKG_VERSION:=		$(KERNEL_VERSION)
PKG_RELEASE:=		1
PKG_DESCR:=		userland tools for linux performance counters
PKG_SECTION:=		app/debug
PKG_DEPENDS:=		elfutils newt
PKG_BUILDDEP:=		elfutils newt
PKG_URL:=		https://perf.wiki.kernel.org/index.php/Main_Page

# elfutils require argp()
PKG_LIBC_DEPENDS:=	glibc

NO_DISTFILES:=		1

include $(ADK_TOPDIR)/mk/package.mk
include $(ADK_TOPDIR)/mk/kernel-vars.mk

$(eval $(call PKG_template,PERF,perf,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

do-build:
	${KERNEL_MAKE} WERROR=0 -C "$(LINUX_DIR)/tools/perf" all

do-install:
	${KERNEL_MAKE} WERROR=0 -C "$(LINUX_DIR)/tools/perf" \
		prefix="$(WRKINST)" install

perf-install:
	$(INSTALL_DIR) $(IDIR_PERF)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/bin/perf $(IDIR_PERF)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
