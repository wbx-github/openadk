# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include ../rules.mk
include $(ADK_TOPDIR)/mk/$(ADK_TARGET_OS)-ver.mk
include $(ADK_TOPDIR)/mk/$(ADK_TARGET_OS).mk
include $(ADK_TOPDIR)/mk/buildhlp.mk

# override linux dir here, as build_bla_bla/linux does not exist yet
LINUX_DIR=${WRKBUILD}

include $(ADK_TOPDIR)/mk/kernel-vars.mk

$(TOOLCHAIN_BUILD_DIR)/w-$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)/linux-$(KERNEL_FILE_VER)/.patched:
ifeq ($(ADK_TARGET_SYSTEM_PCENGINES_APU),y)
ifeq ($(ADK_KERNEL_ROOT_NFS),y)
	cd $(DL_DIR) && wget http://distfiles.openadk.org/realtek-firmware-1.1.tar.xz
	tar xf $(DL_DIR)/realtek-firmware-1.1.tar.xz \
		--strip-components=2 -C $(WRKSRC)/firmware realtek-firmware-1.1
endif
endif
ifeq ($(ADK_TARGET_ARCH_XTENSA),y)
	tar xf $(ADK_TOPDIR)/target/xtensa/overlay/xtensa_$(ADK_TARGET_CPU_TYPE).tar \
		--strip-components=1 -C $(WRKSRC) linux
endif
ifneq ($(ADK_DISABLE_KERNEL_PATCHES),y)
	$(TRACE) kernel-patch
	$(PATCH) $(TOOLCHAIN_BUILD_DIR)/w-$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)/linux-$(KERNEL_FILE_VER) \
		$(ADK_TOPDIR)/target/linux/patches/$(KERNEL_FILE_VER) *.patch $(MAKE_TRACE)
ifeq ($(ADK_KERNEL_PATCH_REALTIME),y)
	$(TRACE) linux-rt-kernel-patch
	$(PATCH) $(TOOLCHAIN_BUILD_DIR)/w-$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)/linux-$(KERNEL_FILE_VER) \
		$(ADK_TOPDIR)/target/linux/patches/$(KERNEL_FILE_VER) patch-realtime $(MAKE_TRACE)
endif
endif
ifneq ($(ADK_DISABLE_TARGET_KERNEL_PATCHES),y)
	$(TRACE) kernel-target-patch
	$(PATCH) $(TOOLCHAIN_BUILD_DIR)/w-$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)/linux-$(KERNEL_FILE_VER) \
		$(ADK_TOPDIR)/target/$(ADK_TARGET_ARCH)/$(ADK_TARGET_BOARD)/patches/$(KERNEL_FILE_VER) *.patch $(MAKE_TRACE)
	$(PATCH) $(TOOLCHAIN_BUILD_DIR)/w-$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)/linux-$(KERNEL_FILE_VER) \
		$(ADK_TOPDIR)/target/$(ADK_TARGET_ARCH)/$(ADK_TARGET_SYSTEM)/patches/$(KERNEL_FILE_VER) *.patch $(MAKE_TRACE)
endif
	touch $(TOOLCHAIN_BUILD_DIR)/w-$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)/linux-$(KERNEL_FILE_VER)/.scmversion
	touch $@

$(WRKBUILD)/.configured: $(TOOLCHAIN_BUILD_DIR)/w-$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)/linux-$(KERNEL_FILE_VER)/.patched
	${KERNEL_MAKE} INSTALL_HDR_PATH=$(STAGING_TARGET_DIR)/usr headers_install
ifeq ($(ADK_TARGET_ARCH_CRIS),y)
ifeq ($(ADK_TARGET_CPU_ARCH),crisv32)
	cd $(STAGING_TARGET_DIR)/usr/include && ln -sf arch-v32/arch arch
else
	cd $(STAGING_TARGET_DIR)/usr/include && ln -sf arch-v10/arch arch
endif
endif
	@-find $(STAGING_TARGET_DIR)/usr/include -name .install -delete
	@-find $(STAGING_TARGET_DIR)/usr/include -name ..install.cmd -delete
	touch $@

include ${ADK_TOPDIR}/mk/toolchain.mk
