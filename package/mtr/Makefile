# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		mtr
PKG_VERSION:=		0.96
PKG_RELEASE:=		1
PKG_HASH:=		73e6aef3fb6c8b482acb5b5e2b8fa7794045c4f2420276f035ce76c5beae632d
PKG_DESCR:=		traceroute/ping tool
PKG_SECTION:=		net/debug
PKG_DEPENDS:=		libncurses
PKG_BUILDDEP:=		ncurses
PKG_URL:=		http://www.bitwizard.nl/mtr/
PKG_SITES:=		https://github.com/traviscross/mtr/archive/refs/tags/

DISTFILES:=		v${PKG_VERSION}.tar.gz

PKG_LIBC_DEPENDS:=	uclibc-ng glibc

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,MTR,mtr,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

AUTOTOOL_STYLE:=	bootstrap
CONFIGURE_ENV+=		ac_cv_lib_resolv_res_mkquery=yes
CONFIGURE_ARGS+=	--without-gtk

mtr-install:
	${INSTALL_DIR} ${IDIR_MTR}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/mtr ${IDIR_MTR}/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
