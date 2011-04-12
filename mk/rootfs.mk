# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

define rootfs_template
ifeq ($(ADK_TARGET_ROOTFS_$(2)),y)
ADK_TARGET_FS:=$(1)
FS_CMDLINE:=$(3)
endif
endef

ifeq ($(ADK_HARDWARE_QEMU),y)
ROOTFS:=	root=/dev/sda1
endif

ifeq ($(ADK_TARGET_SYSTEM_MIKROTIK_RB532),y)
ROOTFS:=	root=/dev/sda2
MTDDEV:=	root=/dev/mtdblock1
endif

ifeq ($(ADK_TARGET_SYSTEM_MIKROTIK_RB433),y)
MTDDEV:=	root=/dev/mtdblock2
endif

ifeq ($(ADK_TARGET_SYSTEM_ACMESYSTEMS_FOXG20),y)
ROOTFS:=	root=/dev/mmcblk0p2 rootwait
endif

$(eval $(call rootfs_template,cf,CF,$(ROOTFS)))
$(eval $(call rootfs_template,mmc,MMC,$(ROOTFS)))
$(eval $(call rootfs_template,usb,USB,rootwait))
$(eval $(call rootfs_template,archive,ARCHIVE,$(ROOTFS)))
$(eval $(call rootfs_template,initramfs,INITRAMFS))
$(eval $(call rootfs_template,initramfs-piggyback,INITRAMFS_PIGGYBACK))
$(eval $(call rootfs_template,squashfs,SQUASHFS))
$(eval $(call rootfs_template,yaffs,YAFFS,$(MTDDEV) panic=3))
$(eval $(call rootfs_template,nfsroot,NFSROOT,root=/dev/nfs ip=dhcp init=/init))
$(eval $(call rootfs_template,encrypted,ENCRYPTED))

export ADK_TARGET_FS
