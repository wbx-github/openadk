# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		zip
PKG_VERSION:=		3.0
PKG_RELEASE:=		1
PKG_HASH:=		f0e8bb1f9b7eb0b01285495a2699df3a4b766784c1765a8f1aeedf63c0806369
PKG_DESCR:=		zip compression utility
PKG_SECTION:=		app/archive
PKG_URL:=		http://www.info-zip.org/Zip.html
PKG_SITES:=		ftp://ftp.info-zip.org/pub/infozip/src/

PKG_CFLINE_ZIP:=	depends on ADK_HOST_ONLY

WRKDIST=		$(WRKDIR)/$(PKG_NAME)30
DISTFILES:=		$(PKG_NAME)30.tgz

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,ZIP,zip,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,ZIP,zip,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

HOST_STYLE:=		manual
CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

TARGET_CPPFLAGS+=	-DNO_BZIP2_SUPPORT
CONFIGURE_PROG:=	unix/configure
MAKE_FILE:=		unix/Makefile
ALL_TARGET:=		generic_gcc

host-build:
	(cd ${WRKBUILD} && env ${HOST_MAKE_ENV} CC="$(HOST_CC) -std=gnu89" ${MAKE} -f ${MAKE_FILE} \
		${HOST_MAKE_FLAGS} ${ALL_TARGET})

zip-hostinstall:
	$(CP) $(WRKBUILD)/zip \
		$(STAGING_HOST_DIR)/usr/bin

zip-install:
	${INSTALL_DIR} ${IDIR_ZIP}/usr/bin
	${INSTALL_BIN} ${WRKBUILD}/zip ${IDIR_ZIP}/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
