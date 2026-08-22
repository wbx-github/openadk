# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		mpc
PKG_VERSION:=		1.4.1
PKG_RELEASE:=		1
PKG_HASH:=		91204cd32f164bd3b7c992d4a6a8ce6519511aadab30f78b6982d0bf8d73e931
PKG_SITES:=		https://ftp.gnu.org/gnu/mpc/
GMP_BUILD_DIR:=		$(TOOLCHAIN_BUILD_DIR)/w-$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)/$(PKG_NAME)-$(PKG_VERSION)
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.xz
