# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

# always use tab spaces as separator, no spaces
PKG_NAME:=		p5-parse-yapp
PKG_VERSION:=		1.21
PKG_RELEASE:=		1
PKG_HASH:=		3810e998308fba2e0f4f26043035032b027ce51ce5c8a52a8b8e340ca65f13e5
PKG_DESCR:=		Parse Yapp
PKG_SECTION:=		dev/perl
PKG_DEPENDS:=		perl
PKG_BUILDDEP:=		perl-host perl
HOST_BUILDDEP:=		perl-host
PKG_SITES:=		https://cpan.metacpan.org/authors/id/W/WB/WBRASWELL/

DISTFILES:=		Parse-Yapp-${PKG_VERSION}.tar.gz
WRKDIST=		${WRKDIR}/Parse-Yapp-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,P5_PARSE_YAPP,p5-parse-yapp,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,P5_PARSE_YAPP,p5-parse-yapp,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

include $(ADK_TOPDIR)/mk/perl.mk

HOST_STYLE:=		perl
CONFIG_STYLE:=		perl
XAKE_FLAGS+=		$(PERL_ENV)

hostpost-install:
	(cd $(WRKBUILD) && PATH='$(HOST_PATH)' $(HOST_PERL_ENV) make install)

p5-parse-yapp-install:
	$(INSTALL_DIR) $(IDIR_P5_PARSE_YAPP)$(PERL_SITEDIR)
	$(CP) $(WRKINST)$(PERL_SITEDIR)/* \
		$(IDIR_P5_PARSE_YAPP)$(PERL_SITEDIR)

include ${ADK_TOPDIR}/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
