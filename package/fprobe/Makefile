# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		fprobe
PKG_VERSION:=		1.1
PKG_RELEASE:=		1
PKG_HASH:=		3a1cedf5e7b0d36c648aa90914fa71a158c6743ecf74a38f4850afbac57d22a0
PKG_DESCR:=		netflow probe
PKG_SECTION:=		net/acct
PKG_DEPENDS:=		libpcap
PKG_BUILDDEP:=		libpcap
PKG_NEEDS:=		threads
PKG_SITES:=		https://sourceforge.net/projects/fprobe/files/fprobe/$(PKG_VERSION)/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.bz2

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,FPROBE,fprobe,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--with-piddir=/var \
			--with-pcap=${STAGING_TARGET_DIR}/usr/include \
			--with-libpcap=${STAGING_TARGET_DIR}/usr/lib \
			--with-membulk=index8 \
			--with-hash=xor8 \

fprobe-install:
	${INSTALL_DIR} ${IDIR_FPROBE}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/fprobe ${IDIR_FPROBE}/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
