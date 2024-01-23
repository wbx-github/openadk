# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		python3
PKG_VERSION:=		3.11.6
PKG_RELEASE:=		1
PKG_HASH:=		0fab78fa7f133f4f38210c6260d90d7c0d5c7198446419ce057ec7ac2e6f5f38
PKG_DESCR:=		python3 scripting language
PKG_SECTION:=		dev/lang
PKG_DEPENDS:=		libffi zlib libexpat
PKG_BUILDDEP:=		python3-host libffi zlib expat
HOST_BUILDDEP:=		libffi-host libressl-host zlib-host bzip2-host ncurses-host sqlite-host
PKG_NEEDS:=		threads
PKG_URL:=		http://www.python.org/
PKG_SITES:=		http://legacy.python.org/ftp/python/${PKG_VERSION}/

PKG_FLAVOURS_PYTHON3:=	MOD_ZLIB MOD_BZ2 MOD_SQLITE MOD_GDBM
PKG_FLAVOURS_PYTHON3+=	MOD_NCURSES MOD_SSL MOD_READLINE
			
PKGFD_MOD_ZLIB:=	zlib support
PKGFB_MOD_ZLIB:=	zlib
PKGFS_MOD_ZLIB:=	zlib
PKGFD_MOD_BZ2:=		bzip2 support
PKGFB_MOD_BZ2:=		bzip2
PKGFS_MOD_BZ2:=		libbz2
PKGFD_MOD_SQLITE:=	sqlite support
PKGFB_MOD_SQLITE:=	sqlite
PKGFS_MOD_SQLITE:=	libsqlite
PKGFD_MOD_GDBM:=	gdbm support
PKGFB_MOD_GDBM:=	gdbm
PKGFS_MOD_GDBM:=	libgdbm
PKGFD_MOD_NCURSES:=	ncurses support
PKGFB_MOD_NCURSES:=	ncurses
PKGFS_MOD_NCURSES:=	libncurses
PKGFD_MOD_READLINE:=	readline support
PKGFB_MOD_READLINE:=	readline
PKGFS_MOD_READLINE:=	libreadline
PKGFD_MOD_SSL:=		ssl support
PKGFB_MOD_SSL:=		libressl
PKGFS_MOD_SSL:=		libressl

DISTFILES:=		Python-${PKG_VERSION}.tar.xz
WRKDIST=		${WRKDIR}/Python-${PKG_VERSION}

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

define PKG_mod_template

INSTALL_MODS_$${ADK_PACKAGE_${1}}+=    ${2}-install

${2}-install:
	${INSTALL_DIR} $$(IDIR_$(1))/usr/lib/python3.11/lib-dynload
	for m in ${2}; do \
		${INSTALL_DATA} $(WRKINST)/usr/lib/python3.11/lib-dynload/$$$${m}*.so $$(IDIR_$(1))/usr/lib/python3.11/lib-dynload ;\
	done
endef


$(eval $(call HOST_template,PYTHON3,python3,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,PYTHON3,python3,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

$(eval $(call PKG_template,PYTHON3_MOD_ZLIB,python3-mod-zlib,$(PKG_VERSION)-${PKG_RELEASE},${PKGFS_MOD_ZLIB},${PKGFD_MOD_ZLIB},${PKG_SECTION}))
$(eval $(call PKG_template,PYTHON3_MOD_BZ2,python3-mod-bz2,$(PKG_VERSION)-${PKG_RELEASE},${PKGFS_MOD_BZ2},${PKGFD_MOD_BZ2},${PKG_SECTION}))
$(eval $(call PKG_template,PYTHON3_MOD_SQLITE,python3-mod-sqlite,$(PKG_VERSION)-${PKG_RELEASE},${PKGFS_MOD_SQLITE},${PKGFD_MOD_SQLITE},${PKG_SECTION}))
$(eval $(call PKG_template,PYTHON3_MOD_GDBM,python3-mod-gdbm,$(PKG_VERSION)-${PKG_RELEASE},${PKGFS_MOD_GDBM},${PKGFD_MOD_GDBM},${PKG_SECTION}))
$(eval $(call PKG_template,PYTHON3_MOD_NCURSES,python3-mod-ncurses,$(PKG_VERSION)-${PKG_RELEASE},${PKGFS_MOD_NCURSES},${PKGFD_MOD_NCURSES},${PKG_SECTION}))
$(eval $(call PKG_template,PYTHON3_MOD_SSL,python3-mod-ssl,$(PKG_VERSION)-${PKG_RELEASE},${PKGFS_MOD_SSL},${PKGFD_MOD_SSL},${PKG_SECTION}))
$(eval $(call PKG_template,PYTHON3_MOD_READLINE,python3-mod-readline,$(PKG_VERSION)-${PKG_RELEASE},${PKGFS_MOD_READLINE},${PKGFD_MOD_READLINE},${PKG_SECTION}))

$(eval $(call PKG_mod_template,PYTHON3_MOD_ZLIB,zlib))
$(eval $(call PKG_mod_template,PYTHON3_MOD_BZ2,_bz2))
$(eval $(call PKG_mod_template,PYTHON3_MOD_SQLITE,_sqlite))
$(eval $(call PKG_mod_template,PYTHON3_MOD_GDBM,_gdbm))
$(eval $(call PKG_mod_template,PYTHON3_MOD_NCURSES,_curses))
$(eval $(call PKG_mod_template,PYTHON3_MOD_SSL,_ssl))
$(eval $(call PKG_mod_template,PYTHON3_MOD_READLINE,readline))

MAKE_ENV+=		HOSTPGEN=$(STAGING_HOST_DIR)/usr/bin/pgen3
FAKE_FLAGS+=		ENSUREPIP=no
CONFIGURE_ARGS:=	--with-system-expat \
			--disable-ipv6 \
			--with-build-python

CONFIGURE_ENV+=		ac_cv_have_long_long_format=yes \
			ac_cv_file__dev_ptmx=yes \
			ac_cv_file__dev_ptc=no

python3-install: ${INSTALL_MODS_y} ${INSTALL_MODS_m}
	${INSTALL_DIR} ${IDIR_PYTHON3}/usr/bin ${IDIR_PYTHON3}/usr/lib
	${INSTALL_DIR} ${IDIR_PYTHON3}/usr/lib/python3.11
	${INSTALL_DIR} ${IDIR_PYTHON3}/usr/include/python3.11
	${INSTALL_BIN} ${WRKINST}/usr/bin/python3 ${IDIR_PYTHON3}/usr/bin
	${CP} ${WRKINST}/usr/lib/libpython*.so* ${IDIR_PYTHON3}/usr/lib
	${CP} ${WRKINST}/usr/lib/python3.11/* ${IDIR_PYTHON3}/usr/lib/python3.11
	${CP} ${WRKINST}/usr/include/python3.11/pyconfig.h \
		 ${IDIR_PYTHON3}/usr/include/python3.11
	@-for i in zlib _bz2 _curses _ssl _gdbm _sqlite pyexpat readline; do \
		rm ${IDIR_PYTHON3}/usr/lib/python3.11/lib-dynload/$${i}*so; \
	done

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
