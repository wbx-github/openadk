# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		jack
PKG_VERSION:=		5013bed0b834d0af1ce36077e2b49ed95934fe99
PKG_RELEASE:=		2
PKG_DESCR:=		audio connection kit (v1)
PKG_SECTION:=		mm/audio
PKG_DEPENDS:=		alsa-lib libsndfile libsamplerate libdb
PKG_BUILDDEP:=		db python3-host alsa-lib libsndfile libsamplerate
PKG_NEEDS:=		threads c++
PKG_URL:=		http://jackaudio.org
PKG_SITES:=		https://github.com/jackaudio/jack1.git
PKG_OPT:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,JACK,jack,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

AUTOTOOL_STYLE:=	autogen

post-extract:
	(cd $(WRKBUILD); git submodule init)
	(cd $(WRKBUILD); git submodule update)

jack-install:
	$(INSTALL_DIR) $(IDIR_JACK)/usr/lib/jack
	$(INSTALL_DIR) $(IDIR_JACK)/usr/bin
	$(CP) $(WRKINST)/usr/bin/jack* \
		$(IDIR_JACK)/usr/bin
	$(CP) $(WRKINST)/usr/lib*/libjack*.so* \
		$(IDIR_JACK)/usr/lib
	$(CP) $(WRKINST)/usr/lib*/jack/*.so* \
		$(IDIR_JACK)/usr/lib/jack

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
