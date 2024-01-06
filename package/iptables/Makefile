# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		iptables
PKG_VERSION:=		1.8.10
PKG_RELEASE:=		1
PKG_HASH:=		5cc255c189356e317d070755ce9371eb63a1b783c34498fb8c30264f3cc59c9c
PKG_DESCR:=		netfilter firewalling software
PKG_SECTION:=		net/firewall
PKG_DEPENDS:=		libnetfilter_conntrack libmnl libnfnetlink
PKG_KDEPENDS:=		ip-nf-iptables ip-nf-filter ip-nf-nat nf-conntrack-ipv4
PKG_KDEPENDS+=		ip-nf-target-reject ip-nf-target-masquerade
PKG_BUILDDEP:=		libnetfilter_conntrack pkgconf-host
PKG_URL:=		http://www.netfilter.org/
PKG_SITES:=		http://www.netfilter.org/projects/iptables/files/
PKG_OPTS:=		dev

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,IPTABLES,iptables,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

TARGET_LDFLAGS+=	-fPIC
CONFIGURE_ARGS+=	--enable-devel \
			--disable-nftables

iptables-install:
	${INSTALL_DIR} ${IDIR_IPTABLES}/{usr/lib,etc/xtables,usr/sbin}
	${INSTALL_DATA} ./files/firewall.conf ${IDIR_IPTABLES}/etc
	${INSTALL_DATA} ./files/connlabel.conf ${IDIR_IPTABLES}/etc/xtables
	${CP} ${WRKINST}/usr/sbin/xtables-legacy-multi ${IDIR_IPTABLES}/usr/sbin
	${CP} ${WRKINST}/usr/sbin/iptables ${IDIR_IPTABLES}/usr/sbin
	${CP} ${WRKINST}/usr/sbin/ip6tables ${IDIR_IPTABLES}/usr/sbin
	${CP} ${WRKINST}/usr/sbin/iptables-{save,restore} \
		 ${IDIR_IPTABLES}/usr/sbin
	${CP} ${WRKINST}/usr/lib/libip4tc.so* ${IDIR_IPTABLES}/usr/lib
	${CP} ${WRKINST}/usr/lib/libip6tc.so* ${IDIR_IPTABLES}/usr/lib
	${CP} ${WRKINST}/usr/lib/libxtables.so* ${IDIR_IPTABLES}/usr/lib
	${CP} ${WRKINST}/usr/lib/xtables ${IDIR_IPTABLES}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
