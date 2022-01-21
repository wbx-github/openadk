# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		bash
PKG_VERSION:=		5.1.16
PKG_RELEASE:=		1
PKG_HASH:=		5bac17218d3911834520dad13cd1f85ab944e1c09ae1aba55906be1f8192f558
PKG_DESCR:=		bourne-again shell
PKG_SECTION:=		base/shells
PKG_URL:=		http://www.gnu.org/software/bash/
PKG_SITES:=		http://ftp.gnu.org/gnu/bash/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_CHOICES_BASH:=	WITH_CURSES WITH_TERMCAP
PKGCD_WITH_CURSES:=	use curses library instead of termcap
PKGCS_WITH_CURSES:=	libncurses
PKGCB_WITH_CURSES:=	ncurses
PKGCD_WITH_TERMCAP:=	use termcap library instead of curses

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,BASH,bash,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=		bash_cv_getenv_redef=no \
			bash_cv_job_control_missing=yes
CONFIGURE_ARGS+=	--disable-rpath \
			--without-bash-malloc \
			--cache-file=/dev/null \
			--enable-job-control \
			--enable-history
ifneq (${ADK_PACKAGE_BASH_WITH_CURSES},)
CONFIGURE_ARGS+=	--with-curses
endif
XAKE_FLAGS+=		LIBS_FOR_BUILD=''

bash-install:
	$(INSTALL_DIR) $(IDIR_BASH)/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/bash $(IDIR_BASH)/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
