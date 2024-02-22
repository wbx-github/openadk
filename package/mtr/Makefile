# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		mtr
PKG_VERSION:=		0.95
PKG_RELEASE:=		1
PKG_HASH:=		12490fb660ba5fb34df8c06a0f62b4f9cbd11a584fc3f6eceda0a99124e8596f
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

TARGET_LDFLAGS+=	-ltinfo
AUTOTOOL_STYLE:=	bootstrap
CONFIGURE_ENV+=		ac_cv_lib_resolv_res_mkquery=yes
CONFIGURE_ARGS+=	--without-gtk

mtr-install:
	${INSTALL_DIR} ${IDIR_MTR}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/mtr ${IDIR_MTR}/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
