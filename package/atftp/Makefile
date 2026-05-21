# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		atftp
PKG_VERSION:=		0.8.1
PKG_RELEASE:=		1
PKG_HASH:=		96cbdbd2f16615c89c9db36be9b306de176d9a1c03dcb8cb777625bfe068bc2b
PKG_DESCR:=		tftp client
PKG_SECTION:=		net/misc
PKG_DEPENDS:=		libreadline libncurses
PKG_BUILDDEP:=		readline ncurses
PKG_URL:=		http://sourceforge.net/projects/atftp/
PKG_SITES:=		https://sourceforge.net/projects/atftp/files/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		ATFTP ATFTPD
PKGSD_ATFTPD:=		tftp server
PKGSS_ATFTPD:=		libreadline libncurses

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ATFTP,atftp,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,ATFTPD,atftpd,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_ATFTPD},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--disable-libpcre

atftp-install:
	$(INSTALL_DIR) $(IDIR_ATFTP)/usr/bin
	$(INSTALL_BIN) $(WRKBUILD)/atftp $(IDIR_ATFTP)/usr/bin

atftpd-install:
	$(INSTALL_DIR) $(IDIR_ATFTPD)/usr/sbin
	$(INSTALL_BIN) $(WRKBUILD)/atftpd $(IDIR_ATFTPD)/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
