# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		lxdm
PKG_VERSION:=		0.5.3
PKG_RELEASE:=		1
PKG_HASH:=		4891efee81c72a400cc6703e40aa76f3f3853833d048b72ec805da0f93567f2f
PKG_DESCR:=		lxde display manager
PKG_SECTION:=		x11/lxde
PKG_DEPENDS:=		pam
PKG_BUILDDEP:=		pam
PKG_URL:=		https://lxde.org/
PKG_SITES:=		https://sourceforge.net/projects/lxdm/files/lxdm%200.5.3/lxdm-0.5.3.tar.xz/download

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LXDM,lxdm,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIGURE_ARGS+=	--enable-gtk3 \
			--with-pam \
			--enable-debug

lxdm-install:
	$(INSTALL_DIR) $(IDIR_LXDM)/etc/lxdm
	$(CP) $(WRKINST)/etc/lxdm/* $(IDIR_LXDM)/etc/lxdm
	$(INSTALL_DIR) $(IDIR_LXDM)/usr/share/lxdm
	$(CP) $(WRKINST)/usr/share/lxdm/* \
		$(IDIR_LXDM)/usr/share/lxdm
	$(INSTALL_DIR) $(IDIR_LXDM)/usr/libexec
	$(CP) $(WRKINST)/usr/libexec/* \
		$(IDIR_LXDM)/usr/libexec
	$(INSTALL_DIR) $(IDIR_LXDM)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/lxdm* \
		$(IDIR_LXDM)/usr/sbin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
