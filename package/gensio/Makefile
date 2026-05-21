# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		gensio
PKG_VERSION:=		3.0.2
PKG_RELEASE:=		1
PKG_HASH:=		f05e96d3497c4085c5493b36a3a6d5e25d8787a3de220135335f1ec93fca3637
PKG_DESCR:=		c library/framework for generalized stream i/o 
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://sourceforge.net/projects/ser2net/files/ser2net/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,GENSIO,gensio,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIGURE_ARGS+=	--with-glib=no \
			--with-tcl=no \
			--with-cplusplus=no \
			--with-python=no

gensio-install:
	$(INSTALL_DIR) $(IDIR_GENSIO)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgensio*.so* \
		$(IDIR_GENSIO)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
