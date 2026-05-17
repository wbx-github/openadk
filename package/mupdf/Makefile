# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mupdf
PKG_VERSION:=		1.27.2
PKG_RELEASE:=		1
PKG_HASH:=		553867b135303dc4c25ab67c5f234d8e900a0e36e66e8484d99adc05fe1e8737
PKG_DESCR:=		pdf reader
PKG_SECTION:=		x11/apps
PKG_DEPENDS:=		brotli openjpeg jbig2dec gumbo-parser freeglut
PKG_BUILDDEP:=		brotli openjpeg jbig2dec gumbo-parser freeglut
PKG_URL:=		https://mupdf.com/
PKG_SITES:=		https://casper.mupdf.com/downloads/archive/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION)-source.tar.gz
WRKDIST=		$(WRKDIR)/$(PKG_NAME)-$(PKG_VERSION)-source

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MUPDF,mupdf,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
MAKE_ENV+=		USE_SYSTEM_LIBS=yes

mupdf-install:
	$(INSTALL_DIR) $(IDIR_MUPDF)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/local/bin/mupdf-x11 \
		$(IDIR_MUPDF)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
