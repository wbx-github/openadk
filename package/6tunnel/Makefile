# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		6tunnel
PKG_VERSION:=		0.14
PKG_RELEASE:=		1
PKG_HASH:=		6945312793079408f1ab40071cee68e70158a23560145f1d424a3eb16227f235
PKG_DESCR:=		ipv4/ipv6 tunnel proxy
PKG_SECTION:=		net/ipv6
PKG_URL:=		https://github.com/wojtekka/6tunnel
PKG_SITES:=		https://github.com/wojtekka/6tunnel/releases/download/0.14/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,6TUNNEL,6tunnel,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autoconf

6tunnel-install:
	$(INSTALL_DIR) $(IDIR_6TUNNEL)/usr/sbin
	$(INSTALL_BIN) $(WRKBUILD)/6tunnel $(IDIR_6TUNNEL)/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
