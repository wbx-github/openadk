# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libvpx
PKG_VERSION:=		1.14.0
PKG_RELEASE:=		1
PKG_HASH:=		5f21d2db27071c8a46f1725928a10227ae45c5cd1cad3727e4aafbe476e321fa
PKG_DESCR:=		vp8/vp9 codec library
PKG_SECTION:=		libs/video
PKG_BUILDDEP:=		yasm-host
PKG_URL:=		http://www.webmproject.org/about/
PKG_SITES:=		https://github.com/webmproject/libvpx/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBVPX,libvpx,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ENV+=		LD=$(TARGET_CC)

CONFIG_STYLE:=		minimal
ifeq ($(ADK_TARGET_ARCH_AARCH64),y)
CONFIGURE_ARGS+=	--target=armv8-linux-gcc
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_VEXPRESS_A9),y)
CONFIGURE_ARGS+=	--target=armv7-linux-gcc
endif
ifeq ($(ADK_TARGET_SYSTEM_SOLIDRUN_IMX6),y)
CONFIGURE_ARGS+=	--target=armv7-linux-gcc
endif
ifeq ($(ADK_TARGET_SYSTEM_RASPBERRY_PI),y)
CONFIGURE_ARGS+=	--target=armv6-linux-gcc
endif
ifeq ($(ADK_TARGET_SYSTEM_RASPBERRY_PI2),y)
CONFIGURE_ARGS+=	--target=armv7-linux-gcc
endif
ifeq ($(ADK_TARGET_SYSTEM_RASPBERRY_PI3),y)
CONFIGURE_ARGS+=	--target=armv7-linux-gcc
endif
ifeq ($(ADK_TARGET_SYSTEM_RASPBERRY_PI3P),y)
CONFIGURE_ARGS+=	--target=armv7-linux-gcc
endif
ifeq ($(ADK_TARGET_SYSTEM_RASPBERRY_PI4),y)
CONFIGURE_ARGS+=	--target=armv7-linux-gcc
endif
ifeq ($(ADK_TARGET_SYSTEM_SHARP_ZAURUS),y)
CONFIGURE_ARGS+=	--target=armv5te-linux-gcc
endif
ifeq ($(ADK_TARGET_SYSTEM_ACMESYSTEMS_FOXG20),y)
CONFIGURE_ARGS+=	--target=armv5te-linux-gcc
endif
ifeq ($(ADK_TARGET_ARCH_MIPS),y)
CONFIGURE_ARGS+=	--target=mips32-linux-gcc
endif
ifeq ($(ADK_TARGET_CPU_MIPS64_LOONGSON2F),y)
CONFIGURE_ARGS+=	--target=loongson2f-linux-gcc
endif
ifeq ($(ADK_TARGET_ARCH_MIPS64),y)
CONFIGURE_ARGS+=	--target=mips64-linux-gcc
endif
ifeq ($(ADK_TARGET_ARCH_X86),y)
CONFIGURE_ARGS+=	--target=x86-linux-gcc --as=yasm
endif
ifeq ($(ADK_TARGET_ARCH_X86_64),y)
CONFIGURE_ARGS+=	--target=x86_64-linux-gcc --as=yasm
endif
ifeq ($(ADK_TARGET_ARCH_XTENSA),y)
CONFIGURE_ARGS+=	--target=generic-gnu
endif
CONFIGURE_ARGS+=	--prefix=/usr \
			--disable-install-docs \
			--disable-install-bins \
			--enable-install-libs \
			--disable-unit-tests \
			--disable-docs \
			--disable-examples \
			--enable-shared
ALL_TARGET:=

post-extract:
	chmod a+x $(WRKBUILD)/build/make/*.sh
	chmod a+x $(WRKBUILD)/build/make/*.pl

libvpx-install:
	$(INSTALL_DIR) $(IDIR_LIBVPX)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libvpx.so* \
		$(IDIR_LIBVPX)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
