# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		git
PKG_VERSION:=		2.39.1
PKG_RELEASE:=		1
PKG_HASH:=		40a38a0847b30c371b35873b3afcf123885dd41ea3ecbbf510efa97f3ce5c161
PKG_DESCR:=		fast version control system
PKG_SECTION:=		dev/scm
PKG_BUILDDEP:=		curl expat libressl
PKG_DEPENDS:=		curl libexpat libressl
PKG_NEEDS:=		threads
PKG_URL:=		http://git-scm.com/
PKG_SITES:=		https://www.kernel.org/pub/software/scm/git/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,GIT,git,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autoreconf
XAKE_FLAGS+=		NO_PERL=1 NO_NSEC=1 NO_TCLTK=1 NO_PYTHON=1 \
			NO_INSTALL_HARDLINKS=1 NO_GETTEXT=1 NO_ICONV=1 \
			CURLDIR=${STAGING_TARGET_DIR} \
			EXPATDIR=${STAGING_TARGET_DIR}
XAKE_FLAGS+=		uname_S=Linux uname_O=GNU/Linux
CONFIGURE_ARGS+=	--without-iconv
CONFIGURE_ENV+=		ac_cv_c_c99_format=yes \
			ac_cv_fread_reads_directories=no \
			ac_cv_snprintf_returns_bogus=no

git-install:
	$(INSTALL_DIR) $(IDIR_GIT)/usr/bin $(IDIR_GIT)/usr/libexec/git-core
	$(INSTALL_DIR) $(IDIR_GIT)/usr/share/git-core/templates
	$(CP) $(WRKINST)/usr/share/git-core/templates/* \
		$(IDIR_GIT)/usr/share/git-core/templates
	$(CP) $(WRKINST)/usr/bin/git $(IDIR_GIT)/usr/bin
	$(CP) $(WRKINST)/usr/bin/git-shell $(IDIR_GIT)/usr/bin
	$(CP) $(WRKINST)/usr/bin/git-receive-pack $(IDIR_GIT)/usr/bin
	$(CP) $(WRKINST)/usr/bin/git-upload-pack $(IDIR_GIT)/usr/bin
	$(CP) $(WRKINST)/usr/bin/git-upload-archive $(IDIR_GIT)/usr/bin
	${CP} $(WRKINST)/usr/libexec/git-core/* $(IDIR_GIT)/usr/libexec/git-core

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
