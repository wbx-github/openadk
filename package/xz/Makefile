# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xz
PKG_VERSION:=		5.4.6
PKG_RELEASE:=		1
PKG_HASH:=		913851b274e8e1d31781ec949f1c23e8dbcf0ecf6e73a2436dc21769dd3e6f49
PKG_DESCR:=		compression utility
PKG_SECTION:=		app/archive
PKG_DEPENDS:=		libxz
PKG_SITES:=		https://distfiles.openadk.org/
PKG_LIBNAME:=		libxz
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.bz2

PKG_SUBPKGS:=		XZ LIBXZ
PKGSD_LIBXZ:=		xz compression library
PKGSC_LIBXZ:=		libs/comp

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,XZ,xz,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,XZ,xz,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))
$(eval $(call PKG_template,LIBXZ,libxz,$(PKG_VERSION)-$(PKG_RELEASE),$(PKGSS_LIBXZ),$(PKGSD_LIBXZ),$(PKGSC_LIBXZ),$(PKG_OPTS)))

HOST_CONFIGURE_ARGS+=	--disable-shared

xz-install:
	$(INSTALL_DIR) $(IDIR_XZ)/usr/bin
	$(CP) $(WRKINST)/usr/bin/* $(IDIR_XZ)/usr/bin

libxz-install:
	$(INSTALL_DIR) $(IDIR_LIBXZ)/usr/lib
	$(CP) $(WRKINST)/usr/lib/liblzma.so* $(IDIR_LIBXZ)/usr/lib

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
