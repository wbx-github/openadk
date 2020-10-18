# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/$(ADK_TARGET_OS)-ver.mk
include $(ADK_TOPDIR)/mk/$(ADK_TARGET_OS).mk
include $(ADK_TOPDIR)/mk/kernel-vars.mk

ifeq ($(ADK_TARGET_OS_LINUX),y)
KERNEL_MODULES_USED:=$(shell grep ^ADK_LINUX_KERNEL $(ADK_TOPDIR)/.config|grep =m)
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_USE_CUSTOMCONFIG),y)
KERNEL_MODULES_USED:=$(shell grep -s =m $(ADK_TOPDIR)/$(ADK_TARGET_LINUX_KERNEL_CUSTOMCONFIG_PATH))
endif

KERNEL_FILE:=$(ADK_TARGET_KERNEL)
KERNEL_TARGET:=$(ADK_TARGET_KERNEL)
ifeq ($(ADK_TARGET_KERNEL_LINUXBIN),y)
KERNEL_FILE:=vmlinux
KERNEL_TARGET:=$(ADK_TARGET_KERNEL)
endif
ifeq ($(ADK_TARGET_KERNEL_ZIMAGE),y)
KERNEL_FILE:=vmlinux
KERNEL_TARGET:=$(ADK_TARGET_KERNEL)
endif
ifeq ($(ADK_TARGET_KERNEL_VMLINUX_BOOTP),y)
KERNEL_FILE:=bootpfile
KERNEL_TARGET:=bootpfile
endif
ifeq ($(ADK_TARGET_KERNEL_VMLINUX_GZ),y)
KERNEL_FILE:=vmlinux
KERNEL_TARGET:=all
endif
ifeq ($(ADK_TARGET_KERNEL_BZIMAGE),y)
KERNEL_FILE:=vmlinux
KERNEL_TARGET:=all
endif
ifeq ($(ADK_TARGET_KERNEL_IMAGE),y)
KERNEL_FILE:=vmlinux
KERNEL_TARGET:=$(ADK_TARGET_KERNEL)
endif
ifeq ($(ADK_TARGET_KERNEL_SIMPLEIMAGE),y)
KERNEL_FILE:=vmlinux.bin
KERNEL_TARGET:=simpleImage.milkymist_one
endif

ifneq ($(KERNEL_MODULES_USED),)
KERNEL_TARGET+=modules
endif

ifeq ($(ADK_RUNTIME_DEV_UDEV),y)
ADK_DEPMOD:=$(STAGING_HOST_DIR)/usr/bin/depmod
else
ADK_DEPMOD:=true
endif

$(LINUX_DIR)/.prepared: $(TOOLCHAIN_BUILD_DIR)/w-$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)/$(ADK_TARGET_OS)-$(KERNEL_FILE_VER)/.patched
	ln -sf $(TOOLCHAIN_BUILD_DIR)/w-$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)/$(ADK_TARGET_OS)-$(KERNEL_FILE_VER) $(LINUX_DIR)
	mkdir -p $(LINUX_BUILD_DIR)/kmod-control
	touch $@

ifeq ($(ADK_TARGET_LINUX_KERNEL_USE_MINICONFIG),y)
$(LINUX_DIR)/.config: $(BUILD_DIR)/.kernelconfig
endif

ifeq ($(ADK_TARGET_LINUX_KERNEL_USE_CUSTOMCONFIG),y)
$(ADK_TOPDIR)/$(ADK_TARGET_LINUX_KERNEL_CUSTOMCONFIG_PATH):
$(LINUX_DIR)/.config: $(ADK_TOPDIR)/$(ADK_TARGET_LINUX_KERNEL_CUSTOMCONFIG_PATH)
endif

$(LINUX_DIR)/.config: $(LINUX_DIR)/.prepared
	$(START_TRACE) "target/$(ADK_TARGET_ARCH)-kernel-configure.. "
	echo "-${KERNEL_RELEASE}" >${LINUX_DIR}/localversion
