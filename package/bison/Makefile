# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		bison
PKG_VERSION:=		3.8.2
PKG_RELEASE:=		1
PKG_HASH:=		9bba0214ccf7f1079c5d59210045227bcf619519840ebfa80cd3849cff5a5bf2
PKG_DESCR:=		parser generator
PKG_SECTION:=		dev/tools
PKG_BUILDDEP:=		m4-host bison-host
HOST_BUILDDEP:=		m4-host 
PKG_URL:=		http://www.gnu.org/software/bison/
PKG_SITES:=		$(MASTER_SITE_GNU:=bison/)

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,BISON,bison,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,BISON,bison,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

TARGET_LDFLAGS+=	-lrt
XAKE_FLAGS+=		M4=m4

bison-install:
	$(INSTALL_DIR) $(IDIR_BISON)/usr/bin $(IDIR_BISON)/usr/share/bison
	$(INSTALL_BIN) $(WRKINST)/usr/bin/bison $(IDIR_BISON)/usr/bin
	$(INSTALL_BIN) ./files/yacc $(IDIR_BISON)/usr/bin
	$(CP) $(WRKINST)/usr/share/bison/* $(IDIR_BISON)/usr/share/bison

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
