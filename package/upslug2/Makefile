# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		upslug2
PKG_VERSION:=		5ce4239b8e6da802904b30aaa2ebcc7bc25d0200
PKG_RELEASE:=		1
PKG_HASH:=		af254788be98861f2bd9103fe6e60a774ec96a8c374744eef9197f6043075afa
PKG_DESCR:=		flash utility for Linksys NSLU2
PKG_SECTION:=		dev/tools
PKG_SITES:=		https://github.com/nslu2-linux/UpSlug2.git

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_CFLINE_UPSLUG2:=	depends on ADK_HOST_ONLY

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,UPSLUG2,upslug2,$(PKG_VERSION)-${PKG_RELEASE}))

AUTOTOOL_STYLE:=	autoreconf
HOST_STYLE:=		auto

upslug2-hostinstall:
	cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_FAKE_FLAGS} ${HOST_INSTALL_TARGET} $(MAKE_TRACE)

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
