# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xawtv
PKG_VERSION:=		47a81c3ca7ac9b4f0989cccb7961dc4bff52364a
PKG_RELEASE:=		1
PKG_GIT:=		hash
PKG_DESCR:=		video & webcam application
PKG_BUILDDEP:=		libXinerama v4l-utils
PKG_DEPENDS:=		libxinerama libv4l
PKG_SECTION:=		x11/apps
PKG_SITES:=		http://git.linuxtv.org/xawtv3.git

PKG_ARCH_DEPENDS:=	x86 x86_64

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,XAWTV,xawtv,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autoreconf
XAKE_FLAGS:=		SUID_ROOT=-m755

xawtv-install:
	$(INSTALL_DIR) $(IDIR_XAWTV)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/xawtv \
		$(IDIR_XAWTV)/usr/bin
	$(INSTALL_DIR) $(IDIR_XAWTV)/usr/lib/xawtv
	$(CP) $(WRKINST)/usr/lib/xawtv/*.so \
		$(IDIR_XAWTV)/usr/lib/xawtv
	$(INSTALL_DIR) $(IDIR_XAWTV)/usr/share/xawtv
	$(CP) $(WRKINST)/usr/share/xawtv/* \
		$(IDIR_XAWTV)/usr/share/xawtv

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
