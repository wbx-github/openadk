# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		tcptrace
PKG_VERSION:=		6.6.7
PKG_RELEASE:=		1
PKG_HASH:=		63380a4051933ca08979476a9dfc6f959308bc9f60d45255202e388eb56910bd
PKG_DESCR:=		tool for analyzing network packet dumps
PKG_SECTION:=		net/debug
PKG_DEPENDS:=		libpcap
PKG_BUILDDEP:=		libpcap
PKG_URL:=		http://www.tcptrace.org
PKG_SITES:=		http://www.tcptrace.org/download/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,TCPTRACE,tcptrace,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

FAKE_FLAGS:=		BINDIR="$(WRKINST)/usr/bin" MANDIR="$(WRKINST)/usr/man" INSTALL="install -D"
TARGET_CPPFLAGS+=	-D_BSD_SOURCE
TARGET_CFLAGS+=		-std=gnu99

tcptrace-install:
	$(INSTALL_DIR) $(IDIR_TCPTRACE)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/tcptrace \
		$(IDIR_TCPTRACE)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
