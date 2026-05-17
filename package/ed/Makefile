# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		ed
PKG_VERSION:=		1.22.5
PKG_RELEASE:=		1
PKG_HASH:=		56e107ddc2f29dad6690376c15bf9751509e1ee3b8241710e44edbe5c3a158cc
PKG_DESCR:=		unix editor
PKG_SECTION:=		app/editor
PKG_BUILDDEP+=		lzip-host
HOST_BUILDDEP+=		lzip-host
PKG_URL:=		http://www.gnu.org/software/ed/ed.html
PKG_SITES:=		${MASTER_SITE_GNU:=ed/}

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.lz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,ED,ed,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,ED,ed,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

ed-install:
	$(INSTALL_DIR) $(IDIR_ED)/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/ed \
		$(IDIR_ED)/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
