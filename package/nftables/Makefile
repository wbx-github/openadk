# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		nftables
PKG_VERSION:=		1.1.7
PKG_RELEASE:=		1
PKG_HASH:=		a6fbf060d8d4fff001517a2b94f356bb4366bfbf0ba366366f9d27cc38caa58f
PKG_DESCR:=		firewall framework utils for linux
PKG_SECTION:=		net/firewall
PKG_DEPENDS:=		libmnl libnftnl libgmp libreadline libncurses
PKG_KDEPENDS:=		nf-conntrack nf-tables nf-nat
PKG_BUILDDEP:=		libmnl libnftnl gmp readline ncurses
PKG_URL:=		https://www.netfilter.org
PKG_SITES:=		https://www.netfilter.org/projects/nftables/files/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,NFTABLES,nftables,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

TARGET_LDFLAGS+=	-lncursesw

CONFIGURE_ARGS+=	--with-cli=readline

nftables-install:
	$(INSTALL_DIR) $(IDIR_NFTABLES)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libnftables.so.* \
		$(IDIR_NFTABLES)/usr/lib
	$(INSTALL_DIR) $(IDIR_NFTABLES)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/nft \
		$(IDIR_NFTABLES)/usr/sbin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
