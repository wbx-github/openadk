# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mupdf
PKG_VERSION:=		1.28.5
PKG_RELEASE:=		1
PKG_HASH:=		98a5c10cda20c3992cdf76ff6b2a1149c32bd79cc796d3f703230b1185b7e934
PKG_DESCR:=		pdf reader
PKG_SECTION:=		x11/apps
PKG_DEPENDS:=		brotli openjpeg jbig2dec gumbo-parser fontconfig libjpeg-turbo
PKG_DEPENDS+=		libX11 harfbuzz
PKG_BUILDDEP:=		brotli openjpeg jbig2dec gumbo-parser fontconfig libjpeg-turbo
PKG_BUILDDEP+=		libX11 harfbuzz
PKG_URL:=		https://mupdf.com/
PKG_SITES:=		https://casper.mupdf.com/downloads/archive/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION)-source.tar.gz
WRKDIST=		$(WRKDIR)/$(PKG_NAME)-$(PKG_VERSION)-source

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MUPDF,mupdf,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
MAKE_ENV+=		USE_SYSTEM_LIBS=yes \
			HAVE_GLUT=no

mupdf-install:
	$(INSTALL_DIR) $(IDIR_MUPDF)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/local/bin/mupdf-x11 \
		$(IDIR_MUPDF)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
