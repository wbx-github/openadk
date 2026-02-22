# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		lxsession
PKG_VERSION:=		0.5.6
PKG_RELEASE:=		1
PKG_HASH:=		884a33824c86c8eddd77a86237b337aab9d3a08f61da7b88faa47ed05e02d1df
PKG_DESCR:=		lxde session manager
PKG_DEPENDS:=		pango cairo libxrandr glib libgtk3 harfbuzz
PKG_DEPENDS+=		libx11
PKG_BUILDDEP:=		pango cairo glib polkit libXrandr libgtk3 
PKG_BUILDDEP+=		libX11 harfbuzz
PKG_SECTION:=		x11/lxde
PKG_URL:=		https://lxde.org/
PKG_SITES:=		https://github.com/lxde/releases/raw/refs/heads/master/releases/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LXSESSION,lxsession,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIGURE_ARGS+=	--enable-gtk3

lxsession-install:
	$(INSTALL_DIR) $(IDIR_LXSESSION)/etc/xdg
	$(CP) $(WRKINST)/etc/xdg/* \
		$(IDIR_LXSESSION)/etc/xdg
	# do not start lxpolkit here
	rm $(IDIR_LXSESSION)/etc/xdg/autostart/lxpolkit.desktop
	$(INSTALL_DIR) $(IDIR_LXSESSION)/usr/bin
	$(CP) $(WRKINST)/usr/bin/* \
		$(IDIR_LXSESSION)/usr/bin
	$(INSTALL_DIR) $(IDIR_LXSESSION)/usr/share
	$(CP) $(WRKINST)/usr/share/* \
		$(IDIR_LXSESSION)/usr/share
	$(INSTALL_DIR) $(IDIR_LXSESSION)/usr/libexec
	$(CP) $(WRKINST)/usr/libexec/* \
		$(IDIR_LXSESSION)/usr/libexec

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
