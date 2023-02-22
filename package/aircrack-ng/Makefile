# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		aircrack-ng
PKG_VERSION:=		1.7
PKG_RELEASE:=		1
PKG_HASH:=		05a704e3c8f7792a17315080a21214a4448fd2452c1b0dd5226a3a55f90b58c3
PKG_DESCR:=		set of tools for auditing wireless networks
PKG_SECTION:=		net/wifi
PKG_DEPENDS:=		libpcap libnl libressl zlib
PKG_BUILDDEP:=		libpcap libnl libressl zlib
PKG_NEEDS:=		threads c++
PKG_URL:=		http://www.aircrack-ng.org/
PKG_SITES:=		http://download.aircrack-ng.org/
# do not build parallel, otherwise libosdep.a may not be ready when compiling airtun-ng
PKG_NOPARALLEL:=	1

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,AIRCRACK_NG,${PKG_NAME},$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autogen
XAKE_FLAGS+=		V=1
CONFIGURE_ARGS+=	--with-libpcap-include='$(STAGING_TARGET_DIR)/usr/include'

aircrack-ng-install:
	$(INSTALL_DIR) $(IDIR_AIRCRACK_NG)/usr/bin
	$(INSTALL_DIR) $(IDIR_AIRCRACK_NG)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/aircrack-ng \
		$(IDIR_AIRCRACK_NG)/usr/bin/
	$(INSTALL_BIN) $(WRKINST)/usr/bin/airdecap-ng \
		$(IDIR_AIRCRACK_NG)/usr/bin/
	$(INSTALL_BIN) $(WRKINST)/usr/bin/packetforge-ng \
		$(IDIR_AIRCRACK_NG)/usr/bin/
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/aireplay-ng \
		$(IDIR_AIRCRACK_NG)/usr/sbin/
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/airodump-ng \
		$(IDIR_AIRCRACK_NG)/usr/sbin/
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/airtun-ng \
		$(IDIR_AIRCRACK_NG)/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
