# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		lvm
PKG_VERSION:=		2.02.188
PKG_RELEASE:=		1
PKG_HASH:=		7101e8b0816ad77e4390fed9749a090214ba520061cd083437871e19e50cc9bd
PKG_DESCR:=		logical volume management
PKG_SECTION:=		sys/fs
PKG_DEPENDS:=		libdevmapper libncurses libaio
PKG_KDEPENDS:=		blk-dev-dm
PKG_BUILDDEP:=		ncurses util-linux libaio
PKG_NEEDS:=		threads
PKG_URL:=		http://sourceware.org/lvm2/
PKG_SITES:=		http://ftp.gwdg.de/pub/linux/sources.redhat.com/lvm2/
PKG_LIBNAME:=		libdevmapper
PKG_OPTS:=		dev

PKG_SUBPKGS:=		LVM DEVICE_MAPPER LIBDEVMAPPER
PKGSD_DEVICE_MAPPER:=	device-mapper utility
PKGSS_DEVICE_MAPPER:=	libdevmapper
PKGSD_LIBDEVMAPPER:=	device-mapper library
PKGSC_LIBDEVMAPPER:=	libs/misc

DISTFILES:=		LVM2.${PKG_VERSION}.tgz
WRKDIST=		${WRKDIR}/LVM2.${PKG_VERSION}

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LVM,${PKG_NAME},${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,DEVICE_MAPPER,device-mapper,${PKG_VERSION}-${PKG_RELEASE},,${PKGSD_DEVICE_MAPPER},${PKG_SECTION}))
$(eval $(call PKG_template,LIBDEVMAPPER,libdevmapper,${PKG_VERSION}-${PKG_RELEASE},,${PKGSD_LIBDEVMAPPER},${PKGSC_LIBDEVMAPPER},${PKG_OPTS}))

ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
CONFIGURE_ARGS+=	--enable-static_link
endif

CONFIGURE_ARGS+=	--with-user="" --with-group="" \
			--with-optimisation="" \
			--disable-testing \
			--disable-blkid_wiping \
			--disable-udev-systemd-background-jobs \
			--with-symvers=no \
			--with-lvm1=none
CONFIGURE_ENV+=		ac_cv_flag_HAVE_PIE=no \
			ac_cv_func_malloc_0_nonnull=yes \
			ac_cv_func_realloc_0_nonnull=yes

lvm-install:
	${INSTALL_DIR} ${IDIR_LVM}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/lvm \
		${IDIR_LVM}/usr/sbin

libdevmapper-install:
	${INSTALL_DIR} ${IDIR_LIBDEVMAPPER}/usr/lib
	${CP} ${WRKINST}/usr/lib/libdevmapper.so* \
		${IDIR_LIBDEVMAPPER}/usr/lib

device-mapper-install:
	${INSTALL_DIR} ${IDIR_DEVICE_MAPPER}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/dmsetup \
		${IDIR_DEVICE_MAPPER}/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
