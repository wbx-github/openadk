# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libxcrypt
PKG_VERSION:=		4.5.2
PKG_RELEASE:=		1
PKG_HASH:=		d99b548636894641e6b29b58ef592cab692e75672155a938c3209c187a872e1e
PKG_DESCR:=		crypt library
PKG_SECTION:=		libs/crypto
PKG_SITES:=		https://github.com/besser82/libxcrypt/archive/refs/tags/
PKG_OPTS:=		dev

PKG_LIBC_DEPENDS:=	glibc

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBXCRYPT,libxcrypt,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

AUTOTOOL_STYLE:=	autogen

libxcrypt-install:
	$(INSTALL_DIR) $(IDIR_LIBXCRYPT)/usr/lib
	$(CP) $(WRKINST)/usr/lib/lib*crypt*.so* \
		$(IDIR_LIBXCRYPT)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
