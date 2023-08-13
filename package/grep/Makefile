# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		grep
PKG_VERSION:=		3.0
PKG_RELEASE:=		2
PKG_HASH:=		e2c81db5056e3e8c5995f0bb5d0d0e1cad1f6f45c3b2fc77b6e81435aed48ab5
PKG_DESCR:=		global search for a regex
PKG_SECTION:=		base/tools
PKG_DEPENDS:=		libpcre
PKG_BUILDDEP:=		pcre
HOST_BUILDDEP:=		pcre-host
PKG_URL:=		http://www.gnu.org/software/grep/
PKG_SITES:=		${MASTER_SITE_GNU:=grep/}
PKG_NOPARALLEL:=	1
PKG_BB:=		1

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,GREP,grep,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,GREP,grep,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

grep-install:
	$(INSTALL_DIR) $(IDIR_GREP)/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/{e,f,}grep \
		$(IDIR_GREP)/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
