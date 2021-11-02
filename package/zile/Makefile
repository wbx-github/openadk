# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		zile
PKG_VERSION:=		2.6.2
PKG_RELEASE:=		1
PKG_HASH:=		77eb7daff3c98bdc88daa1ac040dccca72b81dc32fc3166e079dd7a63e42c741
PKG_DESCR:=		tiny emacs clone
PKG_SECTION:=		app/editor
PKG_DEPENDS:=		libgc glib libgee libmount libblkid
PKG_BUILDDEP:=		libgc glib libgee
PKG_LIBC_DEPENDS:=	glibc
PKG_URL:=		http://www.gnu.org/software/zile/
PKG_SITES:=		${MASTER_SITE_GNU:=zile/}

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ZILE,zile,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autoreconf
TARGET_LDFLAGS+=	-ltinfo -lrt

zile-install:
	$(INSTALL_DIR) $(IDIR_ZILE)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/zile \
		$(IDIR_ZILE)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
