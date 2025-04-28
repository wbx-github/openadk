# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xf86-video-fbdev
PKG_VERSION:=		0.5.1
PKG_RELEASE:=		1
PKG_HASH:=		5e73c01f6ede09ddbc1f553fecdf35dd8efe76b44c7ed263de786a5968c5116f
PKG_DESCR:=		x11 driver for framebuffer devices
PKG_SECTION:=		x11/drivers
PKG_DEPENDS:=		xorg-server
PKG_BUILDDEP:=		xorg-server
PKG_NEEDS:=		c++
PKG_SITES:=		http://www.x.org/releases/individual/driver/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_ARCH_DEPENDS:=      !m68k
PKG_CFLINE_XF86_VIDEO_FBDEV:=	depends on ADK_TARGET_WITH_VGA

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,XF86_VIDEO_FBDEV,xf86-video-fbdev,$(PKG_VERSION)-$(PKG_RELEASE),${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

xf86-video-fbdev-install:
	${INSTALL_DIR} ${IDIR_XF86_VIDEO_FBDEV}/usr/lib/xorg/modules/drivers
	${CP} ${WRKINST}/usr/lib/xorg/modules/drivers/fbdev_*.so \
		${IDIR_XF86_VIDEO_FBDEV}/usr/lib/xorg/modules/drivers/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
