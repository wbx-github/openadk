# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		lftp
PKG_VERSION:=		4.9.3
PKG_RELEASE:=		1
PKG_HASH:=		96e7199d7935be33cf6b1161e955b2aab40ab77ecdf2a19cea4fc1193f457edc
PKG_DESCR:=		ftp and http client
PKG_SECTION:=		net/http
PKG_DEPENDS:=		libncurses libexpat
PKG_DEPENDS+=		zlib libreadline
PKG_BUILDDEP:=		ncurses expat readline zlib
PKG_NEEDS:=		c++
PKG_URL:=		http://lftp.yar.ru/
PKG_SITES:=		http://lftp.yar.ru/ftp/

PKG_CHOICES_LFTP:=	WITH_OPENSSL WITH_GNUTLS WITHOUT_SSL
PKGCD_WITH_OPENSSL:=	use openssl for crypto
PKGCS_WITH_OPENSSL:=	libopenssl ca-certificates
PKGCB_WITH_OPENSSL:=	openssl
PKGCD_WITH_GNUTLS:=	use gnutls for crypto
PKGCS_WITH_GNUTLS:=	libgnutls ca-certificates
PKGCB_WITH_GNUTLS:=	gnutls
PKGCD_WITHOUT_SSL:=	use no ssl

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LFTP,lftp,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_LDFLAGS+=	-lncursesw

CONFIGURE_ARGS+=	--with-readline="$(STAGING_TARGET_DIR)/usr" \
			--with-zlib="$(STAGING_TARGET_DIR)/usr" \
			--with-expat="$(STAGING_TARGET_DIR)/usr"

ifeq (${ADK_PACKAGE_LFTP_WITHOUT_SSL},y)
CONFIGURE_ARGS+=	--without-openssl \
			--without-gnutls
endif
ifeq (${ADK_PACKAGE_LFTP_WITH_GNUTLS},y)
CONFIGURE_ARGS+=	--without-openssl \
			--with-gnutls
endif
ifeq (${ADK_PACKAGE_LFTP_WITH_OPENSSL},y)
CONFIGURE_ARGS+=	--with-openssl="$(STAGING_TARGET_DIR)/usr" \
			--without-gnutls
endif

lftp-install:
	$(INSTALL_DIR) $(IDIR_LFTP)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/lftp \
		$(IDIR_LFTP)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
