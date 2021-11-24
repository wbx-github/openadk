# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		sngrep
PKG_VERSION:=		1.4.10
PKG_RELEASE:=		1
PKG_HASH:=		cedbe521c9730deda004bff71e88c8c56ae66d3d147ddc6f5f965df2ca67a8df
PKG_DESCR:=		displaying sip calls message flows from terminal 
PKG_SECTION:=		net/debug
PKG_BUILDDEP:=		libpcap ncurses
PKG_DEPENDS:=		libpcap libncurses
PKG_URL:=		https://github.com/irontec/sngrep
PKG_SITES:=		https://github.com/irontec/sngrep/archive/

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SNGREP,sngrep,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

TARGET_LDFLAGS+=	-ltinfo

AUTOTOOL_STYLE:=	bootstrap

sngrep-install:
	$(INSTALL_DIR) $(IDIR_SNGREP)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/sngrep \
		$(IDIR_SNGREP)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
