# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		brutefir
PKG_VERSION:=		1.0o
PKG_RELEASE:=		3
PKG_HASH:=		caae4a933b53b55b29d6cb7e2803e20819f31def6d0e4e12f9a48351e6dbbe9f
PKG_DESCR:=		convolution engine
PKG_SECTION:=		mm/audio
PKG_DEPENDS:=		fftw alsa-lib
PKG_BUILDDEP:=		flex-host fftw alsa-lib
PKG_URL:=		https://www.ludd.ltu.se/~torger/brutefir.html
PKG_SITES:=		https://www.ludd.ltu.se/~torger/files/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_CHOICES_BRUTEFIR:=	WITH_JACK2
PKGCD_WITH_JACK2:=	use jack
PKGCB_WITH_JACK2:=	jack2
PKGCS_WITH_JACK2:=	jack2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,BRUTEFIR,brutefir,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE=		manual
ifeq ($(ADK_TARGET_CPU_WITH_SSE2),y)
TARGET_CFLAGS+=		-msse2
else
ifeq ($(ADK_TARGET_CPU_WITH_SSE),y)
TARGET_CFLAGS+=		-msse
endif
endif

MAKE_ENV+= 		FLEX=$(STAGING_HOST_DIR)/usr/bin/flex UNAME_M=$(ADK_TARGET_ARCH)
GCCPATH:=		$(subst libgcc.a,,$(shell $(TARGET_CC) -print-libgcc-file-name 2>/dev/null))
XAKE_FLAGS+=		LIBPATHS="-L$(GCCPATH)"

brutefir-install:
	$(INSTALL_DIR) $(IDIR_BRUTEFIR)/usr/bin
	$(INSTALL_DIR) $(IDIR_BRUTEFIR)/usr/lib
	$(INSTALL_BIN) $(WRKINST)/usr/bin/brutefir \
		$(IDIR_BRUTEFIR)/usr/bin
	$(CP) $(WRKINST)/usr/lib/* \
		$(IDIR_BRUTEFIR)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
