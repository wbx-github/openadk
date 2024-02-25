# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mopd
PKG_VERSION:=		1.3.5
PKG_RELEASE:=		1
PKG_DESCR:=		mop daemon
PKG_SECTION:=		net/misc

NO_DISTFILES:=		1

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MOPD,mopd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

TARGET_CFLAGS+=		-fcommon
CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

mopd-install:
	$(INSTALL_DIR) $(IDIR_MOPD)/usr/sbin
	$(INSTALL_BIN) $(WRKBUILD)/mopd/mopd \
		$(IDIR_MOPD)/usr/sbin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
