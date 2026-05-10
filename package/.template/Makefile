# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

# always use tab spaces as separator, no spaces
PKG_NAME:=		@PKG@
PKG_VERSION:=		@VER@
PKG_RELEASE:=		1
PKG_HASH:=		add sha256 checksum of package here
PKG_DESCR:=		add short description
PKG_SECTION:=		add section
PKG_DEPENDS:=		add dependendant package names
PKG_BUILDDEP:=		add packages which need to be compiled
PKG_URL:=		add project url
PKG_SITES:=		add download url without package name
# alternatively use a pre-defined set of mirrors, see mk/mirrors.mk:
#PKG_SITES:=		$(MASTER_SITE_SOURCEFORGE:=sub/path/)

# if more than one binary package is created, add symbol names of all here
# leave variable empty, when no binary package is created. You can set it
# to override PKG_NAME for the main binary package 
#PKG_SUBPKGS:=		PKG SUBPKG1 SUBPKG2
# you can add separate, build depends, run depends, section and description
# build time dependency for subpackage SUBPKG1, package dir
#PKGSB_SUBPKG1:=
# runtime dependency for subpackage SUBPKG1, package names
#PKGSS_SUBPKG1:=
# section for subpackage SUBPKG1
#PKGSC_SUBPKG1:=
# description for subpackage SUBPKG1
#PKGSD_SUBPKG1:=

# define your flavours for your package here, WITH_SSL f.e.
#PKG_FLAVOURS_PKGNAME:=		WITH_SSL
# flavour description
#PKGFD_WITH_SSL:=	enable SSL support
# flavour runtime dependency, package name
#PKGFS_WITH_SSL:=	libopenssl
# flavour build time dependency, package dir
#PKGFB_WITH_SSL:=	openssl

# define your choices for your package here, f.e. different SSL implementations
#PKG_CHOICES_PKGNAME:=	WITH_OPENSSL WITH_GNUTLS
# package description for each choice
#PKGCD_WITH_OPENSSL:=	ssl support via libopenssl library
#PKGCD_WITH_GNUTLS:=	ssl support via gnutls library
# package build time dependencies
#PKGCB_WITH_OPENSSL:=	openssl
#PKGCB_WITH_GNUTLS:=	gnutls
# package runtime dependencies
#PKGCS_WITH_OPENSSL:=	libopenssl
#PKGCS_WITH_GNUTLS:=	libgnutls

# if downloaded package is not ending with .tar.xz use following
#DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,@UPKG@,@PKG@,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

#CONFIG_STYLE:=		manual
# use following to add ./configure options
#CONFIGURE_ARGS+=	--disable-foo
# override any configure variables
#CONFIGURE_ENV+=	ac_cv_func_setpgrp_void=yes
#BUILD_STYLE:=		manual
#INSTALL_STYLE:=	manual

# please install all files and directories to the package dir
@PKG@-install:
	$(INSTALL_DIR) $(IDIR_@UPKG@)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/@PKG@ \
		$(IDIR_@UPKG@)/usr/bin

# please remove ALL above comments, before commiting
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
