# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		postfix
PKG_VERSION:=		3.2.0
PKG_RELEASE:=		1
PKG_HASH:=		420726e79622620394fd17799e49268dada7041ea067ca3aa1c8bf155b9aa487
PKG_DESCR:=		popular mail transfer agent
PKG_SECTION:=		net/mail
PKG_BUILDDEP:=		tinycdb
PKG_URL:=		http://www.postfix.org/
PKG_SITES:=		http://de.postfix.org/ftpmirror/official/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

# missing res_send support in resolver
PKG_LIBC_DEPENDS:=	glibc musl

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,POSTFIX,postfix,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
ALL_TARGET:=		
INSTALL_STYLE:=		manual

do-configure:
	(cd $(WRKBUILD) && make -f Makefile.init makefiles "CCARGS=-DNO_PCRE -DNO_NIS -DNO_DB -DHAS_CDB -I$(STAGING_TARGET_DIR)/usr/include" "AUXLIBS=$(STAGING_TARGET_DIR)/usr/lib/libcdb.a")

postfix-install:
	$(INSTALL_DIR) $(IDIR_POSTFIX)/etc/postfix
	$(CP) $(WRKBUILD)/conf/* $(IDIR_POSTFIX)/etc/postfix
	$(CP) ./files/main.cf $(IDIR_POSTFIX)/etc/postfix
	$(INSTALL_DIR) $(IDIR_POSTFIX)/usr/sbin
	$(CP) $(WRKBUILD)/bin/* $(IDIR_POSTFIX)/usr/sbin
	$(INSTALL_DIR) $(IDIR_POSTFIX)/usr/libexec/postfix
	$(CP) $(WRKBUILD)/libexec/* $(IDIR_POSTFIX)/usr/libexec/postfix

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
