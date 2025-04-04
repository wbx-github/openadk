# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		u-boot-h8300
PKG_VERSION:=		0.1
PKG_RELEASE:=		1
PKG_HASH:=		65461cc0cab37251e2487c0f5d4ae34c7ca89767bdf790b9a863800206b83539
PKG_DESCR:=		portable bootloader
PKG_SECTION:=		base/boot
HOST_BUILDDEP:=		openssl-host dtc-host
PKG_BUILDDEP:=		u-boot-h8300-host
PKG_SITES:=		https://distfiles.openadk.org/

PKG_SYSTEM_DEPENDS:=	hitachi-edosk2674

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,U_BOOT_H8300,u-boot-h8300,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,U_BOOT_8300,u-boot-h8300,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

UBOOT:=			u-boot.bin

HOST_MAKE_FLAGS+=	HOSTCFLAGS="$(HOST_CPPFLAGS) $(HOST_CFLAGS)" \
			HOSTLDFLAGS="$(HOST_LDFLAGS) -ldl"
HOST_STYLE:=		manual
CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

host-build:
	(cd $(WRKBUILD) && env $(HOST_MAKE_ENV) $(MAKE) -f $(MAKE_FILE) \
		$(HOST_MAKE_FLAGS) sandbox_defconfig )
	(cd $(WRKBUILD) && env $(HOST_MAKE_ENV) $(MAKE) -f $(MAKE_FILE) \
		$(HOST_MAKE_FLAGS) tools $(MAKE_TRACE) )

u-boot-h8300-hostinstall:
	$(INSTALL_BIN) $(WRKBUILD)/tools/mk{,env}image \
		$(STAGING_HOST_DIR)/usr/bin

do-configure:
	(cd $(WRKBUILD) && $(MAKE) $(CONFIG))

do-build:
	(cd $(WRKBUILD) && env \
		PATH='$(HOST_PATH)' \
		CROSS_COMPILE='$(TARGET_CROSS)' \
		$(MAKE))
ifneq ($(OS_FOR_BUILD),Darwin)
	(cd $(WRKBUILD) && env \
		PATH='$(HOST_PATH)' \
		CROSS_COMPILE='$(TARGET_CROSS)' \
		$(MAKE) env)
endif

u-boot-h8300-install:
	$(CP) $(WRKBUILD)/$(UBOOT) $(FW_DIR)
	$(INSTALL_DIR) $(IDIR_U_BOOT)/etc
	$(CP) ./files/fw_env.config $(IDIR_U_BOOT)/etc

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
