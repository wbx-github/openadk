# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		sysvinit
PKG_VERSION:=		2.97
PKG_RELEASE:=		1
PKG_HASH:=		2d5996857519bfd8634d2e1debabb3238fb38440f65fbfdc46420ee8bdf25110
PKG_DESCR:=		systemV init
PKG_SECTION:=		base/init
PKG_URL:=		http://savannah.nongnu.org/projects/sysvinit
PKG_SITES:=		http://download.savannah.gnu.org/releases/sysvinit/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SYSVINIT,sysvinit,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
FAKE_FLAGS+=		ROOT='$(WRKINST)'

sysvinit-install:
	$(INSTALL_DIR) $(IDIR_SYSVINIT)/sbin
	$(INSTALL_BIN) $(WRKINST)/sbin/init \
		$(IDIR_SYSVINIT)/sbin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
