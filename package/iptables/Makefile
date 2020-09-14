# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		iptables
PKG_VERSION:=		1.8.5
PKG_RELEASE:=		1
PKG_HASH:=		d457d74512e63aa3f50336e0597d4023c0e3c6845594d38532efb6ebcb294309
PKG_DESCR:=		netfilter firewalling software
PKG_SECTION:=		net/firewall
PKG_DEPENDS:=		libnetfilter_conntrack libmnl libnfnetlink
PKG_KDEPENDS:=		ip-nf-iptables ip-nf-filter ip-nf-nat nf-conntrack-ipv4
PKG_KDEPENDS+=		ip-nf-target-reject ip-nf-target-masquerade
PKG_BUILDDEP:=		libnetfilter_conntrack pkgconf-host
PKG_URL:=		http://www.netfilter.org/
PKG_SITES:=		http://www.netfilter.org/projects/iptables/files/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.bz2

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,IPTABLES,iptables,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

TARGET_LDFLAGS+=	-fPIC
CONFIGURE_ARGS+=	--enable-devel \
			--disable-nftables

iptables-install:
	${INSTALL_DIR} ${IDIR_IPTABLES}/{usr/lib,etc/xtables,usr/sbin}
	${INSTALL_DATA} ./files/firewall.conf ${IDIR_IPTABLES}/etc
	${INSTALL_DATA} ./files/connlabel.conf ${IDIR_IPTABLES}/etc/xtables
	${CP} ${WRKINST}/usr/sbin/iptables ${IDIR_IPTABLES}/usr/sbin
	${CP} ${WRKINST}/usr/sbin/ip6tables ${IDIR_IPTABLES}/usr/sbin
	${CP} ${WRKINST}/usr/sbin/iptables-{save,restore} \
		 ${IDIR_IPTABLES}/usr/sbin
	${CP} ${WRKINST}/usr/lib/libip4tc.so* ${IDIR_IPTABLES}/usr/lib
	${CP} ${WRKINST}/usr/lib/libip6tc.so* ${IDIR_IPTABLES}/usr/lib
	${CP} ${WRKINST}/usr/lib/libxtables.so* ${IDIR_IPTABLES}/usr/lib
	${CP} ${WRKINST}/usr/lib/xtables ${IDIR_IPTABLES}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
