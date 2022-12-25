# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		fwupdate
PKG_VERSION:=		1.0
PKG_RELEASE:=		2
PKG_DESCR:=		update firmware
PKG_SECTION:=		base/adk
PKG_DEPENDS:=		mke2fs
PKG_URL:=		http://www.openadk.org

PKG_CFLINE_FWUPDATE:=	select BUSYBOX_SHA256SUM@

NO_DISTFILES:=          1

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FWUPDATE,fwupdate,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=          manual
BUILD_STYLE:=           manual
INSTALL_STYLE:=         manual

fwupdate-install:
	$(INSTALL_DIR) $(IDIR_FWUPDATE)/usr/sbin
	$(INSTALL_BIN) $(WRKBUILD)/fwupdate $(IDIR_FWUPDATE)/usr/sbin
	$(INSTALL_BIN) $(WRKBUILD)/fwvalidate $(IDIR_FWUPDATE)/usr/sbin
	$(SED) "s/@@DISK@@/$(ADK_TARGET_ROOTDEV)/g" \
		$(IDIR_FWUPDATE)/usr/sbin/fwupdate
	$(SED) "s/@@DISK@@/$(ADK_TARGET_ROOTDEV)/g" \
		$(IDIR_FWUPDATE)/usr/sbin/fwvalidate

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
