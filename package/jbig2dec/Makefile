# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		jbig2dec
PKG_VERSION:=		0.20
PKG_RELEASE:=		1
PKG_HASH:=		7b63ff6470289547e7a3a0f145cb8ea6c2afffdd65645b7d87d3b7febc96fb3a
PKG_DESCR:=		jbig image decoder
PKG_SECTION:=		libs/image
PKG_URL:=		https://github.com/ArtifexSoftware/jbig2dec/
PKG_SITES:=		https://github.com/ArtifexSoftware/jbig2dec/releases/download/$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,JBIG2DEC,jbig2dec,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

jbig2dec-install:
	$(INSTALL_DIR) $(IDIR_JBIG2DEC)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libjbig2dec*.so* \
		$(IDIR_JBIG2DEC)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
