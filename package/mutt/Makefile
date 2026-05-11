# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		mutt
PKG_VERSION:=		2.2.15
PKG_RELEASE:=		1
PKG_HASH:=		a51686104e4203f4c2a3b176527be3b95d08e808e94fd2dcadb7c30566bf894d
PKG_DESCR:=		mail client for console
PKG_SECTION:=		net/mail
PKG_DEPENDS:=		libncurses
PKG_BUILDDEP:=		ncurses
PKG_URL:=		http://www.mutt.org/
PKG_SITES:=		ftp://ftp.mutt.org/pub/mutt/

PKG_CHOICES_MUTT:=	WITH_OPENSSL WITHOUT_SSL
PKGCD_WITH_OPENSSL:=	use openssl for crypto
PKGCB_WITH_OPENSSL:=	openssl
PKGCS_WITH_OPENSSL:=	libopenssl ca-certificates
PKGCD_WITHOUT_SSL:=	use no ssl

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,MUTT,mutt,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--with-homespool="~/Maildir" \
			--with-curses="$(STAGING_TARGET_DIR)/usr" \
			--enable-pop \
			--enable-imap \
			--enable-smtp \
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
