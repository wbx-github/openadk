# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		gawk
PKG_VERSION:=		5.4.0
PKG_RELEASE:=		1
PKG_HASH:=		3dd430f0cd3b4428c6c3f6afc021b9cd3c1f8c93f7a688dc268ca428a90b4ac1
PKG_DESCR:=		awk programming language interpreter
PKG_SECTION:=		base/tools
PKG_URL:=		http://www.gnu.org/software/gawk/
PKG_SITES:=		${MASTER_SITE_GNU:=gawk/}
PKG_BB:=		1

PKG_LIBC_DEPENDS:=	glibc musl

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,GAWK,gawk,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,GAWK,gawk,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

HOST_CONFIGURE_ARGS+=	--disable-shared

gawk-install:
	${INSTALL_DIR} ${IDIR_GAWK}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/gawk ${IDIR_GAWK}/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
