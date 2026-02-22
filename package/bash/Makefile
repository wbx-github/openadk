# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		bash
PKG_VERSION:=		5.3
PKG_RELEASE:=		1
PKG_HASH:=		0d5cd86965f869a26cf64f4b71be7b96f90a3ba8b3d74e27e8e9d9d5550f31ba
PKG_DESCR:=		bourne-again shell
PKG_SECTION:=		base/shells
PKG_URL:=		http://www.gnu.org/software/bash/
PKG_SITES:=		http://ftp.gnu.org/gnu/bash/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,BASH,bash,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=		bash_cv_getenv_redef=no \
			bash_cv_job_control_missing=yes
CONFIGURE_ARGS+=	--disable-rpath \
			--without-bash-malloc \
			--cache-file=/dev/null \
			--enable-job-control \
			--enable-history
XAKE_FLAGS+=		LIBS_FOR_BUILD=''

bash-install:
	$(INSTALL_DIR) $(IDIR_BASH)/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/bash $(IDIR_BASH)/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
