# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		lua
PKG_VERSION:=		5.4.8
PKG_RELEASE:=		1
PKG_HASH:=		4f18ddae154e793e46eeab727c59ef1c0c0c2b744e7b94219710d76f530629ae
PKG_DESCR:=		programming language interpreter
PKG_SECTION:=		dev/lang
PKG_DEPENDS:=		libreadline
PKG_BUILDDEP:=		readline
PKG_URL:=		http://www.lua.org/
PKG_SITES:=		http://www.lua.org/ftp/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		LUA LUAC
PKGSD_LUAC:=		lua bytecode compiler
PKGSN_LUAC:=		lua

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LUA,lua,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LUAC,luac,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_LUAC},${PKG_SECTION}))

CONFIG_STYLE:=		manual
MAKE_FLAGS+=		CFLAGS="${TARGET_CFLAGS} ${TARGET_CPPFLAGS} -DLUA_USE_LINUX -fPIC" \
			MYLDFLAGS="${TARGET_LDFLAGS} -ltinfo" \
			CC="${TARGET_CC}" LD="${TARGET_CROSS}ld" \
			AR="${TARGET_CROSS}ar rcu" \
			RANLIB="${TARGET_CROSS}ranlib"
XAKE_FLAGS+=		INSTALL_TOP="${WRKINST}/usr"
ALL_TARGET:=		linux

post-install:
	$(CP) ./files/lua.pc $(STAGING_TARGET_DIR)/usr/lib/pkgconfig

lua-install:
	${INSTALL_DIR} ${IDIR_LUA}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/lua ${IDIR_LUA}/usr/bin/

luac-install:
	${INSTALL_DIR} ${IDIR_LUAC}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/luac ${IDIR_LUAC}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
