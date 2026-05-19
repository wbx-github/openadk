# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		weechat
PKG_VERSION:=		4.9.0
PKG_RELEASE:=		1
PKG_HASH:=		7cbb9b27f25a7d2f1d8c426a08f8e625eefbc1d3e59bbf775925444f72394b6f
PKG_DESCR:=		lightweight irc client
PKG_SECTION:=		app/chat
PKG_DEPENDS:=		libncurses zlib libcurl libgcrypt libgnutls
PKG_BUILDDEP:=		cmake-host ncurses zlib curl libgcrypt gnutls
PKG_URL:=		https://www.weechat.org/
PKG_SITES:=		https://weechat.org/files/src/

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,WEECHAT,weechat,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=          cmake
CMAKE_FLAGS+=		-DENABLE_PERL=OFF \
			-DENABLE_PYTHON=OFF \
			-DENABLE_LUA=OFF \
			-DENABLE_RUBY=OFF \
			-DENABLE_PHP=OFF \
			-DENABLE_TCL=OFF \
			-DENABLE_GUILE=OFF \
			-DENABLE_SPELL=OFF \
			-DENABLE_NLS=OFF \
			-DENABLE_CJSON=OFF \
			-DGCRYPT_LDFLAGS="-L$(STAGING_TARGET_DIR)/usr/lib -lgcrypt" \
			-DGCRYPT_CFLAGS="-I$(STAGING_TARGET_DIR)/usr/include" \

weechat-install:
	${INSTALL_DIR} ${IDIR_WEECHAT}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/weechat-curses \
		${IDIR_WEECHAT}/usr/bin/weechat

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
