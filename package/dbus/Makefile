# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		dbus
PKG_VERSION:=		1.10.20
PKG_RELEASE:=		2
PKG_HASH:=		e574b9780b5425fde4d973bb596e7ea0f09e00fe2edd662da9016e976c460b48
PKG_DESCR:=		desktop bus daemon
PKG_SECTION:=		sys/misc
PKG_DEPENDS:=		libdbus libexpat
PKG_BUILDDEP:=		expat util-linux
PKG_NEEDS:=		threads
PKG_URL:=		http://dbus.freedesktop.org/
PKG_SITES:=		https://dbus.freedesktop.org/releases/dbus/
PKG_LIBNAME:=		libdbus
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		DBUS LIBDBUS
PKGSD_LIBDBUS:=		DBUS library
PKGSC_LIBDBUS:=		libs/misc
PKGSS_LIBDBUS:=		libexpat libuuid

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,DBUS,dbus,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIBDBUS,libdbus,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_LIBDBUS},${PKGSD_LIBDBUS},${PKGSC_LIBDBUS},${PKG_OPTS}))

TARGET_LDFLAGS+=	-luuid

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--disable-systemd \
			--disable-tests \
			--disable-asserts \
			--enable-abstract-sockets \
			--with-dbus-user=dbus \
			--with-system-socket=/run/dbus/system_bus_socket \
			--with-system-pid-file=/run/dbus/dbus.pid \
			--disable-verbose-mode \
			--disable-kqueue \
			--disable-selinux \
			--disable-libaudit \
			--disable-doxygen-docs \
			--disable-xml-docs \
			--without-x

pre-install:
	${INSTALL_DIR} $(STAGING_TARGET_DIR)/usr/include/dbus-1.0/dbus
	$(CP) $(WRKBUILD)/dbus/dbus-arch-deps.h \
		$(STAGING_TARGET_DIR)/usr/include/dbus-1.0/dbus

libdbus-install:
	${INSTALL_DIR} ${IDIR_LIBDBUS}/usr/lib
	${CP} ${WRKINST}/usr/lib/libdbus-1.so* ${IDIR_LIBDBUS}/usr/lib

dbus-install:
	${INSTALL_DIR} ${IDIR_DBUS}/etc ${IDIR_DBUS}/usr/share \
		${IDIR_DBUS}/usr/bin ${IDIR_DBUS}/usr/libexec
	${INSTALL_DIR} ${IDIR_DBUS}/var/lib/dbus ${IDIR_DBUS}/run/dbus
	(cd ${IDIR_DBUS}/var/lib/dbus; ln -sf ../../../etc/machine-id .)
	${INSTALL_BIN} ${WRKINST}/usr/libexec/dbus-daemon-launch-helper \
		${IDIR_DBUS}/usr/libexec/
	${CP} ${WRKINST}/etc/dbus-1 ${IDIR_DBUS}/etc
	${CP} ${WRKINST}/usr/share/dbus-1 ${IDIR_DBUS}/usr/share
	${CP} ${WRKINST}/usr/bin/dbus-* ${IDIR_DBUS}/usr/bin
	# workaround for dev subpackage
	${INSTALL_DIR} $(IDIR_DBUS_DEV)/usr/include/dbus-1.0/dbus
	$(CP) $(WRKBUILD)/dbus/dbus-arch-deps.h \
		$(IDIR_DBUS_DEV)/usr/include/dbus-1.0/dbus

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
