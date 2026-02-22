# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		lightdm
PKG_VERSION:=		1.32.0
PKG_RELEASE:=		1
PKG_HASH:=		12f5ab432748f0387c7cf8b94430495a558a035a4f8465e5181af6faff133e4b
PKG_DESCR:=		light display manager
PKG_DEPENDS:=		libgcrypt libxklavier
PKG_BUILDDEP:=		libgcrypt libxklavier
PKG_SECTION:=		x11/apps
PKG_SITES:=		https://github.com/CanonicalLtd/lightdm/releases/download/1.32.0/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIGHTDM,lightdm,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

lightdm-install:
	$(INSTALL_DIR) $(IDIR_LIGHTDM)/etc
	$(CP) $(WRKINST)/etc/* \
		$(IDIR_LIGHTDM)/etc
	$(INSTALL_DIR) $(IDIR_LIGHTDM)/usr/sbin
	$(CP) $(WRKINST)/usr/sbin/lightdm* \
		$(IDIR_LIGHTDM)/usr/sbin
	$(INSTALL_DIR) $(IDIR_LIGHTDM)/usr/lib
	$(CP) $(WRKINST)/usr/lib/*.so* \
		$(IDIR_LIGHTDM)/usr/lib
	$(INSTALL_DIR) $(IDIR_LIGHTDM)/usr/share
	$(CP) $(WRKINST)/usr/share/* \
		$(IDIR_LIGHTDM)/usr/share
	$(INSTALL_DIR) $(IDIR_LIGHTDM)/usr/libexec
	$(CP) $(WRKINST)/usr/libexec/* \
		$(IDIR_LIGHTDM)/usr/libexec

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
