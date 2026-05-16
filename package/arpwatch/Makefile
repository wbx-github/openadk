# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		arpwatch
PKG_VERSION:=		3.9
PKG_RELEASE:=		1
PKG_HASH:=		832d20a5a508d9694a84a17e2627de3b3aa8b42b19ebdd97e264c511168f6eb4
PKG_DESCR:=		ethernet monitor program
PKG_SECTION:=		net/debug
PKG_DEPENDS:=		libpcap
PKG_BUILDDEP:=		libpcap
PKG_URL:=		http://www-nrg.ee.lbl.gov/
PKG_SITES:=		https://ee.lbl.gov/downloads/arpwatch/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ARPWATCH,${PKG_NAME},${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--with-sendmail=/dev/null

INSTALL_STYLE:=		manual

MAKE_FLAGS+=		ARPDIR=/etc/arpwatch \
			CCOPT="$(TARGET_CFLAGS)" \
			INCLS="-I. -I$(STAGING_TARGET_DIR)/usr/include" \
			LIBS="-L$(STAGING_TARGET_DIR)/usr/lib -lpcap"

do-install:
	$(INSTALL_DIR) $(IDIR_ARPWATCH)/usr/sbin $(IDIR_ARPWATCH)/etc/arpwatch
	$(INSTALL_BIN) $(WRKBUILD)/arpwatch $(IDIR_ARPWATCH)/usr/sbin/
	$(INSTALL_BIN) $(WRKBUILD)/arpsnmp $(IDIR_ARPWATCH)/usr/sbin/
	$(INSTALL_DATA) $(WRKBUILD)/arp.dat $(IDIR_ARPWATCH)/etc/arpwatch/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
