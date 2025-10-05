# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libsquish
PKG_VERSION:=		1.15
PKG_RELEASE:=		1
PKG_HASH:=		628796eeba608866183a61d080d46967c9dda6723bc0a3ec52324c85d2147269
PKG_DESCR:=		c++ compression library
PKG_SECTION:=		libs/misc
PKG_SITES:=		http://downloads.sourceforge.net/project/libsquish/
PKG_OPTS:=		dev

WRKDIST=		${WRKDIR}/
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tgz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBSQUISH,libsquish,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		manual
XAKE_FLAGS+=		INSTALL_DIR="${WRKINST}/usr"

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
