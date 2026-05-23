# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		bogofilter
PKG_VERSION:=		1.3.0.rc1
PKG_RELEASE:=		1
PKG_HASH:=		0bc4b8300a106e7c5a4110c052272cfe64bb096ec5e7f552a44c3f41b574b29b
PKG_DESCR:=		mail filter software
PKG_SECTION:=		net/mail
PKG_NEEDS:=		c++
PKG_URL:=		http://bogofilter.sourceforge.net/
PKG_SITES:=		https://sourceforge.net/projects/bogofilter/files/bogofilter-current/bogofilter-1.3.0.beta/

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
