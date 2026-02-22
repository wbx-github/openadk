# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libfm-extra
PKG_VERSION:=		1.3.2
PKG_RELEASE:=		1
PKG_HASH:=		a5042630304cf8e5d8cff9d565c6bd546f228b48c960153ed366a34e87cad1e5
PKG_DESCR:=		lxde fm extra library
PKG_SECTION:=		x11/lxde
PKG_URL:=		https://lxde.org/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=pcmanfm/files/}
PKG_OPTS:=		dev

DISTFILES:=		libfm-$(PKG_VERSION).tar.xz
WRKDIST=                ${WRKDIR}/libfm-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBFM_EXTRA,libfm-extra,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIGURE_ARGS+=	--with-extra-only --with-gtk=no

libfm-extra-install:
	$(INSTALL_DIR) $(IDIR_LIBFM_EXTRA)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libfm-extra*.so* \
		$(IDIR_LIBFM_EXTRA)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
