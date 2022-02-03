# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		m4
PKG_VERSION:=		1.4.19
PKG_RELEASE:=		1
PKG_HASH:=		63aede5c6d33b6d9b13511cd0be2cac046f2e70fd0a07aa9573a04a82783af96
PKG_DESCR:=		macro processor
PKG_SECTION:=		dev/tools
PKG_BUILDDEP:=		m4-host
HOST_BUILDDEP:=		xz-host
PKG_URL:=		http://www.gnu.org/software/m4/
PKG_SITES:=		${MASTER_SITE_GNU:=m4/}

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,M4,m4,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,M4,m4,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=		ac_cv_func_posix_spawn=yes \
			ac_cv_func_posix_spawn_works=yes
TARGET_LDFLAGS+=	-lrt

m4-install:
	${INSTALL_DIR} ${IDIR_M4}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/m4 ${IDIR_M4}/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
