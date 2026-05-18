# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		mc
PKG_VERSION:=		4.8.33
PKG_RELEASE:=		1
PKG_HASH:=		cae149d42f844e5185d8c81d7db3913a8fa214c65f852200a9d896b468af164c
PKG_DESCR:=		norton commander clone
PKG_SECTION:=		sys/misc
PKG_DEPENDS:=		glib libncurses libssh2
PKG_BUILDDEP:=		glib ncurses libssh2
PKG_URL:=		http://www.midnight-commander.org/
PKG_SITES:=		http://ftp.midnight-commander.org/
PKG_NOPARALLEL:=	1

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,MC,mc,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--enable-charset \
			--disable-background \
			--disable-glibtest \
			--disable-netcode \
			--without-libiconv-prefix \
			--without-x \
			--enable-vfs \
			--enable-vfs-sftp \
			--with-mcfs \
			--without-samba \
			--without-gpm-mouse \
			--with-configdir=/etc \
			--without-ext2undel \
			--with-subshell \
			--with-screen=ncurses \
			--disable-silent-rules
CONFIGURE_ENV+=		mc_cv_have_zipinfo=yes \
			am_cv_func_iconv=no

mc-install:
	${INSTALL_DIR} ${IDIR_MC}/etc/mc
	${INSTALL_DIR} ${IDIR_MC}/usr/bin
	${INSTALL_DIR} ${IDIR_MC}/usr/share/mc
	${CP} ${WRKINST}/usr/share/mc/* ${IDIR_MC}/usr/share/mc
	${INSTALL_BIN} ${WRKINST}/usr/bin/mc ${IDIR_MC}/usr/bin/
	cd ${IDIR_MC}/usr/bin && ln -fs mc mcedit && ln -fs mc mcview
	cd ${WRKINST}/etc/mc && ${CP} mcedit.menu sfs.ini \
	    mc.menu ${IDIR_MC}/etc/mc/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
