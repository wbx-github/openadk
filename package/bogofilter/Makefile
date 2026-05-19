# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		bogofilter
PKG_VERSION:=		1.2.4
PKG_RELEASE:=		1
PKG_HASH:=		d2f2598d1300307209b7b1905cc0637d2d053c0a4701a8d44383867299578471
PKG_DESCR:=		mail filter software
PKG_SECTION:=		net/mail
PKG_NEEDS:=		c++
PKG_URL:=		http://bogofilter.sourceforge.net/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=bogofilter/}

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,BOGOFILTER,bogofilter,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=		ac_cv_func_memcmp_working=yes
CONFIGURE_ARGS+=	--without-libqdbm-prefix \
			--without-libiconv-prefix \
			--without-libdb-prefix \
			--with-included-gsl \
			--with-database=sqlite3 \
			--disable-static \
			--disable-transactions

bogofilter-install:
	${INSTALL_DIR} ${IDIR_BOGOFILTER}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/bogofilter \
		 ${IDIR_BOGOFILTER}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
