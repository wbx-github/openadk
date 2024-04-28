# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mosh
PKG_VERSION:=		1.4.0
PKG_RELEASE:=		1
PKG_HASH:=		ae581fbddf038730af9eee4d319a483288395a0722d0c94c7efb7fdbdbb0dbac
PKG_DESCR:=		mobile shell
PKG_SECTION:=		net/security
PKG_DEPENDS:=		zlib libncurses libressl perl protobuf
PKG_BUILDDEP:=		protobuf-host protobuf zlib ncurses libressl
PKG_NEEDS:=		c++
PKG_URL:=		https://mosh.org/
PKG_SITES:=		https://github.com/mobile-shell/mosh/archive/refs/tags/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

WRKDIST=		${WRKDIR}/$(PKG_NAME)-$(PKG_NAME)-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MOSH,mosh,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

AUTOTOOL_STYLE:=	autogen

mosh-install:
	$(INSTALL_DIR) $(IDIR_MOSH)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/mosh* \
		$(IDIR_MOSH)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
