# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/rootfs.mk

ifeq ($(ADK_TARGET_LINUX_KERNEL_USE_CUSTOMCONFIG),y)
KERNEL_MODULES_USED:=$(shell grep -s =m $(ADK_TOPDIR)/$(ADK_TARGET_LINUX_KERNEL_CUSTOMCONFIG_PATH))
else
KERNEL_MODULES_USED:=$(shell grep ^ADK_$(ADK_TARGET_OS)_KERNEL $(ADK_TOPDIR)/.config|grep =m)
endif

all: install

### Kernel .config Creation
# The following target combines all kernel-related variables and
# config files into a single one to be used as the final kernel
# configuration when building. This is how it's done:
# 1) fetch all enabled ADK_OS_KERNEL_* vars into
#    .kernelconfig.kernel
# 2) get the global and device-specific static kernel config and place it into
#    .kernelconfig.board
# 3) append $(FS_CMDLINE) to the kernel commandline inside .kernelconfig.board
# 4) merge both together into .kernelconfig.tmp
# 5) check if .kernelconfig.tmp differs from the current one
#    (.kernelconfig) at all, overwriting the current one
#    only if it does (so the timestamp stays intact)
# 6) remove the temporary .kernelconfig.tmp
###
ADK_PACKAGE_CRYPTINIT_ROOT:=$(strip $(subst ",, $(ADK_PACKAGE_CRYPTINIT_ROOT)))
ADK_PACKAGE_CRYPTINIT_SWAP:=$(strip $(subst ",, $(ADK_PACKAGE_CRYPTINIT_SWAP)))
ADK_PACKAGE_CMDLINE:=root=$(ADK_PACKAGE_CRYPTINIT_ROOT) swap=$(ADK_PACKAGE_CRYPTINIT_SWAP) resume=/dev/mapper/swapcrypt

ifeq ($(ADK_TARGET_OS_LINUX),y)
ifeq ($(ADK_TARGET_LINUX_KERNEL_USE_MINICONFIG),y)
ifeq ($(ADK_TARGET_KERNEL_CUSTOMISING),y)
config-prepare: $(ADK_TOPDIR)/.config
ifeq ($(ADK_TARGET_OS_LINUX),y)
	@PATH='$(HOST_PATH)' sed -n '/^ADK_LINUX_KERNEL/s//CONFIG/p' $(ADK_TOPDIR)/.config \
	    >$(BUILD_DIR)/.kernelconfig.kernel
endif
	@if [ -f $(ADK_TARGET_ARCH)/kernel/$(ADK_TARGET_SYSTEM) ];then \
		cat $(ADK_TOPDIR)/target/$(ADK_TARGET_OS)/kernel.config \
		    $(ADK_TARGET_ARCH)/kernel/$(ADK_TARGET_SYSTEM) > $(BUILD_DIR)/.kernelconfig.board; \
	else \
		echo "no miniconfig found for target system"; \
		exit 1; \
	fi
ifneq ($(ADK_TARGET_NO_CMDLINE),y)
ifeq ($(ADK_APPLIANCE_KODI),y)
	$(SED) 's#^\(CONFIG_.*CMDLINE="\)\(.*\)"#\1\2 consoleblank=0 vt.global_cursor_default=0"#' \
		$(BUILD_DIR)/.kernelconfig.board
endif
ifeq ($(ADK_RUNTIME_VERBOSE_KERNEL_VGA_ONLY),y)
	$(SED) 's#^\(CONFIG_.*CMDLINE="\)\(.*\)"#\1\2 console=$(ADK_RUNTIME_CONSOLE_VGA_DEVICE)"#' \
		$(BUILD_DIR)/.kernelconfig.board
endif
ifeq ($(ADK_RUNTIME_VERBOSE_KERNEL_SERIAL_ONLY),y)
	$(SED) 's#^\(CONFIG_.*CMDLINE="\)\(.*\)"#\1\2 console=$(ADK_RUNTIME_CONSOLE_SERIAL_DEVICE),$(ADK_RUNTIME_CONSOLE_SERIAL_SPEED)"#' \
		$(BUILD_DIR)/.kernelconfig.board
endif
ifeq ($(ADK_RUNTIME_VERBOSE_KERNEL_VGA_SERIAL),y)
	$(SED) 's#^\(CONFIG_.*CMDLINE="\)\(.*\)"#\1\2 console=$(ADK_RUNTIME_CONSOLE_VGA_DEVICE) console=$(ADK_RUNTIME_CONSOLE_SERIAL_DEVICE),$(ADK_RUNTIME_CONSOLE_SERIAL_SPEED)"#' \
		$(BUILD_DIR)/.kernelconfig.board
endif
ifeq ($(ADK_RUNTIME_VERBOSE_KERNEL_SERIAL_VGA),y)
	$(SED) 's#^\(CONFIG_.*CMDLINE="\)\(.*\)"#\1\2 console=$(ADK_RUNTIME_CONSOLE_SERIAL_DEVICE),$(ADK_RUNTIME_CONSOLE_SERIAL_SPEED) console=$(ADK_RUNTIME_CONSOLE_VGA_DEVICE)"#' \
		$(BUILD_DIR)/.kernelconfig.board
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_M68K_Q800)$(ADK_TARGET_SYSTEM_QEMU_M68K_MCF5208),y)
	@$(SED) 's#^\(CONFIG_.*BOOTPARAM_STRING="\)\(.*\)"#\1\2 ro $(FS_CMDLINE)"#' \
		$(BUILD_DIR)/.kernelconfig.board
endif
ifeq ($(ADK_TARGET_ROOTFS_NFSROOT),)
	@$(SED) 's#^\(CONFIG_.*CMDLINE="\)\(.*\)"#\1\2 ro"#' \
		$(BUILD_DIR)/.kernelconfig.board
else
	@$(SED) 's#^\(CONFIG_.*CMDLINE="\)\(.*\)"#\1\2 rw"#' \
		$(BUILD_DIR)/.kernelconfig.board
endif
	@$(SED) 's#^\(CONFIG_.*CMDLINE="\)\(.*\)"#\1\2 $(FS_CMDLINE)"#' \
		$(BUILD_DIR)/.kernelconfig.board
ifneq ($(ADK_TARGET_CMDLINE),)
	@$(SED) 's#^\(CONFIG_.*CMDLINE="\)\(.*\)"#\1\2 $(ADK_TARGET_CMDLINE)"#' \
		$(BUILD_DIR)/.kernelconfig.board
endif
ifeq ($(ADK_TARGET_QEMU_WITH_GRAPHIC),y)
	@$(SED) 's#^\(CONFIG_.*CMDLINE="\)\(.*\)"#\1\2 console=tty0"#' \
		$(BUILD_DIR)/.kernelconfig.board
endif
ifneq ($(ADK_PACKAGE_CRYPTINIT_ROOT),)
	@$(SED) 's#^\(CONFIG_.*CMDLINE="\)\(.*\)"#\1\2 $(ADK_PACKAGE_CMDLINE)"#' \
		$(BUILD_DIR)/.kernelconfig.board
endif
ifeq ($(ADK_RUNTIME_QUIET_INIT),y)
	@$(SED) 's#^\(CONFIG_.*CMDLINE="\)\(.*\)"#\1\2 rcquiet=1"#' \
		$(BUILD_DIR)/.kernelconfig.board
endif
ifeq ($(ADK_RUNTIME_QUIET_KERNEL),y)
	@$(SED) 's#^\(CONFIG_.*CMDLINE="\)\(.*\)"#\1\2 quiet loglevel=2 vt.global_cursor_default=0"#' \
		$(BUILD_DIR)/.kernelconfig.board
endif
ifeq ($(ADK_LINUX_KERNEL_DEBUG_WITH_KGDB),y)
	@$(SED) 's#^\(CONFIG_.*CMDLINE="\)\(.*\)"#\1\2 kgdbwait kgdboc=ttyS0,115200"#' \
		$(BUILD_DIR)/.kernelconfig.board
endif
ifeq ($(ADK_LINUX_KERNEL_NETCONSOLE),y)
	@$(SED) 's#^\(CONFIG_.*CMDLINE="\)\(.*\)"#\1\2 netconsole=@$(ADK_PARAMETER_NETCONSOLE_SRC_IP)/,@$(ADK_PARAMETER_NETCONSOLE_DST_IP)/"#' \
		$(BUILD_DIR)/.kernelconfig.board
endif
endif
	@cd $(BUILD_DIR) && cat .kernelconfig.board .kernelconfig.kernel \
	    >.kernelconfig.tmp
	@cd $(BUILD_DIR) && cmp -s .kernelconfig.tmp .kernelconfig || \
	    cp .kernelconfig.tmp .kernelconfig
	@-rm -f $(BUILD_DIR)/.kernelconfig.tmp
else
config-prepare: $(ADK_TOPDIR)/.config
	@if [ -f $(ADK_TARGET_ARCH)/kernel/$(ADK_TARGET_SYSTEM) ];then \
		cat $(ADK_TOPDIR)/target/$(ADK_TARGET_OS)/kernel.config \
		    $(ADK_TARGET_ARCH)/kernel/$(ADK_TARGET_SYSTEM) > $(BUILD_DIR)/.kernelconfig.board; \
	else \
		echo "no miniconfig found for target system"; \
		exit 1; \
	fi
	@cd $(BUILD_DIR) && cmp -s .kernelconfig.board .kernelconfig || \
	    cp .kernelconfig.board .kernelconfig
endif
else
config-prepare: $(ADK_TOPDIR)/.config
	@true
endif
endif


ifeq ($(ADK_TARGET_OS_LINUX),y)
prepare: $(ADK_TARGET_ARCH)-prepare
compile: $(ADK_TARGET_ARCH)-compile
image: $(ADK_TARGET_ARCH)-imageclean $(ADK_TARGET_ARCH)-imageinstall
targethelp: $(ADK_TARGET_ARCH)-targethelp
install: $(ADK_TARGET_ARCH)-imageclean $(ADK_TARGET_ARCH)-install $(ADK_TARGET_ARCH)-imageinstall
clean: $(ADK_TARGET_ARCH)-clean $(ADK_TARGET_ARCH)-imageclean
endif

%-clean:
	$(START_TRACE) "target/$(patsubst %-clean,%,$@)-clean.. "
	$(MAKE) -C $(patsubst %-clean,%,$@) clean
	$(CMD_TRACE) " done"
	$(END_TRACE)

%-imageclean:
	$(START_TRACE) "target/$(patsubst %-imageclean,%,$@)-imageclean.. "
	$(MAKE) -C $(patsubst %-imageclean,%,$@) imageclean
	$(CMD_TRACE) " done"
	$(END_TRACE)

%-prepare:
	$(START_TRACE) "target/$(patsubst %-prepare,%,$@)-prepare.. "
	$(MAKE) -C $(patsubst %-prepare,%,$@) prepare
	$(CMD_TRACE) " done"
	$(END_TRACE)

%-imageprepare:
	$(START_TRACE) "target/$(patsubst %-imageprepare,%,$@)-imageprepare.. "
ifeq ($(ADK_RUNTIME_DEV_UDEV),y)
ifneq ($(KERNEL_MODULES_USED),)
	# This should be made a package instead
	$(CP) $(BUILD_DIR)/$(ADK_TARGET_OS)-$(ADK_TARGET_ARCH)/modules/lib $(TARGET_DIR)
	rm -f "$(TARGET_DIR)"/lib/modules/*/build \
	      "$(TARGET_DIR)"/lib/modules/*/source
endif
endif
	@for x in $$(ls $(ADK_TOPDIR)/scripts/preimage/*.sh 2>/dev/null); do \
		[[ -x "$$x" ]] && $$x; \
		break; \
	done
	$(MAKE) -C $(patsubst %-imageprepare,%,$@) imageprepare
	$(CMD_TRACE) " done"
	$(END_TRACE)

%-compile: %-prepare
	$(START_TRACE) "target/$(patsubst %-compile,%,$@)-compile.. "
	$(MAKE) -C $(patsubst %-compile,%,$@) compile
	$(CMD_TRACE) " done"
	$(END_TRACE)

%-install:
	$(START_TRACE) "target/$(patsubst %-install,%,$@)-install.. "
	$(MAKE) -C $(patsubst %-install,%,$@) install
	$(CMD_TRACE) " done"
	$(END_TRACE)

%-targethelp:
	$(MAKE) -C $(patsubst %-targethelp,%,$@) targethelp

%-imageinstall: %-imageprepare
ifdef ADK_POST_BUILD_ACTION
ifneq ($(ADK_POST_BUILD_ACTION),"")
	@printf "running post build action '$(ADK_POST_BUILD_ACTION)'\n"
	$(ADK_TOPDIR)/$(ADK_POST_BUILD_ACTION) $(ADK_TOPDIR)
endif
endif
	$(MAKE) -C $(patsubst %-imageinstall,%,$@) imageinstall
	@for x in $$(ls $(ADK_TOPDIR)/scripts/postimage/*.sh 2>/dev/null); do \
		[[ -x "$$x" ]] && $$x; \
		break; \
	done
	@echo "Login as user root via ssh or console."
