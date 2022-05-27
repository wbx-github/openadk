# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		mutt
PKG_VERSION:=		2.2.3
PKG_RELEASE:=		1
PKG_HASH:=		978addcdab454f447ed7d1de84b5767e714c30714285bf82e4a1745071d18d89
PKG_DESCR:=		mail client for console
PKG_SECTION:=		net/mail
PKG_DEPENDS:=		libncurses
PKG_BUILDDEP:=		ncurses
PKG_URL:=		http://www.mutt.org/
PKG_SITES:=		ftp://ftp.mutt.org/pub/mutt/

PKG_CHOICES_MUTT:=	WITH_LIBRESSL WITHOUT_SSL
PKGCD_WITH_LIBRESSL:=	use libressl for crypto
PKGCB_WITH_LIBRESSL:=	libressl
PKGCS_WITH_LIBRESSL:=	libressl ca-certificates
PKGCD_WITHOUT_SSL:=	use no ssl

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,MUTT,mutt,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_LDFLAGS+=	-ltinfo
CONFIGURE_ARGS+=	--with-homespool="~/Maildir" \
			--with-curses="$(STAGING_TARGET_DIR)/usr" \
			--enable-pop \
			--enable-imap \
			--disable-doc

ifeq ($(ADK_PACKAGE_MUTT_WITHOUT_SSL),y)
CONFIGURE_ARGS+=	--without-ssl
else
CONFIGURE_ARGS+=	--with-ssl
endif

mutt-install:
	${INSTALL_DIR} ${IDIR_MUTT}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/mutt ${IDIR_MUTT}/usr/bin/
ifeq (${ADK_PACKAGE_GPG},y)
	${INSTALL_BIN} ${WRKINST}/usr/bin/pgpewrap ${IDIR_MUTT}/usr/bin/
endif

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
