# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		qtbase
PKG_VERSION:=		5.7.0
PKG_RELEASE:=		1
PKG_HASH:=		3e7b6d123cab23a587ccbc45173296b33786faa409dba0494e4658fda3ede646
PKG_DESCR:=		qt5 base
PKG_SECTION:=		libs/qt
PKG_DEPENDS:=		zlib libopenssl
PKG_BUILDDEP:=		zlib openssl
PKG_NEEDS:=		c++
PKG_URL:=		https://www.qt.io/
PKG_SITES:=		http://download.qt.io/official_releases/qt/5.7/$(PKG_VERSION)/submodules/

DISTFILES:=             $(PKG_NAME)-opensource-src-$(PKG_VERSION).tar.xz
WRKDIST=		$(WRKDIR)/$(PKG_NAME)-opensource-src-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,QTBASE,qtbase,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIGURE_ENV:=
CONFIG_STYLE:=		minimal
CONFIGURE_ARGS+=	-v \
			-prefix /usr \
			-hostprefix $(STAGING_HOST_DIR) \
			-opensource \
			-confirm-license \
			-no-nis \
			-no-pch \
			-no-cups \
			-no-iconv \
			-no-rpath \
			-no-gstreamer \
			-no-dbus \
			-no-pulseaudio \
			-no-alsa \
			-no-openssl \
			-release \
			-shared \
			-system-zlib \
			-nomake tests \
			-nomake examples \
			-device openadk \
			-device-option CROSS_COMPILE="$(TARGET_CROSS)" \
			-device-option ADK_COMPILER_CFLAGS="$(TARGET_CFLAGS)" \
			-device-option ADK_COMPILER_CXXFLAGS="$(TARGET_CXXFLAGS)" \
			-device-option ADK_COMPILER_LDFLAGS="$(TARGET_LDFLAGS)" \
			-no-gcc-sysroot \
			-sysroot $(STAGING_TARGET_DIR)

pre-configure:
	$(INSTALL_DIR) $(WRKBUILD)/mkspecs/devices/linux-openadk-g++/
	$(CP) ./files/qmake.conf $(WRKBUILD)/mkspecs/devices/linux-openadk-g++/
	$(CP) ./files/qplatformdefs.h $(WRKBUILD)/mkspecs/devices/linux-openadk-g++/

qtbase-install:
	$(INSTALL_DIR) $(IDIR_QTBASE)/usr/lib
	$(CP) $(STAGING_TARGET_DIR)/usr/lib/libQt5*.so* $(IDIR_QTBASE)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
