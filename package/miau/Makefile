# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		miau
PKG_VERSION:=		0.6.6
PKG_RELEASE:=		1
PKG_HASH:=		bfa023436714f0c8128ac996cc9d599a6baa04179aadf1a1ec386653bfe3992f
PKG_DESCR:=		irc-bouncer/proxy
PKG_SECTION:=		app/chat
PKG_URL:=		http://miau.sourceforge.net/
PKG_SITES:=		https://sourceforge.net/projects/miau/files/miau/$(PKG_VERSION)/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,MIAU,miau,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=         ac_cv_func_malloc_0_nonnull=yes \
			ac_cv_func_realloc_0_nonnull=yes
CONFIGURE_ARGS+=	--enable-automode \
			--enable-releasenick \
			--enable-uptime \
			--enable-privlog \
			--enable-onconnect

miau-install:
	${INSTALL_DIR} ${IDIR_MIAU}/usr/bin ${IDIR_MIAU}/etc/miau
	${INSTALL_BIN} ${WRKINST}/usr/bin/miau ${IDIR_MIAU}/usr/bin/
	${INSTALL_DATA} ./files/miaurc ${IDIR_MIAU}/etc/miau/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
