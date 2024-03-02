# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		protobuf
PKG_VERSION:=		3.19.4
PKG_RELEASE:=		1
PKG_HASH:=		3bd7828aa5af4b13b99c191e8b1e884ebfa9ad371b0ce264605d347f135d2568
PKG_DESCR:=		extensible mechanism for serializing structured data
PKG_SECTION:=		libs/misc
PKG_URL:=		https://developers.google.com/protocol-buffers/
PKG_BUILDDEP:=		protobuf-host
PKG_NEEDS:=		c++
PKG_SITES:=		https://github.com/google/protobuf/archive/
PKG_OPTS:=		dev

DISTFILES:=		v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,PROTOBUF,protobuf,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,PROTOBUF,protobuf,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

AUTOTOOL_STYLE:=	autogen
CONFIGURE_ARGS+=	--with-protoc=$(STAGING_HOST_DIR)/usr/bin/protoc

protobuf-install:
	$(INSTALL_DIR) $(IDIR_PROTOBUF)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libprotobuf*.so* \
		$(IDIR_PROTOBUF)/usr/lib

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
