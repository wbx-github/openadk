# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		weechat
PKG_VERSION:=		4.2.1
PKG_RELEASE:=		1
PKG_HASH:=		253ddf086f6c845031a2dd294b1552851d6b04cc08a2f9da4aedfb3e2f91bdcd
PKG_DESCR:=		lightweight irc client
PKG_SECTION:=		app/chat
PKG_DEPENDS:=		libncurses zlib libcurl libgcrypt libgnutls
PKG_BUILDDEP:=		cmake-host ncurses zlib curl libgcrypt gnutls
PKG_URL:=		http://www.weechat.org/
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
			-DGCRYPT_LDFLAGS="-L$(STAGING_TARGET_DIR)/usr/lib -ltinfo -lgcrypt" \
			-DGCRYPT_CFLAGS="-I$(STAGING_TARGET_DIR)/usr/include" \

weechat-install:
	${INSTALL_DIR} ${IDIR_WEECHAT}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/weechat-curses \
		${IDIR_WEECHAT}/usr/bin/weechat

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
