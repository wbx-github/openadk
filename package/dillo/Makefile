# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		dillo
PKG_VERSION:=		3.2.0
PKG_RELEASE:=		1
PKG_HASH:=		1066ed42ea7fe0ce19e79becd029c651c15689922de8408e13e70bb5701931bf
PKG_DESCR:=		small graphical web browser
PKG_SECTION:=		x11/apps
PKG_DEPENDS:=		libfltk libxi libpng zlib libjpeg-turbo libopenssl
PKG_DEPENDS+=		libXrender libXfixes libXext fontconfig libxml2 ca-certificates
PKG_BUILDDEP:=		fltk libXi libjpeg-turbo libpng zlib openssl
PKG_NEEDS:=		threads cxx
PKG_URL:=		https://dillo-browser.github.io/
PKG_SITES:=		https://github.com/dillo-browser/dillo/releases/download/v$(PKG_VERSION)/

PKG_ARCH_DEPENDS:=	aarch64 arm mips mips64 sh x86 x86_64

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,DILLO,dillo,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_LDFLAGS+=	-latomic
CONFIGURE_ENV+=		PNG_CONFIG=$(STAGING_TARGET_DIR)/scripts/libpng-config
CONFIGURE_ARGS+=	--enable-tls \
			--disable-xembed

dillo-install:
	$(INSTALL_DIR) $(IDIR_DILLO)/etc/dillo
	$(INSTALL_DATA) $(WRKINST)/etc/dillo/* $(IDIR_DILLO)/etc/dillo
	$(INSTALL_DIR) $(IDIR_DILLO)/usr/bin $(IDIR_DILLO)/usr/lib/dillo
	$(INSTALL_BIN) $(WRKINST)/usr/bin/dillo $(IDIR_DILLO)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/dpid* $(IDIR_DILLO)/usr/bin
	$(CP) $(WRKINST)/usr/lib/dillo/* $(IDIR_DILLO)/usr/lib/dillo

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
