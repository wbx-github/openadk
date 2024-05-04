# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		openocd
PKG_VERSION:=		0.12.0
PKG_RELEASE:=		1
PKG_HASH:=		af254788be98861f2bd9103fe6e60a774ec96a8c374744eef9197f6043075afa
PKG_DESCR:=		jtag flash and debugging utility
PKG_SECTION:=		dev/tools
HOST_BUILDDEP:=		libusb-host
PKG_URL:=		http://openocd.org/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=openocd/}

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.bz2

PKG_CFLINE_OPENOCD:=	depends on ADK_HOST_ONLY

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,OPENOCD,openocd,$(PKG_VERSION)-${PKG_RELEASE}))

HOST_STYLE:=		auto
HOST_CFLAGS+=		-I$(STAGING_HOST_DIR)/usr/include/libusb-1.0
HOST_CONFIGURE_ARGS+=	--with-jim-shared=no \
			--disable-shared

openocd-hostinstall:
	cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_FAKE_FLAGS} ${HOST_INSTALL_TARGET} $(MAKE_TRACE)

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
