# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		gcc
ifeq ($(ADK_TOOLCHAIN_GCC_10),y)
PKG_VERSION:=		10.2.0
PKG_HASH:=		b8dd4368bb9c7f0b98188317ee0254dd8cc99d1e3a18d0ff146c855fe16c1d8c
PKG_SITES:=		${MASTER_SITE_GNU:=gcc/gcc-${PKG_VERSION}/}
PKG_RELEASE:=		1
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.xz
LIBSTDCXXVER:=		26
endif
ifeq ($(ADK_TOOLCHAIN_GCC_9),y)
PKG_VERSION:=		9.3.0
PKG_HASH:=		71e197867611f6054aa1119b13a0c0abac12834765fe2d81f35ac57f84f742d1
PKG_SITES:=		${MASTER_SITE_GNU:=gcc/gcc-${PKG_VERSION}/}
PKG_RELEASE:=		1
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.xz
LIBSTDCXXVER:=		25
endif
ifeq ($(ADK_TOOLCHAIN_GCC_8),y)
PKG_VERSION:=		8.4.0
PKG_HASH:=		e30a6e52d10e1f27ed55104ad233c30bd1e99cfb5ff98ab022dc941edd1b2dd4
PKG_SITES:=		${MASTER_SITE_GNU:=gcc/gcc-${PKG_VERSION}/}
PKG_RELEASE:=		1
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.xz
LIBSTDCXXVER:=		24
endif
ifeq ($(ADK_TOOLCHAIN_GCC_7),y)
PKG_VERSION:=		7.5.0
PKG_HASH:=		b81946e7f01f90528a1f7352ab08cc602b9ccc05d4e44da4bd501c5a189ee661
PKG_SITES:=		${MASTER_SITE_GNU:=gcc/gcc-${PKG_VERSION}/}
PKG_RELEASE:=		1
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.xz
LIBSTDCXXVER:=		23
endif
ifeq ($(ADK_TOOLCHAIN_GCC_ARC),y)
PKG_VERSION:=          arc-2020.09-eng007
PKG_GIT:=              tag
PKG_SITES:=            https://github.com/foss-for-synopsys-dwc-arc-processors/gcc.git
PKG_RELEASE:=          1
DISTFILES:=            ${PKG_NAME}-${PKG_VERSION}.tar.xz
endif
ifeq ($(ADK_TOOLCHAIN_GCC_AVR32),y)
PKG_VERSION:=		4.4.7
PKG_HASH:=		76ad7c433af1c798a1e116c4dfa8f5f794f0d32bff65f88c54dcd5e5d146fc32
PKG_SITES:=		${MASTER_SITE_GNU:=gcc/gcc-${PKG_VERSION}/}
PKG_RELEASE:=		1
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
LIBSTDCXXVER:=		19
endif
ifeq ($(ADK_TOOLCHAIN_GCC_METAG),y)
PKG_VERSION:=		4.2.4
PKG_HASH:=		7cb75c5183bd18f415860084440377016dc78feeee2852227b831f2e4fcaa5d6
PKG_SITES:=		http://gcc.cybermirror.org/releases/gcc-${PKG_VERSION}/
PKG_RELEASE:=		1
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
LIBSTDCXXVER:=		19
endif
ifeq ($(ADK_TOOLCHAIN_GCC_LM32),y)
PKG_VERSION:=		4.5.4
PKG_HASH:=		33fb968907ef7b6c528f6395ba049eb34c4df859bf5aa6c2bc3856268801e078
PKG_SITES:=		https://ftp.gnu.org/gnu/gcc/gcc-$(PKG_VERSION)/
PKG_RELEASE:=		1
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
LIBSTDCXXVER:=		19
endif
ifeq ($(ADK_TOOLCHAIN_GCC_NDS32),y)
PKG_VERSION:=		nds32-6.3.0-open
PKG_HASH:=		b23ce96df25dfdd5526496a3c2cd7ee1da4ed4094971a2e0c47c73ad7e1ad30a
PKG_SITES:=		https://github.com/andestech/gcc.git
PKG_RELEASE:=		1
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.xz
endif
ifeq ($(ADK_TOOLCHAIN_GCC_GIT),y)
PKG_VERSION:=		git
PKG_SITES:=		https://github.com/gcc-mirror/gcc.git
PKG_RELEASE:=		1
LIBSTDCXXVER:=		23
endif
