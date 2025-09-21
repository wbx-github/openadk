# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		m4
PKG_VERSION:=		1.4.20
PKG_RELEASE:=		1
PKG_HASH:=		e236ea3a1ccf5f6c270b1c4bb60726f371fa49459a8eaaebc90b216b328daf2b
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

m4-install:
	${INSTALL_DIR} ${IDIR_M4}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/m4 ${IDIR_M4}/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
