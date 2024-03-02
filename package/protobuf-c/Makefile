# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		protobuf-c
PKG_VERSION:=		1.5.0
PKG_RELEASE:=		1
PKG_HASH:=		d4cb022d55f49796959b07a9d83040822e39129bc0eb28f4e8301da17d758f62
PKG_DESCR:=		protocol buffers implementation in c
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		protobuf-c-host
PKG_SITES:=		https://github.com/protobuf-c/protobuf-c/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,PROTOBUF_C,protobuf-c,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,PROTOBUF_C,protobuf-c,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

AUTOTOOL_STYLE:=	autogen
CONFIGURE_ENV+=		PROTOC="$(STAGING_HOST_DIR)/usr/bin/protoc"

protobuf-c-install:
	$(INSTALL_DIR) $(IDIR_PROTOBUF_C)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libprotobuf-c*.so* \
		$(IDIR_PROTOBUF_C)/usr/lib

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
