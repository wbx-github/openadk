# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		cpio
PKG_VERSION:=		2.15
PKG_RELEASE:=		1
PKG_HASH:=		efa50ef983137eefc0a02fdb51509d624b5e3295c980aa127ceee4183455499e
PKG_DESCR:=		archive utility
PKG_SECTION:=		app/archive
PKG_URL:=		http://www.gnu.org/software/cpio/
PKG_SITES:=		${MASTER_SITE_GNU:=cpio/}
PKG_BB:=		1

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,CPIO,cpio,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,CPIO,cpio,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

cpio-install:
	${INSTALL_DIR} ${IDIR_CPIO}/usr/bin
	${CP} ${WRKINST}/usr/bin/cpio ${IDIR_CPIO}/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
