# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		logitechmediaserver
PKG_VERSION:=		8.4.1
PKG_EXTRAVER:=		1708787582-noCPAN
PKG_RELEASE:=		1
PKG_HASH:=		b521bb7e03ee24003e718298cf54c7aac29e59a2da37d55a3380904397341802
PKG_DESCR:=		popular media server
PKG_SECTION:=		mm/audio
PKG_NEEDS:=		data
PKG_DEPENDS:=		perl p5-xml-parser p5-dbi p5-ev p5-html-parser
PKG_DEPENDS+=		p5-json-xs p5-digest-sha1 p5-yaml-xs p5-sub-name
PKG_DEPENDS+=		p5-xml-parser-expat p5-common-sense
PKG_DEPENDS+=		p5-types-serialiser p5-audio-scan p5-image-scale
PKG_DEPENDS+=		p5-dbd-sqlite p5-tie-refhash p5-template-toolkit
PKG_DEPENDS+=		p5-class-xsaccessor p5-io-interface p5-anyevent
PKG_BUILDDEP:=		perl
PKG_URL:=		http://wiki.slimdevices.com/index.php/Logitech_Media_Server
PKG_SITES:=		https://downloads.slimdevices.com/nightly/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}-${PKG_EXTRAVER}.tgz
WRKDIST=		${WRKDIR}/${PKG_NAME}-${PKG_VERSION}-${PKG_EXTRAVER}

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LOGITECHMEDIASERVER,logitechmediaserver,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

post-extract:
	rm -rf ${WRKBUILD}/CPAN/Class/XSAccessor*
	rm -rf ${WRKBUILD}/CPAN/Template*
	rm -rf ${WRKBUILD}/CPAN/HTML*
	rm -rf ${WRKBUILD}/CPAN/DBI/
	rm -rf ${WRKBUILD}/CPAN/DBI.pm
	rm -rf ${WRKBUILD}/CPAN/EV.pm
	rm -rf ${WRKBUILD}/CPAN/IO/Interface*
	rm -rf ${WRKBUILD}/CPAN/JSON/XS.pm
	rm -rf ${WRKBUILD}/CPAN/Image/

logitechmediaserver-install:
	$(INSTALL_DIR) $(IDIR_LOGITECHMEDIASERVER)/opt/lms
	$(CP) $(WRKSRC)/* $(IDIR_LOGITECHMEDIASERVER)/opt/lms
	@find $(IDIR_LOGITECHMEDIASERVER)/opt/lms -type f -exec chmod 644 {} \;
	@find $(IDIR_LOGITECHMEDIASERVER)/opt/lms -type d -exec chmod 755 {} \;
	ln -sf ../../data/lms/prefs $(IDIR_LOGITECHMEDIASERVER)/opt/lms/prefs
	ln -sf ../../data/lms/Logs $(IDIR_LOGITECHMEDIASERVER)/opt/lms/Logs
	ln -sf ../../data/lms/Cache $(IDIR_LOGITECHMEDIASERVER)/opt/lms/Cache

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
