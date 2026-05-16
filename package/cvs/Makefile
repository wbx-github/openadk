# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		cvs
PKG_VERSION:=		1.11.23
PKG_RELEASE:=		2
PKG_HASH:=		0ad692e3c22e4b33274a53ad22a194deb3024ec833b9e87ad7968d9b0b58cdcf
PKG_DESCR:=		concurrent version system
PKG_SECTION:=		dev/scm
PKG_URL:=		http://www.nongnu.org/cvs/
PKG_SITES:=		http://ftp.gnu.org/non-gnu/cvs/source/stable/${PKG_VERSION}/

PKG_CFLINE_CVS:=	depends on ADK_BROKEN

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,CVS,cvs,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=		ac_cv_lib_nsl_main=no
CONFIGURE_ARGS+=	--without-gssapi

cvs-install:
	$(INSTALL_DIR) $(IDIR_CVS)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/cvs \
		$(IDIR_CVS)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
