# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		jack2
PKG_VERSION:=		99e5d115ea47f6673ef741ce5633e57661f63510
PKG_RELEASE:=		1
PKG_GIT:=		hash
PKG_DESCR:=		audio connection kit (v2)
PKG_SECTION:=		mm/audio
PKG_DEPENDS:=		alsa-lib libsndfile libsamplerate
PKG_BUILDDEP:=		python3-host alsa-lib libsndfile libsamplerate
PKG_NEEDS:=		threads c++
PKG_URL:=		http://jackaudio.org
PKG_SITES:=		https://github.com/jackaudio/jack2.git

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,JACK2,jack2,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

do-configure:
	cd $(WRKBUILD) && PATH='$(HOST_PATH)' ./waf configure --alsa=yes --prefix=/usr

do-build:
	cd $(WRKBUILD) && PATH='$(HOST_PATH)' ./waf build

do-install:
	cd $(WRKBUILD) && PATH='$(HOST_PATH)' ./waf install --destdir=$(WRKINST)

jack2-install:
	$(INSTALL_DIR) $(IDIR_JACK2)/usr/bin
	$(CP) $(WRKINST)/usr/bin/jack* \
		$(IDIR_JACK2)/usr/bin
	$(INSTALL_DIR) $(IDIR_JACK2)/usr/lib/jack
	$(CP) $(WRKINST)/usr/lib/libjack{,server,net}.so* \
		$(IDIR_JACK2)/usr/lib
	$(CP) $(WRKINST)/usr/lib/jack/*.so \
		$(IDIR_JACK2)/usr/lib/jack
	$(CP) ./files/jack.pc.in $(WRKINST)/usr/lib/pkgconfig/jack.pc
	$(SED) "s#@INCLUDEDIR@#$(STAGING_TARGET_DIR)/usr/include#" \
		-e "s#@LIBDIR@#$(STAGING_TARGET_DIR)/usr/lib#" \
		-e "s#@PREFIX@#$(STAGING_TARGET_DIR)/usr#" \
		$(WRKINST)/usr/lib/pkgconfig/jack.pc


include ${ADK_TOPDIR}/mk/pkg-bottom.mk
