# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		fmt
PKG_VERSION:=		12.1.0
PKG_RELEASE:=		1
PKG_HASH:=		ea7de4299689e12b6dddd392f9896f08fb0777ac7168897a244a6d6085043fea
PKG_DESCR:=		modern formatting library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		cmake-host
PKG_URL:=		http://fmtlib.net/latest/index.html
PKG_SITES:=		https://github.com/fmtlib/fmt/archive/
PKG_LIBNAME:=		libfmt
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBFMT,libfmt,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		cmake
CMAKE_FLAGS+=		-DFMT_DOC=OFF -DFMT_INSTALL=ON -DFMT_TEST=OFF

libfmt-install:

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
