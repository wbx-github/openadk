# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		dillo
PKG_VERSION:=		3.0.5
PKG_RELEASE:=		1
PKG_HASH:=		db1be16c1c5842ebe07b419aa7c6ef11a45603a75df2877f99635f4f8345148b
PKG_DESCR:=		small graphical web browser
PKG_SECTION:=		x11/apps
PKG_DEPENDS:=		libfltk libxi libpng zlib libjpeg-turbo libressl
PKG_BUILDDEP:=		fltk libXi libjpeg-turbo libpng zlib libressl
PKG_NEEDS:=		threads cxx
PKG_URL:=		http://www.dillo.org/
PKG_SITES:=		http://www.dillo.org/download/

PKG_HOST_DEPENDS:=	!cygwin
PKG_ARCH_DEPENDS:=	arm mips mips64 x86 x86_64

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,DILLO,dillo,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CFLAGS+=		-fcommon
TARGET_CXXFLAGS+=	-fcommon
TARGET_LDFLAGS+=	-liconv
CONFIGURE_ENV+=		PNG_CONFIG=$(STAGING_TARGET_DIR)/scripts/libpng-config
CONFIGURE_ARGS+=	--enable-ssl

dillo-install:
	$(INSTALL_DIR) $(IDIR_DILLO)/etc/dillo
	$(INSTALL_DATA) $(WRKINST)/etc/dillo/* $(IDIR_DILLO)/etc/dillo
	$(INSTALL_DIR) $(IDIR_DILLO)/usr/bin $(IDIR_DILLO)/usr/lib/dillo
	$(INSTALL_BIN) $(WRKINST)/usr/bin/dillo $(IDIR_DILLO)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/dpid* $(IDIR_DILLO)/usr/bin
	$(CP) $(WRKINST)/usr/lib/dillo/* $(IDIR_DILLO)/usr/lib/dillo

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
