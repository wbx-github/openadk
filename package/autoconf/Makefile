# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		autoconf
PKG_VERSION:=		2.72
PKG_RELEASE:=		1
PKG_HASH:=		ba885c1319578d6c94d46e9b0dceb4014caafe2490e437a0dbca3f270a223f5a
PKG_DESCR:=		automatically configure software source code packages
PKG_SECTION:=		dev/tools
HOST_BUILDDEP:=		m4-host
PKG_URL:=		http://www.gnu.org/software/autoconf/
PKG_SITES:=		${MASTER_SITE_GNU:=autoconf/}
PKG_OPTS:=		noscripts

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,AUTOCONF,autoconf,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,AUTOCONF,autoconf,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

XAKE_FLAGS+=		PERL="/usr/bin/perl"

autoconf-install:
	${INSTALL_DIR} ${IDIR_AUTOCONF}/usr/bin
	${INSTALL_DIR} ${IDIR_AUTOCONF}/usr/share/autoconf
	${CP} ${WRKINST}/usr/bin/auto* ${IDIR_AUTOCONF}/usr/bin
	${CP} ${WRKINST}/usr/share/autoconf/* \
		${IDIR_AUTOCONF}/usr/share/autoconf

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
