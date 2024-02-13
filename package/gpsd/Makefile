# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		gpsd
PKG_VERSION:=		3.25
PKG_RELEASE:=		1
PKG_HASH:=		b368b6a305e3f7a6382d23a0cbfc1d78923060b6b7f54cf7987a73c7b4a9afc2
PKG_DESCR:=		interface daemon for gps receivers
PKG_SECTION:=		sys/hw
PKG_BUILDDEP:=		scons-host ncurses
PKG_NEEDS:=		threads
PKG_URL:=		http://catb.org/gpsd/
PKG_SITES:=		http://download-mirror.savannah.gnu.org/releases/gpsd/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		GPSD GPSD_CLIENTS
PKGSD_GPSD_CLIENTS:=	gps client utilities

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,GPSD,gpsd,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,GPSD_CLIENTS,gpsd-clients,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_GPSD_CLIENTS},${PKG_SECTION}))

TARGET_CPPFLAGS:=
CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

do-install:
	(cd $(WRKBUILD); env PATH='$(TARGET_PATH)' CCFLAGS='' DESTDIR='$(WRKINST)' \
		$(STAGING_HOST_DIR)/usr/bin/python3 $(STAGING_HOST_DIR)/usr/bin/scons install prefix=/usr platform=linux python=no chrpath=no bluez=no usb=no libgpsmm=no)

gpsd-install:
	${INSTALL_DIR} ${IDIR_GPSD}/usr/lib ${IDIR_GPSD}/usr/sbin
	${CP} ${WRKINST}/usr/lib/libgps.so* ${IDIR_GPSD}/usr/lib
	${CP} ${WRKINST}/usr/sbin/gpsd ${IDIR_GPSD}/usr/sbin

gpsd-clients-install:
	${INSTALL_DIR} ${IDIR_GPSD_CLIENTS}/usr/bin
	${CP} ${WRKINST}/usr/bin/{cgps,gpxlogger} \
		${IDIR_GPSD_CLIENTS}/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
