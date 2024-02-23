# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libowfat
PKG_VERSION:=		0.33
PKG_RELEASE:=		1
PKG_HASH:=		311ec8b3f4b72bb442e323fb013a98f956fa745547f2bc9456287b20d027cd7d
PKG_DESCR:=		owfat library
PKG_SECTION:=		libs/misc
PKG_URL:=		https://www.fefe.de/libowfat
PKG_SITES:=		https://www.fefe.de/libowfat/

PKG_NOPARALLEL:=        1

include ${ADK_TOPDIR}/mk/package.mk

CONFIG_STYLE:=		manual

TARGET_CFLAGS+=		${TARGET_CPPFLAGS}
MAKE_FILE=		GNUmakefile
MAKE_FLAGS+=		DIET= CROSS=${TARGET_CROSS} \
			LDFLAGS='${TARGET_LDFLAGS}'
FAKE_FLAGS+=		prefix='/usr'

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
