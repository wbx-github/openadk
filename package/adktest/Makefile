# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		adktest
PKG_VERSION:=		0.1
PKG_RELEASE:=		11
PKG_DESCR:=		helper tools and scripts for qemu testing
PKG_SECTION:=		base/tests
PKG_URL:=		http://openadk.org/

PKG_CFLINE_ADKTEST:=	select BUSYBOX_NC

NO_DISTFILES:=		1

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ADKTEST,adktest,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

adktest-install:
	$(INSTALL_DIR) $(IDIR_ADKTEST)/usr/bin
	$(INSTALL_BIN) $(WRKBUILD)/{qmp,quit} \
		$(IDIR_ADKTEST)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
