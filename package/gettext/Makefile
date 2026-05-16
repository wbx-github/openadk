# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		gettext
PKG_VERSION:=		1.0
PKG_RELEASE:=		1
PKG_HASH:=		71132a3fb71e68245b8f2ac4e9e97137d3e5c02f415636eb508ae607bc01add7
PKG_DESCR:=		i18n tools and libs
PKG_SECTION:=		libs/misc
HOST_BUILDDEP:=		automake-host
PKG_URL:=		https://www.gnu.org/software/gettext/
PKG_SITES:=		${MASTER_SITE_GNU:=gettext/}
PKG_OPTS:=		dev

PKG_LIBC_DEPENDS:=	glibc musl

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