ifeq ($(ADK_TARGET_LINUX_KERNEL_USE_DEFCONFIG),y)
	${KERNEL_MAKE_ENV} $(MAKE) -C "${LINUX_DIR}" ${KERNEL_MAKE_OPTS} $(ADK_TARGET_LINUX_KERNEL_DEFCONFIG) $(MAKE_TRACE)
else ifeq ($(ADK_TARGET_LINUX_KERNEL_USE_CUSTOMCONFIG),y)
	@if [ ! -f $(ADK_TOPDIR)/$(ADK_TARGET_LINUX_KERNEL_CUSTOMCONFIG_PATH) ];then \
		echo "no kernel configuration found in $(ADK_TOPDIR)/$(ADK_TARGET_LINUX_KERNEL_CUSTOMCONFIG_PATH)"; \
		exit 1; \
	fi
	${KERNEL_MAKE_ENV} $(MAKE) -C "${LINUX_DIR}" ${KERNEL_MAKE_OPTS} KCONFIG_ALLCONFIG=$(ADK_TOPDIR)/$(ADK_TARGET_LINUX_KERNEL_CUSTOMCONFIG_PATH) allnoconfig $(MAKE_TRACE)
else
	$(CP) $(BUILD_DIR)/.kernelconfig $(LINUX_DIR)/mini.config
	${KERNEL_MAKE_ENV} $(MAKE) -C "${LINUX_DIR}" ${KERNEL_MAKE_OPTS} KCONFIG_ALLCONFIG=mini.config allnoconfig $(MAKE_TRACE)
endif
	$(CMD_TRACE) " done"
	$(END_TRACE)

$(LINUX_DIR)/$(KERNEL_FILE): $(LINUX_DIR)/.config
	$(START_TRACE) "target/$(ADK_TARGET_ARCH)-kernel-compile.. "
	${KERNEL_MAKE_ENV} $(MAKE) -C "${LINUX_DIR}" ${KERNEL_MAKE_OPTS} -j${ADK_MAKE_JOBS} $(KERNEL_TARGET) $(MAKE_TRACE)
	$(CMD_TRACE) " done"
	$(END_TRACE)

prepare:
compile: $(LINUX_DIR)/$(KERNEL_FILE)
install:
ifneq ($(KERNEL_MODULES_USED),)
	$(START_TRACE) "target/$(ADK_TARGET_ARCH)-kernel-modules-install.. "
	rm -rf $(LINUX_BUILD_DIR)/modules
	${KERNEL_MAKE_ENV} $(MAKE) -C "${LINUX_DIR}" ${KERNEL_MAKE_OPTS} \
		DEPMOD=$(ADK_DEPMOD) \
		INSTALL_MOD_PATH=$(LINUX_BUILD_DIR)/modules \
		modules_install $(MAKE_TRACE)
	$(CMD_TRACE) " done"
	$(END_TRACE)
ifeq ($(ADK_RUNTIME_DEV_UDEV),)
	$(START_TRACE) "target/$(ADK_TARGET_ARCH)-kernel-modules-create-packages.. "
	rm -f ${PACKAGE_DIR}/kmod-*
	PATH='${HOST_PATH}' ${BASH} ${SCRIPT_DIR}/make-module-ipkgs.sh \
		"${ADK_TARGET_CPU_ARCH}" \
		"${KERNEL_VERSION}" \
		"${LINUX_BUILD_DIR}" \
		"${PKG_BUILD}" \
		"${PACKAGE_DIR}"
	$(CMD_TRACE) " done"
	$(END_TRACE)
endif
	$(START_TRACE) "target/${ADK_TARGET_ARCH}-kernel-modules-install-packages.. "
	for pkg in $(PACKAGE_DIR)/kmod-*; do \
		[[ -e "$$pkg" ]] && $(PKG_INSTALL) $$pkg; \
	done
	$(CMD_TRACE) " done"
	$(END_TRACE)
endif

clean:
	rm -rf $(LINUX_BUILD_DIR)
	rm -f $(wildcard ${PACKAGE_DIR}/kmod-*) $(wildcard ${PACKAGE_DIR}/kernel_*)
