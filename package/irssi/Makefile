# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		irssi
PKG_VERSION:=		1.4.5
PKG_RELEASE:=		1
PKG_HASH:=		72a951cb0ad622785a8962801f005a3a412736c7e7e3ce152f176287c52fe062
PKG_DESCR:=		irc text client
PKG_SECTION:=		app/chat
PKG_DEPENDS:=		glib libncurses libopenssl
PKG_BUILDDEP:=		glib ncurses openssl
PKG_URL:=		http://www.irssi.org/
PKG_SITES:=		https://github.com/irssi/irssi/releases/download/$(PKG_VERSION)/

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,IRSSI,irssi,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_LDFLAGS+=	-latomic
CONFIGURE_ARGS+=	--with-perl=no \
			--with-textui \
			--without-bot \
			--without-proxy

irssi-install:
	${INSTALL_DIR} ${IDIR_IRSSI}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/irssi ${IDIR_IRSSI}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
