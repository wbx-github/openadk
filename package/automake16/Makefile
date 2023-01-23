# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		automake16
PKG_VERSION:=		1.16.3
PKG_EXTRAVER:=		1.16
PKG_RELEASE:=		1
PKG_HASH:=		ff2bf7656c4d1c6fdda3b8bebb21f09153a736bcba169aaf65eab25fa113bf3a
PKG_DESCR:=		tool for automatically generating makefiles
PKG_SECTION:=		dev/tools
PKG_BUILDDEP:=		m4-host autoconf-host autoconf
HOST_BUILDDEP:=		autoconf-host
PKG_URL:=		http://www.gnu.org/software/automake/
PKG_SITES:=		$(MASTER_SITE_GNU:=automake/)
PKG_OPTS:=		noscripts

DISTFILES:=		automake-${PKG_VERSION}.tar.xz

WRKDIST=		${WRKDIR}/automake-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,AUTOMAKE16,automake16,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,AUTOMAKE16,automake16,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

XAKE_FLAGS+=		PERL="/usr/bin/perl"

automake16-install:
	$(INSTALL_DIR) $(IDIR_AUTOMAKE16)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/automake $(IDIR_AUTOMAKE16)/usr/bin/automake16
	$(INSTALL_BIN) $(WRKINST)/usr/bin/aclocal $(IDIR_AUTOMAKE16)/usr/bin/aclocal16
	$(INSTALL_DIR) $(IDIR_AUTOMAKE16)/usr/share/aclocal-$(PKG_EXTRAVER)
	$(CP) $(WRKINST)/usr/share/aclocal-$(PKG_EXTRAVER) \
		$(IDIR_AUTOMAKE16)/usr/share
	$(INSTALL_DIR) $(IDIR_AUTOMAKE16)/usr/share/automake-$(PKG_EXTRAVER)
	$(CP) $(WRKINST)/usr/share/automake-$(PKG_EXTRAVER) \
		$(IDIR_AUTOMAKE16)/usr/share

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
