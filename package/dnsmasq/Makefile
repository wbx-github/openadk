# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		dnsmasq
PKG_VERSION:=		2.87
PKG_RELEASE:=		1
PKG_HASH:=		0228c0364a7f2356fd7e7f1549937cbf3099a78d3b2eb1ba5bb0c31e2b89de7a
PKG_DESCR:=		lightweight dns, dhcp and tftp server
PKG_SECTION:=		net/dns
PKG_KDEPENDS:=		inotify-user
PKG_URL:=		http://thekelleys.org.uk/dnsmasq/
PKG_SITES:=		http://thekelleys.org.uk/dnsmasq/
PKG_NOPARALLEL:=	1

PKG_FLAVOURS_DNSMASQ:=	PXE
PKGFD_PXE:=		enable pxe network boot
PKGFS_PXE:=		pxelinux
PKGFB_PXE:=		syslinux

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,DNSMASQ,dnsmasq,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,DNSMASQ,dnsmasq,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

HOST_STYLE:=		manual
CONFIG_STYLE:=		manual

host-build:
	cd ${WRKBUILD} && make	

dnsmasq-hostinstall:
	(cd $(WRKBUILD); make PREFIX=${STAGING_HOST_DIR}/usr install)

dnsmasq-install:
	${INSTALL_DIR} ${IDIR_DNSMASQ}/usr/sbin ${IDIR_DNSMASQ}/etc
	${INSTALL_BIN} ${WRKINST}/usr/sbin/dnsmasq ${IDIR_DNSMASQ}/usr/sbin
	${INSTALL_DATA} ./files/dnsmasq.conf ${IDIR_DNSMASQ}/etc/dnsmasq.conf

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
