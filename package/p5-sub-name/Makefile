# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		p5-sub-name
PKG_VERSION:=		0.27
PKG_RELEASE:=		1
PKG_HASH:=		ecf36fba1c47ca93e1daa394968ed39c4186867459d9cd173c421e2b972043e8
PKG_DESCR:=		rename a sub
PKG_SECTION:=		dev/perl
PKG_DEPENDS:=		perl
PKG_BUILDDEP:=		perl-host perl
PKG_SITES:=		https://cpan.metacpan.org/authors/id/E/ET/ETHER/

DISTFILES:=             Sub-Name-${PKG_VERSION}.tar.gz
WRKDIST=		${WRKDIR}/Sub-Name-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,P5_SUB_NAME,p5-sub-name,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

include $(ADK_TOPDIR)/mk/perl.mk

CONFIG_STYLE:=		perl
XAKE_FLAGS+=		$(PERL_ENV)

p5-sub-name-install:
	$(INSTALL_DIR) $(IDIR_P5_SUB_NAME)$(PERL_SITEDIR)
	$(CP) $(WRKINST)$(PERL_SITEDIR)/* \
		$(IDIR_P5_SUB_NAME)$(PERL_SITEDIR)

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
