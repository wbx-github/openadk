# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libnet
PKG_VERSION:=		1.3
PKG_RELEASE:=		1
PKG_HASH:=		ad1e2dd9b500c58ee462acd839d0a0ea9a2b9248a1287840bc601e774fb6b28f
PKG_DESCR:=		low-level packet creation library
PKG_SECTION:=		libs/net
PKG_DEPENDS:=		libpcap
PKG_BUILDDEP:=		libpcap
PKG_NEEDS:=		c++
PKG_URL:=		https://github.com/libnet/libnet
PKG_SITES:=		https://github.com/libnet/libnet/releases/download/v$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBNET,libnet,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

ENDIAN:=lil
ifeq (${ADK_TARGET_CPU_ARCH},mips)
ENDIAN:=big
endif
ifeq (${ADK_TARGET_CPU_ARCH},mips64)
ENDIAN:=big
endif
ifeq (${ADK_TARGET_CPU_ARCH},ppc)
ENDIAN:=big
endif

CONFIGURE_ENV+=		ac_cv_libnet_endianess=${ENDIAN} \
			ac_cv_lbl_unaligned_fail=no

libnet-install:
	${INSTALL_DIR} ${IDIR_LIBNET}/usr/lib
	${CP} ${WRKINST}/usr/lib/libnet.so* ${IDIR_LIBNET}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
