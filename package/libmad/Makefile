# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libmad
PKG_VERSION:=		0.15.1b
PKG_RELEASE:=		6
PKG_HASH:=		bbfac3ed6bfbc2823d3775ebb931087371e142bb0e9bb1bee51a76a6e0078690
PKG_DESCR:=		high-quality mpeg audio decoding library
PKG_SECTION:=		libs/audio
PKG_URL:=		http://sourceforge.net/projects/mad
PKG_SITES:=		https://sourceforge.net/projects/mad/files/libmad/$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBMAD,libmad,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

FPM:=default
ifeq (${ADK_TARGET_CPU_ARCH},i486)
FPM:=intel
endif
ifeq (${ADK_TARGET_CPU_ARCH},i586)
FPM:=intel
endif
ifeq (${ADK_TARGET_CPU_ARCH},i686)
FPM:=intel
endif
ifeq (${ADK_TARGET_CPU_ARCH},arm)
FPM:=arm
endif
ifeq (${ADK_TARGET_CPU_ARCH},mipsel)
FPM:=mips
endif
ifeq (${ADK_TARGET_CPU_ARCH},mips)
FPM:=mips
endif
ifeq (${ADK_TARGET_CPU_ARCH},ppc)
FPM:=ppc
endif
ifeq (${ADK_TARGET_CPU_ARCH},sparc)
FPM:=sparc
endif
ifeq (${ADK_TARGET_CPU_ARCH},x86_64)
FPM:=64bit
endif

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--enable-fpm=${FPM} \
			--disable-debugging \
			--enable-speed

post-patch:
	touch ${WRKBUILD}/{NEWS,AUTHORS,ChangeLog}

pre-install:
	${INSTALL_DIR} ${WRKINST}/usr/lib/pkgconfig
	${CP} ./files/mad.pc ${WRKINST}/usr/lib/pkgconfig

libmad-install:
	${INSTALL_DIR} ${IDIR_LIBMAD}/usr/lib
	${CP} ${WRKINST}/usr/lib/libmad.so* ${IDIR_LIBMAD}/usr/lib/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
