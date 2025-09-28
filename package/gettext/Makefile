# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		gettext
PKG_VERSION:=		0.26
PKG_RELEASE:=		1
PKG_HASH:=		d1fb86e260cfe7da6031f94d2e44c0da55903dbae0a2fa0fae78c91ae1b56f00
PKG_DESCR:=		i18n tools and libs
PKG_SECTION:=		libs/misc
HOST_BUILDDEP:=		automake-host
PKG_URL:=		https://www.gnu.org/software/gettext/
PKG_SITES:=		${MASTER_SITE_GNU:=gettext/}
PKG_OPTS:=		dev
PKG_CFLINE_GETTEXT:=	depends on !ADK_TARGET_LIBC_WITHOUT_LIBICONV

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,GETTEXT,gettext,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,GETTEXT,gettext,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

gettext-install:
	$(INSTALL_DIR) $(IDIR_GETTEXT)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgettext*.so* \
		$(IDIR_GETTEXT)/usr/lib

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
