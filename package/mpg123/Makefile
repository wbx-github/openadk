# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mpg123
PKG_VERSION:=		1.3.1
PKG_RELEASE:=		1
PKG_HASH:=		36ffe1ff2246da8606c35f5199f439d969da20eadeb2c4ef4278c7aca8f88a5d
PKG_DESCR:=		mp3 console player
PKG_SECTION:=		mm/audio
PKG_DEPENDS:=		alsa-lib
PKG_BUILDDEP:=		alsa-lib
PKG_NEEDS:=		threads
PKG_URL:=		http://www.mpg123.de/
PKG_SITES:=		http://www.mpg123.de/download/

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MPG123,mpg123,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

ifeq ($(ADK_TARGET_CPU_X86_I486),y)
CONFIGURE_ARGS+=	--with-cpu=i486
endif
ifeq ($(ADK_TARGET_CPU_X86_I586),y)
CONFIGURE_ARGS+=	--with-cpu=i586
endif
ifeq ($(ADK_TARGET_CPU_WITH_NEON),y)
CONFIGURE_ARGS+=	--with-cpu=neon
endif

CONFIGURE_ARGS+=	--with-default-audio=alsa

mpg123-install:
	$(INSTALL_DIR) $(IDIR_MPG123)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/mpg123 \
		$(IDIR_MPG123)/usr/bin
	$(INSTALL_DIR) $(IDIR_MPG123)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libmpg123*.so* \
		$(IDIR_MPG123)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libltdl.so.3* \
		$(IDIR_MPG123)/usr/lib
	$(INSTALL_DIR) $(IDIR_MPG123)/usr/lib/mpg123
	$(CP) $(WRKINST)/usr/lib/mpg123/* \
		$(IDIR_MPG123)/usr/lib/mpg123

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
