# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libesmtp
PKG_VERSION:=		1.1.0
PKG_RELEASE:=		1
PKG_HASH:=		32bc3614ca12d21c7d933f32d43410e8744b6f91fdca7732da9877a385e4e6c3
PKG_DESCR:=		implements the client side of the smtp protocol
PKG_SECTION:=		libs/net
PKG_URL:=		https://libesmtp.github.io/index.html
PKG_SITES:=		https://github.com/libesmtp/libESMTP/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v${PKG_VERSION}.tar.gz
WRKDIST=		$(WRKDIR)/libESMTP-$(PKG_VERSION)

PKG_CHOICES_LIBESMTP:=	WITH_OPENSSL WITHOUT_SSL
PKGCD_WITH_OPENSSL:=	use openssl for crypto
PKGCB_WITH_OPENSSL:=	openssl
PKGCS_WITH_OPENSSL:=	libopenssl
PKGCD_WITHOUT_SSL:=	use no ssl

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBESMTP,libesmtp,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

libesmtp-install:
	$(INSTALL_DIR) $(IDIR_LIBESMTP)/usr/lib/esmtp-plugins-6.2.0
	$(CP) $(WRKINST)/usr/lib/libesmtp.so* $(IDIR_LIBESMTP)/usr/lib/
	$(CP) $(WRKINST)/usr/lib/esmtp-plugins-6.2.0/*.so \
		$(IDIR_LIBESMTP)/usr/lib/esmtp-plugins-6.2.0/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
