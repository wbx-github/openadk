# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		pmacct
PKG_VERSION:=		1.7.8
PKG_RELEASE:=		1
PKG_HASH:=		4df50a3c6c7bdace3345bbf3bd4f6fa7a6722ec1fb45dfd266ad956b327da98a
PKG_DESCR:=		ip accounting tools
PKG_SECTION:=		net/acct
PKG_DEPENDS:=		libpcap libcdada
PKG_BUILDDEP:=		libpcap libcdada
PKG_URL:=		http://www.pmacct.net/
PKG_SITES:=		http://www.pmacct.net/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		NFACCTD PMACCTD SFACCTD PMACCT_CLIENT

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,NFACCTD,nfacctd,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,PMACCTD,pmacctd,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SFACCTD,sfacctd,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,PMACCT_CLIENT,pmacct-client,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--with-pcap-includes="$(STAGING_TARGET_DIR)/usr/include" \
			--with-pcap-libs="$(STAGING_TARGET_DIR)/usr/lib" \
			--without-external-deps

sfacctd-install:
	${INSTALL_DIR} $(IDIR_SFACCTD)/usr/sbin
	${INSTALL_BIN} $(WRKINST)/usr/sbin/sfacctd $(IDIR_SFACCTD)/usr/sbin/

nfacctd-install:
	${INSTALL_DIR} $(IDIR_NFACCTD)/usr/sbin $(IDIR_NFACCTD)/etc
	${INSTALL_BIN} $(WRKINST)/usr/sbin/nfacctd $(IDIR_NFACCTD)/usr/sbin/
	${INSTALL_DATA} ./files/nfacctd.conf $(IDIR_NFACCTD)/etc

pmacctd-install:
	${INSTALL_DIR} $(IDIR_PMACCTD)/usr/sbin $(IDIR_PMACCTD)/etc
	${INSTALL_BIN} $(WRKINST)/usr/sbin/pmacctd $(IDIR_PMACCTD)/usr/sbin/
	${INSTALL_DATA} ./files/pmacctd.conf $(IDIR_PMACCTD)/etc

pmacct-client-install:
	${INSTALL_DIR} $(IDIR_PMACCT_CLIENT)/usr/bin
	${INSTALL_BIN} $(WRKINST)/usr/bin/pmacct $(IDIR_PMACCT_CLIENT)/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
