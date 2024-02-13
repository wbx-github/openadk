# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		serdisplib
PKG_VERSION:=		2.02
PKG_RELEASE:=		1
PKG_HASH:=		447b74007dc157b0378044245649850b26432b9185b6540ff681fcb0765c4d8b
PKG_DESCR:=		display drivers (serial, parallel, usb)
PKG_SECTION:=		sys/serial
PKG_DEPENDS:=		libusb-compat
PKG_BUILDDEP:=		libgd libusb-compat
PKG_URL:=		http://serdisplib.sourceforge.net
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=serdisplib/}

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,SERDISPLIB,serdisplib,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

INSTALL_STYLE:=		manual

CONFIGURE_ARGS+=	--enable-libusb
TARGET_CFLAGS+=		${TARGET_CPPFLAGS}

do-install:
	${INSTALL_DIR} ${IDIR_SERDISPLIB}/usr/lib
	${CP} ${WRKBUILD}/lib/libserdisp.so* ${IDIR_SERDISPLIB}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
