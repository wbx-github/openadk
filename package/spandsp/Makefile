# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		spandsp
PKG_VERSION:=		7b0b8cf3d42b725405bcc63145de5e280265ce4e
PKG_GIT:=		hash
PKG_RELEASE:=		1
PKG_DESCR:=		dsp library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		libtiff
PKG_DEPENDS:=		libtiff
PKG_SITES:=		https://github.com/freeswitch/spandsp.git
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SPANDSP,spandsp,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

AUTOTOOL_STYLE:=	autogen
CONFIGURE_ENV+=		ac_cv_func_realloc_0_nonnull=yes
CONFIGURE_ENV+=		ac_cv_func_malloc_0_nonnull=yes

spandsp-install:
	$(INSTALL_DIR) $(IDIR_SPANDSP)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libspandsp*.so* \
		$(IDIR_SPANDSP)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
