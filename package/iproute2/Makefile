# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		iproute2
PKG_VERSION:=		5.8.0
PKG_RELEASE:=		1
PKG_HASH:=		cfcd1f890290f8c8afcc91d9444ad929b9252c16f9ab3f286c50dd3c59dc646e
PKG_DESCR:=		routing control utility
PKG_SECTION:=		net/route
PKG_BUILDDEP:=		iptables libnl linux-atm
PKG_DEPENDS:=		libnl
PKG_URL:=		http://www.linuxfoundation.org/en/Net:Iproute2
PKG_SITES:=		http://www.kernel.org/pub/linux/utils/net/iproute2/

PKG_SUBPKGS:=		IP TC TC_ATM TC_IPT IFSTAT LNSTAT ROUTEL RTMON SS
PKGSD_TC:=		traffic control utility
PKGSB_TC:=		iptables
PKGSD_TC_ATM:=		traffic control atm support library
PKGSS_TC_ATM:=		tc libatm
PKGSB_TC_ATM:=		linux-atm
PKGSD_TC_IPT:=		traffic control iptables support library
PKGSS_TC_IPT:=		tc iptables
PKGSB_TC_IPT:=		iptables
PKGSD_IFSTAT:=		interface statistics utility
PKGSD_LNSTAT:=		network statistics utilities
PKGSD_ROUTEL:=		route list and flush utilities
PKGSD_RTMON:=		rtnetlink monitor
PKGSD_SS:=		socket statistics utility

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,IP,ip,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,TC,tc,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_TC},${PKGSD_TC},${PKG_SECTION}))
$(eval $(call PKG_template,TC_ATM,tc-atm,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_TC_ATM},${PKGSD_TC_ATM},${PKG_SECTION}))
$(eval $(call PKG_template,TC_IPT,tc-iptables,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_TC_IPT},${PKGSD_TC_IPT},${PKG_SECTION}))
$(eval $(call PKG_template,IFSTAT,ifstat,${PKG_VERSION}-${PKG_RELEASE},,${PKGSD_IFSTAT},${PKG_SECTION}))
$(eval $(call PKG_template,LNSTAT,lnstat,${PKG_VERSION}-${PKG_RELEASE},,${PKGSD_LNSTAT},${PKG_SECTION}))
$(eval $(call PKG_template,ROUTEL,routel,${PKG_VERSION}-${PKG_RELEASE},,${PKGSD_ROUTEL},${PKG_SECTION}))
$(eval $(call PKG_template,RTMON,rtmon,${PKG_VERSION}-${PKG_RELEASE},,${PKGSD_RTMON},${PKG_SECTION}))
$(eval $(call PKG_template,SS,ss,${PKG_VERSION}-${PKG_RELEASE},,${PKGSD_SS},${PKG_SECTION}))

CONFIG_STYLE:=		minimal
TARGET_CFLAGS+=		-D_GNU_SOURCE
XAKE_FLAGS+=		CCOPTS="${TARGET_CFLAGS}" MFLAGS="CC=\"${TARGET_CC}\""
CONFIGURE_ENV+=		CC="${TARGET_CC}" IPTC="${TARGET_CFLAGS}" IPTL="${TARGET_LDFLAGS}"

ip-install:
	${INSTALL_DIR} ${IDIR_IP}/{etc/iproute2,bin}
	${INSTALL_DATA} ${WRKINST}/etc/iproute2/* ${IDIR_IP}/etc/iproute2/
	${INSTALL_BIN} ${WRKINST}/sbin/ip ${IDIR_IP}/bin/ip

tc-install:
	${INSTALL_DIR} ${IDIR_TC}/{usr/sbin,usr/lib/tc}
	${CP} ${WRKINST}/usr/lib/tc/*.dist ${IDIR_TC}/usr/lib/tc/
	${INSTALL_BIN} ${WRKINST}/sbin/tc ${IDIR_TC}/usr/sbin/

tc-atm-install:
	${INSTALL_DIR} ${IDIR_TC_ATM}/usr/lib/tc
	${INSTALL_DATA} ${WRKINST}/usr/lib/tc/q_atm.so \
		${IDIR_TC_ATM}/usr/lib/tc/

tc-iptables-install:
	${INSTALL_DIR} ${IDIR_TC_IPT}/usr/lib/tc
	# use ${CP} here, since m_ipt.so is a symlink to m_xt.so
	${CP} ${WRKINST}/usr/lib/tc/m_*.so ${IDIR_TC}/usr/lib/tc/

ifstat-install:
	${INSTALL_DIR} ${IDIR_IFSTAT}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/sbin/ifstat ${IDIR_IFSTAT}/usr/sbin

lnstat-install:
	${INSTALL_DIR} ${IDIR_LNSTAT}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/sbin/{ln,n}stat ${IDIR_LNSTAT}/usr/sbin
	ln -sf lnstat ${IDIR_LNSTAT}/usr/sbin/rtstat
	ln -sf lnstat ${IDIR_LNSTAT}/usr/sbin/ctstat
	${INSTALL_BIN} ${WRKINST}/sbin/rtacct ${IDIR_LNSTAT}/usr/sbin

routel-install:
	${INSTALL_DIR} ${IDIR_ROUTEL}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/sbin/route{l,f} ${IDIR_ROUTEL}/usr/sbin

rtmon-install:
	${INSTALL_DIR} ${IDIR_RTMON}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/sbin/rtmon ${IDIR_RTMON}/usr/sbin

ss-install:
	${INSTALL_DIR} ${IDIR_SS}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/sbin/ss ${IDIR_SS}/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
