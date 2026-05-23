# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		obexftp
PKG_VERSION:=		0.24
PKG_RELEASE:=		1
PKG_HASH:=		b907965608bf0e60c69bc45f074ce1a2ffeb809b4502a7082c6d95e3c73dfe6b
PKG_DESCR:=		bluetooth ftp application
PKG_SECTION:=		sys/misc
PKG_DEPENDS:=		openobex libobexftp
PKG_BUILDDEP:=		openobex
PKG_URL:=		http://dev.zuckschwerdt.org/openobex/wiki/ObexFtp
PKG_SITES:=		https://sourceforge.net/projects/openobex/files/obexftp/$(PKG_VERSION)/
PKG_LIBNAME:=		libobexftp
PKG_OPTS:=		dev

PKG_SUBPKGS:=		OBEXFTP LIBOBEXFTP
PKGSC_LIBOBEXFTP:=	libs/net
PKGSD_LIBOBEXFTP:=	obex ftp library

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}-Source.tar.gz
WRKDIST=		$(WRKDIR)/${PKG_NAME}-${PKG_VERSION}-Source

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,OBEXFTP,obexftp,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIBOBEXFTP,libobexftp,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_LIBOBEXFTP},${PKGSC_LIBOBEXFTP},${PKG_OPTS}))

CONFIG_STYLE:=          cmake
CMAKE_FLAGS:=		-DENABLE_PERL=NO -DENABLE_PYTHON=NO -DENABLE_RUBY=NO -DENABLE_TCL=NO

obexftp-install:
	${INSTALL_DIR} ${IDIR_OBEXFTP}/usr/bin
	${CP} ${WRKINST}/usr/bin/obexftp{,d} ${IDIR_OBEXFTP}/usr/bin/

libobexftp-install:
	${INSTALL_DIR} ${IDIR_LIBOBEXFTP}/usr/lib
	${CP} ${WRKINST}/usr/lib/*.so* ${IDIR_LIBOBEXFTP}/usr/lib/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
