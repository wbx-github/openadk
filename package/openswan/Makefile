# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		openswan
PKG_VERSION:=		3.0.0
PKG_RELEASE:=		1
PKG_HASH:=		69fe7a71e54aaf0ea93b874db4963057c1ff4904b3617b36f2c9be2010c23331
PKG_DESCR:=		ipsec software
PKG_SECTION:=		net/security
PKG_DEPENDS:=		libgmp
PKG_BUILDDEP:=		gmp
PKG_NEEDS:=		threads
PKG_URL:=		http://www.openswan.org/
PKG_SITES:=		https://github.com/xelerance/Openswan/archive/refs/tags/
PKG_NOPARALLEL:=	1

DISTFILES:=		v${PKG_VERSION}.tar.gz
WRKDIST=		$(WRKDIR)/Openswan-$(PKG_VERSION)

# GLOB_BRACE usage
PKG_LIBC_DEPENDS:=	uclibc-ng glibc

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,OPENSWAN,openswan,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
XAKE_FLAGS+=		KERNELSRC="${LINUX_DIR}" \
			IPSECDIR="/usr/lib/ipsec" \
			INC_USRLOCAL="/usr" \
			MODPROBE="insmod" \
			OSDEP="linux" \
			WERROR="" \
			BUILDENV="linux" \
			ARCH=$(ADK_TARGET_KARCH) \
			V=1
ALL_TARGET:=		programs

openswan-install:
	${INSTALL_DIR} ${IDIR_OPENSWAN}/usr/lib/ipsec
	${INSTALL_DIR} ${IDIR_OPENSWAN}/usr/libexec/ipsec
	${INSTALL_DIR} ${IDIR_OPENSWAN}/etc/ipsec.d
	${INSTALL_DIR} ${IDIR_OPENSWAN}/usr/sbin
	${INSTALL_DATA} ${WRKINST}/etc/ipsec.conf ${IDIR_OPENSWAN}/etc/
	${CP} ${WRKINST}/etc/ipsec.d/* ${IDIR_OPENSWAN}/etc/ipsec.d
	${CP} ${WRKINST}/usr/lib/ipsec/* ${IDIR_OPENSWAN}/usr/lib/ipsec
	${CP} ${WRKINST}/usr/libexec/ipsec/* ${IDIR_OPENSWAN}/usr/libexec/ipsec
	rm ${IDIR_OPENSWAN}/usr/libexec/ipsec/setup
	${INSTALL_BIN} ${WRKINST}/etc/rc.d/init.d/ipsec \
		${IDIR_OPENSWAN}/usr/libexec/ipsec/setup
	${INSTALL_BIN} ${WRKINST}/usr/sbin/ipsec ${IDIR_OPENSWAN}/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
