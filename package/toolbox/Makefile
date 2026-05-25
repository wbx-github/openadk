# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		toolbox
PKG_VERSION:=		1.0
PKG_RELEASE:=		1
PKG_DESCR:=		openadk toolbox for very small systems
PKG_SECTION:=		base/apps

NO_DISTFILES:=		1

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,TOOLBOX,toolbox,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual

toolbox-install:
	$(INSTALL_DIR) $(IDIR_TOOLBOX)/bin
	$(CP) $(WRKINST)/bin/* $(IDIR_TOOLBOX)/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
