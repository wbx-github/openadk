# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		consolekit2
PKG_VERSION:=		1.2.6
PKG_RELEASE:=		1
PKG_HASH:=		d41224129c5a689469ebd8fe87e34c4a76afdb7b2f6201eb246320262ea5a942
PKG_DESCR:=		session manager
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		pam
PKG_BUILDDEP:=		pam
PKG_SITES:=		https://github.com/ConsoleKit2/ConsoleKit2/archive/refs/tags/$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz
WRKDIST=		$(WRKDIR)/ConsoleKit2-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,CONSOLEKIT2,consolekit2,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ENV+=		ac_cv_file__sys_class_tty_tty0_active=yes
CONFIGURE_ARGS+=	--enable-pam-module --with-pam-module-dir=/usr/lib/security

post-extract:
	touch $(WRKSRC)/gtk-doc.make

consolekit2-install:
	$(INSTALL_DIR) $(IDIR_CONSOLEKIT2)/etc
	$(CP) $(WRKINST)/etc/* \
		$(IDIR_CONSOLEKIT2)/etc
	$(INSTALL_DIR) $(IDIR_CONSOLEKIT2)/usr/lib
	$(CP) $(WRKINST)/usr/lib/lib*.so* \
		$(IDIR_CONSOLEKIT2)/usr/lib
	$(CP) $(WRKINST)/usr/lib/ConsoleKit \
		$(IDIR_CONSOLEKIT2)/usr/lib
	$(INSTALL_DIR) $(IDIR_CONSOLEKIT2)/usr/libexec
	$(CP) $(WRKINST)/usr/libexec/* \
		$(IDIR_CONSOLEKIT2)/usr/libexec
	$(INSTALL_DIR) $(IDIR_CONSOLEKIT2)/usr/share
	$(CP) $(WRKINST)/usr/share/* \
		$(IDIR_CONSOLEKIT2)/usr/share
	$(INSTALL_DIR) $(IDIR_CONSOLEKIT2)/usr/sbin
	$(CP) $(WRKINST)/usr/sbin/* \
		$(IDIR_CONSOLEKIT2)/usr/sbin
	$(INSTALL_DIR) $(IDIR_CONSOLEKIT2)/usr/bin
	$(CP) $(WRKINST)/usr/bin/* \
		$(IDIR_CONSOLEKIT2)/usr/bin
	$(INSTALL_DIR) $(IDIR_CONSOLEKIT2)/usr/lib/security
	$(CP) $(WRKINST)/usr/lib/security/* \
		$(IDIR_CONSOLEKIT2)/usr/lib/security

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
