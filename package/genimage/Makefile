# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		genimage
PKG_VERSION:=		16
PKG_RELEASE:=		1
PKG_HASH:=		869f9662d3b778c69b1d1fe70df658e1c9e90aeda26abb753f6fe55e8b0c6e73
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
