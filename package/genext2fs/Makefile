# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		genext2fs
PKG_VERSION:=		1.6.2
PKG_RELEASE:=		1
PKG_HASH:=		b8aba9af48e664fa60134af696a57b3bb4ebd2b2878533d7611734e90b883ecc
PKG_DESCR:=		generate ext2 filesystem utility
PKG_SECTION:=		sys/fs
HOST_BUILDDEP:=		autoconf-host automake-host
PKG_SITES:=		https://github.com/bestouff/genext2fs/archive/refs/tags/

DISTFILES:=		v${PKG_VERSION}.tar.gz

PKG_CFLINE_GENEXT2FS:=	depends on ADK_HOST_ONLY

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,GENEXT2FS,genext2fs,$(PKG_VERSION)-${PKG_RELEASE}))

AUTOTOOL_STYLE:=	autoreconf

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
