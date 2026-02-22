# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		pcmanfm
PKG_VERSION:=		1.4.0
PKG_RELEASE:=		1
PKG_HASH:=		55066ccd32039ab2d3f5a9054c34b292451663b0de8d9ef766430ac483624ade
PKG_DESCR:=		lxde file manager
PKG_SECTION:=		x11/lxde
PKG_DEPENDS:=		libfm libmount
PKG_BUILDDEP:=		libfm util-linux
PKG_URL:=		https://lxde.org/
PKG_SITES:=		https://github.com/lxde/releases/raw/refs/heads/master/releases/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,PCMANFM,pcmanfm,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIGURE_ARGS+=	--with-gtk=3

pcmanfm-install:
	$(INSTALL_DIR) $(IDIR_PCMANFM)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/pcmanfm \
		$(IDIR_PCMANFM)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
