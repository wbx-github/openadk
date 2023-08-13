# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/kernel-build.mk
include $(ADK_TOPDIR)/mk/image.mk

KERNEL:=$(LINUX_DIR)/vmlinux

QEMU_ARGS:=${ADK_QEMU_ARGS}
ifeq ($(ADK_TARGET_SYSTEM_QEMU_M68K_VIRT),y)
QEMU_ARGS+=-M virt -netdev user,id=eth0 -device virtio-net-device,netdev=eth0
ifeq ($(ADK_TARGET_FS),archive)
QEMU_ARGS+=-append "rootwait root=/dev/vda1 ro" -drive file=qemu-m68k.img,format=raw,id=hd0 -device virtio-blk-device,drive=hd0
endif
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_M68K_Q800),y)
QEMU_ARGS+=-M q800
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_M68K_MCF5208),y)
QEMU_ARGS+=-M mcf5208evb -cpu m5208
endif

# target helper text
ifeq ($(ADK_TARGET_FS),archive)
targethelp:
	@echo "The RootFS tarball is: $(FW_DIR)/$(ROOTFSTARBALL)"
ifeq ($(ADK_TARGET_QEMU),y)
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo "Use following command to create a QEMU Image:"
	@echo "./scripts/create.sh qemu-${ADK_TARGET_CPU_ARCH}.img $(FW_DIR)/$(ROOTFSUSERTARBALL)"
	@echo "Start qemu with following options:"
ifeq ($(ADK_TARGET_SYSTEM_QEMU_M68K_VIRT),y)
	@echo 'qemu-system-${ADK_TARGET_CPU_ARCH} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL)'
else
	@echo 'qemu-system-${ADK_TARGET_CPU_ARCH} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL) qemu-${ADK_TARGET_CPU_ARCH}.img'
endif
endif
endif
ifeq ($(ADK_TARGET_FS),initramfs)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo 'The initramfs image is: ${FW_DIR}/${INITRAMFS}'
ifeq ($(ADK_TARGET_QEMU),y)
	@echo "Start qemu with following command line:"
	@echo 'qemu-system-${ADK_TARGET_CPU_ARCH} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL) -initrd ${FW_DIR}/${INITRAMFS}'
endif
ifeq ($(ADK_TARGET_SYSTEM_ARANYM_M68K),y)
	@sed -e "s#@@KERNEL@@#$(FW_DIR)/$(TARGET_KERNEL)#" \
	    -e "s#@@INITRAMFS@@#${FW_DIR}/${INITRAMFS}#" \
		$(ADK_TOPDIR)/target/m68k/aranym.cfg.in \
		> $(ADK_TOPDIR)/target/m68k/aranym.cfg
	@echo 'Start aranym with: aranym-mmu -l -c target/m68k/aranym.cfg'
	@echo 'Ungrab mouse with middle mouse click'
endif
endif
ifeq ($(ADK_TARGET_FS),initramfsarchive)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo "The RootFS tarball is: $(FW_DIR)/$(ROOTFSUSERTARBALL)"
endif
ifeq ($(ADK_TARGET_FS),initramfspiggyback)
targethelp:
	@echo 'The kernel+initramfs file is: $(FW_DIR)/${TARGET_KERNEL}'
ifeq ($(ADK_TARGET_QEMU),y)
	@echo "Start qemu with following command line:"
	@echo 'qemu-system-${ADK_TARGET_CPU_ARCH} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL)'
endif
endif

kernel-strip:

kernel-install: kernel-strip
	@cp $(KERNEL) $(FW_DIR)/$(TARGET_KERNEL)

# filesystem specific targets
ifeq ($(ADK_TARGET_FS),archive)
imageinstall: kernel-install $(FW_DIR)/$(ROOTFSUSERTARBALL) targethelp
endif
ifeq ($(ADK_TARGET_FS),initramfs)
imageinstall: kernel-install $(FW_DIR)/$(INITRAMFS) targethelp
endif
ifeq ($(ADK_TARGET_FS),initramfsarchive)
imageinstall: kernel-install $(FW_DIR)/$(ROOTFSUSERTARBALL) targethelp
endif
ifeq ($(ADK_TARGET_FS),initramfspiggyback)
imageinstall: createinitramfs targethelp
endif
