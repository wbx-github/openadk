# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		perl
PKG_VERSION:=		5.38.0
PKG_RELEASE:=		1
PKG_HASH:=		eca551caec3bc549a4e590c0015003790bdd1a604ffe19cc78ee631d51f7072e
PKG_DESCR:=		perl interpreter
PKG_SECTION:=		dev/lang
PKG_NEEDS:=		threads
PKG_URL:=		http://www.perl.org/
PKG_SITES:=		http://www.cpan.org/src/
PKG_NOPARALLEL:=	1

PC_VERSION:=		1.5
PC_SITE:=		https://github.com/arsv/perl-cross/releases/download/$(PC_VERSION)

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,PERL,perl,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,PERL,perl,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

HOST_STYLE:=		manual
INSTALL_TARGET:=	install.perl
CONFIG_STYLE:=		minimal
CONFIGURE_ARGS:=	--target=$(GNU_TARGET_NAME) \
			--target-tools-prefix=$(TARGET_CROSS) \
			--prefix=/usr \
			-Dld="$(TARGET_CC)" \
			-Dccflags="$(TARGET_CFLAGS)" \
			-Dldflags="$(TARGET_LDFLAGS) -lm" \
			-Dmydomain="" \
			-Dmyuname="$(ADK_VENDOR)" \
			-Dosname=linux \
			-Dosvers=4.0 \
			-Dperladmin=root

ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
CONFIGURE_ARGS+=	--all-static --no-dynaloader
endif

host-configure:
	(cd ${WRKBUILD}; ${BASH} ./Configure -des -Duseperlio -Dprefix=${STAGING_HOST_DIR}/usr)

perl-hostinstall:
	(cd ${WRKBUILD} && env CC_FOR_BUILD="gcc" ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_MAKE_FLAGS} ${HOST_INSTALL_TARGET}) 
	mv ${STAGING_HOST_DIR}/usr/bin/perl ${STAGING_HOST_DIR}/usr/bin/perl-host

pre-configure:
	(if [ ! -f $(DL_DIR)/perl-cross-$(PC_VERSION).tar.gz ]; then \
		cd $(DL_DIR); wget $(PC_SITE)/perl-cross-$(PC_VERSION).tar.gz; \
	fi)
	(cd $(WRKSRC); tar --strip-components=1 -xf $(DL_DIR)/perl-cross-$(PC_VERSION).tar.gz)

perl-install:
	${INSTALL_DIR} ${IDIR_PERL}/usr/bin
	${INSTALL_DIR} ${IDIR_PERL}/usr/lib/perl5/${PKG_VERSION}
	${CP} ${WRKINST}/usr/lib/perl5/${PKG_VERSION}/* \
		${IDIR_PERL}/usr/lib/perl5/${PKG_VERSION}
	${INSTALL_BIN} ${WRKINST}/usr/bin/perl ${IDIR_PERL}/usr/bin/
	rm -rf $(IDIR_PERL)/usr/lib/perl5/pod
	find $(IDIR_PERL)/usr/lib/perl5/ -name 'extralibs.ld' -print0 | xargs -0 rm -f
	find $(IDIR_PERL)/usr/lib/perl5/ -name '*.bs' -print0 | xargs -0 rm -f
	find $(IDIR_PERL)/usr/lib/perl5/ -name '.packlist' -print0 | xargs -0 rm -f

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
