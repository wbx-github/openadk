# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		raddump
PKG_VERSION:=		0.3.1
PKG_RELEASE:=		1
PKG_HASH:=		f2d5c80164a5064d25e112f3ead9952d86200b022da584bddbc4afea948cb970
PKG_DESCR:=		interprets captured radius packets
PKG_SECTION:=		net/radius
PKG_DEPENDS:=		libpcap libopenssl
PKG_BUILDDEP:=		libpcap openssl
PKG_URL:=		http://sourceforge.net/projects/raddump
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=raddump/}

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,RADDUMP,raddump,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=		ac_cv_func_malloc_0_nonnull=yes

raddump-install:
	${INSTALL_DIR} ${IDIR_RADDUMP}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/raddump ${IDIR_RADDUMP}/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
