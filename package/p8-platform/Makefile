# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		p8-platform
PKG_VERSION:=		2.1.0.1
PKG_RELEASE:=		1
PKG_HASH:=		064f8d2c358895c7e0bea9ae956f8d46f3f057772cb97f2743a11d478a0f68a0
PKG_DESCR:=		platform library used by libcec
PKG_SECTION:=		libs/misc
PKG_URL:=		https://github.com/Pulse-Eight/platform
PKG_SITES:=		https://github.com/Pulse-Eight/platform/archive/refs/tags/
PKG_LIBNAME:=		libplatform
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
WRKDIST=		$(WRKDIR)/platform-$(PKG_NAME)-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,P8_PLATFORM,p8-platform,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		cmake

p8-platform-install:
	:

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
