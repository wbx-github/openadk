# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		yafut
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_HASH:=		e342c93
PKG_DESCR:=		Access yaffs contents from user space
PKG_SECTION:=		sys/fs
PKG_BUILDDEP:=		cmake-host
PKG_SITES:=		https://github.com/kempniu/yafut.git
DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,YAFUT,yafut,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,YAFUT,yafut,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

HOST_CONFIG_STYLE:=	cmake
CONFIG_STYLE:=		cmake

yafut-install:
	$(INSTALL_DIR) $(IDIR_YAFUT)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/yafut \
		$(IDIR_YAFUT)/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
