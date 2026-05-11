# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		fetchmail
PKG_VERSION:=		6.6.4
PKG_RELEASE:=		1
PKG_HASH:=		efe01690d22bda359a579c77e2b0072658a092bff490ec0478a212c6b7d0eb70
PKG_DESCR:=		fetch mail from a pop3 or imap server
PKG_SECTION:=		net/mail
PKG_URL:=		http://www.fetchmail.info
PKG_SITES:=		https://sourceforge.net/projects/fetchmail/files/branch_6.6/

PKG_CHOICES_FETCHMAIL:=	WITH_OPENSSL WITHOUT_SSL
PKGCD_WITH_OPENSSL:=	use libopenssl for crypto
PKGCB_WITH_OPENSSL:=	openssl
PKGCS_WITH_OPENSSL:=	libopenssl ca-certificates
PKGCD_WITHOUT_SSL:=	use no ssl

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,FETCHMAIL,fetchmail,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--without-hesiod

ifeq (${ADK_PACKAGE_FETCHMAIL_WITH_OPENSSL},y)
CONFIGURE_ARGS+=	--with-ssl='${STAGING_TARGET_DIR}/usr'
endif
ifeq (${ADK_PACKAGE_FETCHMAIL_WITHOUT_SSL},y)
CONFIGURE_ARGS+=	--without-ssl
endif

fetchmail-install:
	${INSTALL_DIR} ${IDIR_FETCHMAIL}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/fetchmail \
		 ${IDIR_FETCHMAIL}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
