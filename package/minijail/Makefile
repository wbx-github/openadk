# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		minijail
PKG_VERSION:=		v17
PKG_RELEASE:=		1
PKG_HASH:=		1ee5a5916491a32c121c7422b4d8c16481c0396a3acab34bf1c44589dcf810ae
PKG_DESCR:=		sandboxing and containment tool
PKG_SECTION:=		sys/misc
PKG_DEPENDS:=		libcap
PKG_BUILDDEP:=		libcap
PKG_URL:=		https://google.github.io/minijail/
PKG_SITES:=		https://github.com/google/minijail/archive/refs/tags/

DISTFILES:=             linux-$(PKG_VERSION).tar.gz
WRKDIST=		${WRKDIR}/${PKG_NAME}-linux-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MINIJAIL,minijail,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

minijail-install:
	$(INSTALL_DIR) $(IDIR_MINIJAIL)/lib
	$(CP) $(WRKBUILD)/libminijailpreload.so \
		$(IDIR_MINIJAIL)/lib
	$(INSTALL_DIR) $(IDIR_MINIJAIL)/lib
	$(CP) $(WRKBUILD)/libminijail.so \
		$(IDIR_MINIJAIL)/lib
	$(INSTALL_DIR) $(IDIR_MINIJAIL)/usr/bin
	$(INSTALL_BIN) $(WRKBUILD)/minijail0 \
		$(IDIR_MINIJAIL)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
