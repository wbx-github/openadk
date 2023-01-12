# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libwebp
PKG_VERSION:=		1.2.2
PKG_RELEASE:=		1
PKG_HASH:=		51e9297aadb7d9eb99129fe0050f53a11fcce38a0848fb2b0389e385ad93695e
PKG_DESCR:=		new image format for the web
PKG_SECTION:=		libs/image
PKG_BUILDDEP:=		cmake-host
PKG_URL:=		https://developers.google.com/speed/webp/
PKG_SITES:=		https://github.com/webmproject/libwebp/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=		v${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

CONFIG_STYLE:=		cmake

$(eval $(call PKG_template,LIBWEBP,libwebp,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

libwebp-install:

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
