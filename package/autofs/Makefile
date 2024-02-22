# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		autofs
PKG_VERSION:=		5.1.9
PKG_RELEASE:=		1
PKG_HASH:=		87e6af6a03794b9462ea519781e50e7d23b5f7c92cd59e1142c85d2493b3c24b
PKG_DESCR:=		automount filesystems
PKG_SECTION:=		net/fs
PKG_DEPENDS:=		libtirpc
PKG_BUILDDEP:=		libtirpc
PKG_SITES:=		https://www.kernel.org/pub/linux/daemons/autofs/v5/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,AUTOFS,autofs,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIGURE_ARGS+=	--with-libtirpc

autofs-install:
	$(INSTALL_DIR) $(IDIR_AUTOFS)/usr/lib/autofs
	$(CP) $(WRKINST)/usr/lib/autofs/*.so \
		$(IDIR_AUTOFS)/usr/lib/autofs
	$(INSTALL_DIR) $(IDIR_AUTOFS)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/automount \
		$(IDIR_AUTOFS)/usr/sbin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
