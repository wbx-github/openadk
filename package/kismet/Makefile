# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		kismet
PKG_VERSION:=		2023-07-R1
PKG_RELEASE:=		1
PKG_HASH:=		f08548e26ca65fa1e567b1debbea1ca4d0e7206bddb96a4f639c90171873e8f7
PKG_DESCR:=		wireless network detector, sniffer, and intrusion detection system
PKG_SECTION:=		net/wifi
PKG_BUILDDEP:=		libpcap ncurses libwebsockets protobuf protobuf-c sqlite
PKG_DEPENDS:=		libpcap libncurses libwebsockets protobuf protobuf-c libsqlite
PKG_NEEDS:=		threads
PKG_URL:=		http://www.kismetwireless.net/
PKG_SITES:=		https://www.kismetwireless.net/code/

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,KISMET,kismet,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_LDFLAGS+=	-lpthread -ltinfo
CONFIGURE_ARGS+=	--sysconfdir=/etc/kismet \
			--disable-libusb \
			--disable-python-tools \
			--disable-wifi-coconut

kismet-install:
	${INSTALL_DIR} ${IDIR_KISMET}/usr/bin/
	${INSTALL_BIN} ${WRKINST}/usr/bin/kismet \
		${IDIR_KISMET}/usr/bin/kismet
	${INSTALL_DIR} ${IDIR_KISMET}/etc/kismet
	${CP} ${WRKINST}/etc/kismet/kismet*.conf \
		${IDIR_KISMET}/etc/kismet/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
