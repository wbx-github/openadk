# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		tmsnc
PKG_VERSION:=		0.3.2
PKG_RELEASE:=		2
PKG_HASH:=		7f54ba3974f45c0787b6d62d0d62ce352ddbf95419123b98b4969b97d3dfed23
PKG_DESCR:=		textbased msn client
PKG_SECTION:=		app/chat
PKG_DEPENDS:=		libopenssl
PKG_BUILDDEP:=		openssl
PKG_URL:=		http://tmsnc.sourceforge.net/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=tmsnc/}

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,TMSNC,tmsnc,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_LDFLAGS+=	-ltinfow

CONFIGURE_ARGS+=	--with-libiconv-prefix=${STAGING_TARGET_DIR}/usr \
			--with-openssl=${STAGING_TARGET_DIR}/usr \
			--with-ncurses=${STAGING_TARGET_DIR}

tmsnc-install:
	${INSTALL_DIR} ${IDIR_TMSNC}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/tmsnc ${IDIR_TMSNC}/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
