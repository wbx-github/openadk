# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		fmt
PKG_VERSION:=		8.1.1
PKG_RELEASE:=		1
PKG_HASH:=		3d794d3cf67633b34b2771eb9f073bde87e846e0d395d254df7b211ef1ec7346
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
