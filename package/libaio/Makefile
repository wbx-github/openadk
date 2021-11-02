# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libaio
PKG_VERSION:=		0.3.112
PKG_RELEASE:=		1
PKG_HASH:=		b7cf93b29bbfb354213a0e8c0e82dfcf4e776157940d894750528714a0af2272
PKG_DESCR:=		Asynchronous input/output library that uses the kernels native interface
PKG_SECTION:=		libs/misc
PKG_URL:=		https://pagure.io/libaio
PKG_SITES:=		https://pagure.io/libaio/archive/libaio-${PKG_VERSION}/

DISTFILES:=             $(PKG_NAME)-$(PKG_NAME)-$(PKG_VERSION).tar.gz
WRKDIST=		$(WRKDIR)/$(PKG_NAME)-$(PKG_NAME)-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBAIO,libaio,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual

libaio-install:
	$(INSTALL_DIR) $(IDIR_LIBAIO)/usr/lib
	${CP} ${WRKINST}/usr/lib/libaio*.so* ${IDIR_LIBAIO}/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
