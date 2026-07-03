# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mpg123
PKG_VERSION:=		1.33.6
PKG_RELEASE:=		1
PKG_HASH:=		929a7c18ba662b8927aed4de229ad9ae8ab2b4806dd0f30b90113eb1b4e2195a
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
ifeq ($(ADK_TARGET_ARCH_ARM)$(ADK_TARGET_CPU_WITH_NEON),yy)
CONFIGURE_ARGS+=	--with-cpu=neon
endif
ifeq ($(ADK_TARGET_ARCH_AARCH64),y)
CONFIGURE_ARGS+=	--with-cpu=aarch64
endif

CONFIGURE_ARGS+=	--with-default-audio=alsa --disable-shared

mpg123-install:
	$(INSTALL_DIR) $(IDIR_MPG123)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/mpg123 \
		$(IDIR_MPG123)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
