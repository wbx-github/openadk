# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		bcm28xx-vc
PKG_VERSION:=		14b90ff9d9f031391a299e6e006965d02bfd1bb1
PKG_GIT:=		hash
PKG_RELEASE:=		1
PKG_DESCR:=		videocore tools and libraries
PKG_SECTION:=		libs/video
PKG_BUILDDEP:=		cmake-host
PKG_NEEDS:=		c++ threads
PKG_URL:=		https://github.com/raspberrypi/userland
PKG_SITES:=		https://github.com/raspberrypi/userland.git

PKG_SUBPKGS:=		BCM28XX_VC_TOOLS BCM28XX_VC_LIBS BCM28XX_VC_GL_LIBS BCM28XX_VC_DEBUG
PKGSS_BCM28XX_VC_TOOLS:=bcm28xx-vc-libs
PKGSC_BCM28XX_VC_TOOLS:=sys/hw
PKGSD_BCM28XX_VC_TOOLS:=videocore tools (vcgencmd,..)
PKGSC_BCM28XX_VC_LIBS:=	libs/misc
PKGSD_BCM28XX_VC_LIBS:=videocore library
PKGSC_BCM28XX_VC_DEBUG:=libs/misc
PKGSD_BCM28XX_VC_DEBUG:=videocore debug library
PKGSC_BCM28XX_VC_GL_LIBS:=libs/video
PKGSS_BCM28XX_VC_GL_LIBS:=bcm28xx-vc-libs
PKGSD_BCM28XX_VC_GL_LIBS:=videocore gl library

PKG_SYSTEM_DEPENDS:=	raspberry-pi raspberry-pi0 raspberry-pi2 raspberry-pi3 raspberry-pi3-64 raspberry-pi3p raspberry-pi3p-64

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,BCM28XX_VC_TOOLS,bcm28xx-vc-tools,$(PKG_VERSION)-$(PKG_RELEASE),$(PKGSS_BCM28XX_VC_TOOLS),$(PKG_DESCR),$(PKGSC_BCM28XX_VC_TOOLS)))
$(eval $(call PKG_template,BCM28XX_VC_LIBS,bcm28xx-vc-libs,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))
$(eval $(call PKG_template,BCM28XX_VC_DEBUG,bcm28xx-vc-debug,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))
$(eval $(call PKG_template,BCM28XX_VC_GL_LIBS,bcm28xx-vc-gl-libs,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=          cmake
CMAKE_FLAGS+=		-DVMCS_INSTALL_PREFIX=/usr

bcm28xx-vc-tools-install:
	$(INSTALL_DIR) $(IDIR_BCM28XX_VC_TOOLS)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/vcgencmd \
		$(IDIR_BCM28XX_VC_TOOLS)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/dtoverlay \
		$(IDIR_BCM28XX_VC_TOOLS)/usr/bin

bcm28xx-vc-debug-install:
	$(INSTALL_DIR) $(IDIR_BCM28XX_VC_DEBUG)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libdebug_sym.so \
		$(IDIR_BCM28XX_VC_DEBUG)/usr/lib

bcm28xx-vc-libs-install:
	$(INSTALL_DIR) $(IDIR_BCM28XX_VC_LIBS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libvcos.so \
		$(IDIR_BCM28XX_VC_LIBS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libvchiq_arm.so \
		$(IDIR_BCM28XX_VC_LIBS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libbcm_host.so \
		$(IDIR_BCM28XX_VC_LIBS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libcontainers.so \
		$(IDIR_BCM28XX_VC_LIBS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libdtovl.so \
		$(IDIR_BCM28XX_VC_LIBS)/usr/lib

bcm28xx-vc-gl-libs-install:
	$(INSTALL_DIR) $(IDIR_BCM28XX_VC_GL_LIBS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libmmal*.so \
		$(IDIR_BCM28XX_VC_GL_LIBS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libopenmaxil.so \
		$(IDIR_BCM28XX_VC_GL_LIBS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libvcsm.so \
		$(IDIR_BCM28XX_VC_GL_LIBS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libEGL.so \
		$(IDIR_BCM28XX_VC_GL_LIBS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libGLESv2.so \
		$(IDIR_BCM28XX_VC_GL_LIBS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libOpenVG.so \
		$(IDIR_BCM28XX_VC_GL_LIBS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libbrcm*.so \
		$(IDIR_BCM28XX_VC_GL_LIBS)/usr/lib
	(cd $(IDIR_BCM28XX_VC_GL_LIBS)/usr/lib && ln -sf libEGL.so libEGL.so.1)

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
