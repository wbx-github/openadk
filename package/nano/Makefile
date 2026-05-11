# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		nano
PKG_VERSION:=		9.0
PKG_RELEASE:=		1
PKG_HASH:=		9f384374b496110a25b73ad5a5febb384783c6e3188b37063f677ac908013fde
PKG_DESCR:=		enhanced clone of the pico editor
PKG_SECTION:=		app/editor
PKG_DEPENDS:=		libncurses
PKG_BUILDDEP:=		ncurses
PKG_URL:=		http://www.nano-editor.org/
PKG_SITES:=		https://www.nano-editor.org/dist/v9/

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,NANO,nano,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=		ac_cv_header_regex_h=no
CONFIGURE_ARGS+=	--enable-nanorc \
			--enable-tiny \
			--enable-utf8 \
			--disable-glibtest \
			--disable-color \
			--without-slang \
			--disable-browser \
			--disable-help \
			--disable-mouse \
			--disable-speller \
			--disable-operatingdir \
			--enable-multibuffer

nano-install:
	${INSTALL_DIR} ${IDIR_NANO}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/nano ${IDIR_NANO}/usr/bin/
	${INSTALL_DIR} ${IDIR_NANO}/etc
	$(INSTALL_DATA) ./files/nanorc ${IDIR_NANO}/etc/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
