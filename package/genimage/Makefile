# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		genimage
PKG_VERSION:=		17
PKG_RELEASE:=		1
PKG_HASH:=		a8756e3567a0d4d82c36b08ccc1e088250b9006d5670c6b2b014185e6ec60671
PKG_DESCR:=		image creation utility
PKG_SECTION:=		dev/tools
HOST_BUILDDEP:=		confuse-host
PKG_URL:=		http://public.pengutronix.de/software/genimage/
PKG_SITES:=		http://public.pengutronix.de/software/genimage/

PKG_CFLINE_GENIMAGE:=	depends on ADK_HOST_ONLY

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,GENIMAGE,genimage,$(PKG_VERSION)-${PKG_RELEASE}))

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
