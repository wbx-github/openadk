# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		unifdef
PKG_VERSION:=		2.12
PKG_RELEASE:=		1
PKG_HASH:=		fba564a24db7b97ebe9329713ac970627b902e5e9e8b14e19e024eb6e278d10b
PKG_DESCR:=		build utility
PKG_SECTION:=		dev/tools
PKG_SITES:=		https://dotat.at/prog/unifdef/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_CFLINE_UNIFDEF:=	depends on ADK_HOST_ONLY

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,UNIFDEF,unifdef,$(PKG_VERSION)-${PKG_RELEASE}))

HOST_STYLE:=		manual
HOST_FAKE_FLAGS+=	prefix=$(STAGING_HOST_DIR)/usr

host-configure:

host-build:
	(cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -j${ADK_MAKE_JOBS} -f ${MAKE_FILE} \
		${HOST_MAKE_FLAGS} ${HOST_ALL_TARGET}) $(MAKE_TRACE)

unifdef-hostinstall:
	cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -j${ADK_MAKE_JOBS} -f ${MAKE_FILE} \
		${HOST_FAKE_FLAGS} ${HOST_INSTALL_TARGET} $(MAKE_TRACE)

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
