# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		netcat-openbsd
PKG_VERSION:=		1.217
PKG_RELEASE:=		1
PKG_HASH:=		fcb551d9987fd51d020c62b6d81df0c2bb17ce1887bbc3fda4d28313791cc0f5
PKG_DESCR:=		openbsd netcat
PKG_SECTION:=		net/misc
PKG_BUILDDEP:=		libbsd
PKG_DEPENDS:=		libbsd
PKG_SITES:=		http://deb.debian.org/debian/pool/main/n/netcat-openbsd/

NO_DISTFILES:=		1

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,NETCAT_OPENBSD,netcat-openbsd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

netcat-openbsd-install:
	$(INSTALL_DIR) $(IDIR_NETCAT_OPENBSD)/usr/bin
	$(INSTALL_BIN) $(WRKBUILD)/nc \
		$(IDIR_NETCAT_OPENBSD)/usr/bin/netcat-openbsd

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
