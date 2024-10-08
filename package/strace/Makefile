# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		strace
PKG_VERSION:=		6.10
PKG_RELEASE:=		1
PKG_HASH:=		765ec71aa1de2fe37363c1e40c7b7669fc1d40c44bb5d38ba8e8cd82c4edcf07
PKG_DESCR:=		system call trace program
PKG_SECTION:=		app/debug
PKG_URL:=		https://strace.io
PKG_SITES:=		https://strace.io/files/$(PKG_VERSION)/

PKG_ARCH_DEPENDS:=	!h8300 !nds32 !cris

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,STRACE,strace,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

ifeq ($(OS_FOR_BUILD),Darwin)
XAKE_FLAGS+=		CPPFLAGS_FOR_BUILD="-I$(STAGING_TARGET_DIR)/usr/include -I$(LINUX_DIR)/include/uapi -I$(LINUX_DIR)/arch/$(ADK_TARGET_ARCH)/include/generated"
else
XAKE_FLAGS+=		CPPFLAGS_FOR_BUILD="-I$(LINUX_DIR)/include/uapi -I$(LINUX_DIR)/arch/$(ADK_TARGET_ARCH)/include/generated"
endif

ifeq ($(ADK_TARGET_LIB_MUSL),y)
TARGET_CPPFLAGS+=	-DMSG_EXCEPT=020000 -D_LARGEFILE64_SOURCE=1
CONFIGURE_ENV+=		st_cv_m32_mpers=no \
			st_cv_mx32_mpers=no
endif
ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
TARGET_LDFLAGS+=	-pthread
endif

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--enable-mpers=check
INSTALL_STYLE:=		manual

do-install:
	${INSTALL_DIR} ${IDIR_STRACE}/usr/sbin
	${INSTALL_BIN} ${WRKBUILD}/src/strace ${IDIR_STRACE}/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
