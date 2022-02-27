# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libcec
PKG_VERSION:=		6.0.2
PKG_RELEASE:=		1
PKG_HASH:=		090696d7a4fb772d7acebbb06f91ab92e025531c7c91824046b9e4e71ecb3377
PKG_DESCR:=		control your device with your tv remote control
PKG_SECTION:=		libs/video
PKG_DEPENDS:=		libudev p8-platform
PKG_BUILDDEP:=		eudev cmake-host p8-platform
PKG_URL:=		http://libcec.pulse-eight.com/
PKG_SITES:=		https://github.com/Pulse-Eight/libcec/archive/refs/tags/
PKG_OPTS:=		dev

PKG_DEPENDS_RASPBERRY_PI4:=	bcm28xx-vc
PKG_BUILDDEP_RASPBERRY_PI4:=	bcm28xx-vc
PKG_DEPENDS_RASPBERRY_PI3:=	bcm28xx-vc
PKG_BUILDDEP_RASPBERRY_PI3:=	bcm28xx-vc
PKG_DEPENDS_RASPBERRY_PI2:=	bcm28xx-vc
PKG_BUILDDEP_RASPBERRY_PI2:=	bcm28xx-vc
PKG_DEPENDS_RASPBERRY_PI:=	bcm28xx-vc
PKG_BUILDDEP_RASPBERRY_PI:=	bcm28xx-vc
PKG_SYSTEM_DEPENDS:=    raspberry-pi raspberry-pi2 raspberry-pi3 raspberry-pi4 solidrun-imx6

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
WRKDIST=		$(WRKDIR)/$(PKG_NAME)-$(PKG_NAME)-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBCEC,libcec,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=		$(WRKDIR)/$(PKG_NAME)-obj
TARGET_LDFLAGS+=	-ltinfo
TARGET_CXXFLAGS+=	-I$(STAGING_TARGET_DIR)/opt/vc/include \
			-I$(STAGING_TARGET_DIR)/opt/vc/include/interface/vcos/pthreads \
			-I$(STAGING_TARGET_DIR)/opt/vc/include/interface/vmcs_host/linux \
			-I$(STAGING_TARGET_DIR)/opt/vc/include/interface/vmcs_host \
			-L$(STAGING_TARGET_DIR)/opt/vc/lib

CONFIG_STYLE:=          cmake
CMAKE_FLAGS+=		-DSKIP_PYTHON_WRAPPER=1 -DBUILD_SHARED_LIBS=1
ifeq ($(ADK_TARGET_BOARD_BCM28XX),y)
CMAKE_FLAGS+=		-DHAVE_RPI_API=1 -DRPI_LIB_DIR=$(STAGING_TARGET_DIR)/opt/vc/lib
endif
ifeq ($(ADK_TARGET_SYSTEM_SOLIDRUN_IMX6),y)
CMAKE_FLAGS+=		-DHAVE_IMX_API=1
endif

libcec-install:
	$(INSTALL_DIR) $(IDIR_LIBCEC)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libcec*.so* \
		$(IDIR_LIBCEC)/usr/lib
	$(INSTALL_DIR) $(IDIR_LIBCEC)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/cec-client \
		$(IDIR_LIBCEC)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
