# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		tptest
PKG_VERSION:=		3.1.7
PKG_RELEASE:=		2
PKG_HASH:=		db39257b3ee6408a575e16804975df1e68f52270537cc3e7505897b777f7994d
PKG_DESCR:=		internet bandwidth tester
PKG_SECTION:=		net/perf
PKG_URL:=		http://tptest.sourceforge.net/
PKG_SITES:=		https://sourceforge.net/projects/tptest/files/tptest%20source/tptest%203.1/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,TPTEST,tptest,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

do-build:
	(cd ${WRKSRC}/apps/unix/server && ${MAKE} && ${MAKE} install DESTDIR="${WRKINST}")
	(cd ${WRKSRC}/apps/unix/client && ${MAKE} && ${MAKE} install DESTDIR="${WRKINST}")

do-install:
	$(INSTALL_DIR) $(IDIR_TPTEST)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/tptest{client,server} \
		$(IDIR_TPTEST)/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
