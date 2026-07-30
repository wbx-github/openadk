# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		frr
PKG_VERSION:=		10.7.0
PKG_RELEASE:=		1
PKG_HASH:=		5c56b27756854b8d0a62b3e152d3f9ea08091851b2d686e140fdfb95cd88f612
PKG_DESCR:=		internet routing protocol suite
PKG_SECTION:=		net/route
PKG_BUILDDEP:=		json-c libyang readline ncurses libcap
PKG_DEPENDS:=		json-c libyang libreadline libncurses libcap
PKG_BUILDDEP_GLIBC:=	libxcrypt
PKG_DEPENDS_GLIBC:=	libxcrypt
PKG_URL:=		https://frrouting.org/
PKG_SITES:=		https://github.com/FRRouting/frr/archive/refs/tags/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz
WRKDIST=		$(WRKDIR)/$(PKG_NAME)-$(PKG_NAME)-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FRR,frr,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

AUTOTOOL_STYLE:=	autoreconf

CONFIGURE_ARGS+=	--disable-protobuf

frr-install:
	$(INSTALL_DIR) $(IDIR_FRR)/usr/lib
	$(CP) $(WRKINST)/usr/lib/lib*.so.* \
		$(IDIR_FRR)/usr/lib
	$(INSTALL_DIR) $(IDIR_FRR)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/*d \
		$(IDIR_FRR)/usr/sbin
	$(INSTALL_DIR) $(IDIR_FRR)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/* \
		$(IDIR_FRR)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
