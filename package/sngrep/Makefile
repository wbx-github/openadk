# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		sngrep
PKG_VERSION:=		1.8.3
PKG_RELEASE:=		1
PKG_HASH:=		794224f4cd08978a6115a767e9945f756fdf7cbc7c1a34eabca293e0293b21b8
PKG_DESCR:=		displaying sip calls message flows from terminal 
PKG_SECTION:=		net/debug
PKG_BUILDDEP:=		libpcap ncurses
PKG_DEPENDS:=		libpcap libncurses
PKG_URL:=		https://github.com/irontec/sngrep
PKG_SITES:=		https://github.com/irontec/sngrep/archive/

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SNGREP,sngrep,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

TARGET_CFLAGS+=		-Wno-implicit-function-declaration

AUTOTOOL_STYLE:=	bootstrap
CONFIGURE_ARGS+=	--enable-unicode

sngrep-install:
	$(INSTALL_DIR) $(IDIR_SNGREP)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/sngrep \
		$(IDIR_SNGREP)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
