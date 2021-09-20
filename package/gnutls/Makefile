# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		gnutls
PKG_VERSION:=		3.6.16
PKG_RELEASE:=		1
PKG_HASH:=		1b79b381ac283d8b054368b335c408fedcb9b7144e0c07f531e3537d4328f3b3
PKG_DESCR:=		transport layer security library
PKG_SECTION:=		libs/crypto
PKG_DEPENDS:=		libgcrypt libtasn1 zlib libnettle libgmp libunistring
PKG_BUILDDEP:=		libgcrypt liblzo libtasn1
PKG_BUILDDEP+=		zlib ncurses libnettle libunistring
PKG_URL:=		http://www.gnutls.org/
PKG_SITES:=		https://www.gnupg.org/ftp/gcrypt/gnutls/v3.6/
PKG_LIBNAME:=		libgnutls
PKG_OPTS:=		dev

PKG_SUBPKGS:=		LIBGNUTLS GNUTLS_UTILS
PKGSD_GNUTLS_UTILS:=	transport layer security utilities
PKGSS_GNUTLS_UTILS:=	libgnutls libgnutls-extra
PKGSC_GNUTLS_UTILS:=	app/crypto
PKGSC_LIBGNUTLS:=	libs/crypto

PKG_FLAVOURS_LIBGNUTLS:=WITH_CRYPTODEV
PKGFD_WITH_CRYPTODEV:=	enable support for cryptodev-linux
PKGFB_WITH_CRYPTODEV:=	cryptodev-linux

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBGNUTLS,libgnutls,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKGSC_LIBGNUTLS),$(PKG_OPTS)))
$(eval $(call PKG_template,GNUTLS_UTILS,gnutls-utils,$(PKG_VERSION)-$(PKG_RELEASE),$(PKGSS_GNUTLS_UTILS),$(PKGSD_GNUTLS_UTILS),$(PKGSC_GNUTLS_UTILS)))

ifneq ($(ADK_PACKAGE_LIBGNUTLS_WITH_CRYPTODEV),)
CONFIGURE_ARGS+= 	--enable-cryptodev
endif

TARGET_LDFLAGS+=	-pthread
CONFIGURE_ARGS+=	--disable-rpath \
			--disable-doc \
			--disable-tests \
			--disable-seccomp-tests \
			--with-libunistring-prefix='$(STAGING_TARGET_DIR)/usr' \
			--without-libz-prefix \
			--without-p11-kit
CONFIGURE_ENV+=		ac_cv_prog_AR='$(TARGET_CROSS)ar'

libgnutls-install:
	$(INSTALL_DIR) $(IDIR_LIBGNUTLS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgnutls.so* $(IDIR_LIBGNUTLS)/usr/lib

gnutls-utils-install:
	$(INSTALL_DIR) $(IDIR_GNUTLS_UTILS)/usr/bin
	$(CP) $(WRKINST)/usr/bin/{{cert,srp,psk}tool,gnutls-{cli,serv}} \
	    $(IDIR_GNUTLS_UTILS)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
