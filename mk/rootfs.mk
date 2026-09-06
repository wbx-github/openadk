# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

define rootfs_template
ifeq ($(ADK_TARGET_ROOTFS_$(2)),y)
ADK_TARGET_FS:=$(1)
FS_CMDLINE:=$(3)
endif
endef

ifeq ($(ADK_TARGET_QEMU),y)
MTDDEV:=	root=/dev/mtdblock0
ifeq ($(ADK_TARGET_ROOTFS_ARCHIVE),y)
ifeq ($(ADK_TARGET_QEMU_WITH_VIRTIO),y)
BLOCKDEV:=	root=/dev/vda1
else
BLOCKDEV:=	root=/dev/sda1
endif
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_VEXPRESS_A9),y)
BLOCKDEV:=	root=/dev/mmcblk0p1
endif
endif

ifeq ($(ADK_TARGET_SYSTEM_MIKROTIK_RB532),y)
BLOCKDEV:=	root=/dev/sda2
MTDDEV:=	root=/dev/mtdblock1
UBIDEV:=	ubi.mtd=1 root=ubi0:rootfs
endif

ifeq ($(ADK_TARGET_SYSTEM_MIKROTIK_RB4XX),y)
MTDDEV:=	root=/dev/mtdblock3
UBIDEV:=	ubi.mtd=3 root=ubi0:rootfs
endif

ifeq ($(ADK_TARGET_SYSTEM_PHYTEC_WEGA),y)
BLOCKDEV:=	root=/dev/mmcblk0p2
endif

ifeq ($(ADK_TARGET_SYSTEM_ACMESYSTEMS_FOXG20),y)
BLOCKDEV:=	root=/dev/mmcblk0p2
endif

ifeq ($(ADK_TARGET_SYSTEM_SHARP_ZAURUS),y)
BLOCKDEV:=	root=/dev/sda1
endif

ifeq ($(ADK_TARGET_BOARD_BCM28XX),y)
BLOCKDEV:=	root=/dev/mmcblk0p2
endif

ifeq ($(ADK_TARGET_SYSTEM_SOLIDRUN_IMX6),y)
BLOCKDEV:=	root=/dev/mmcblk1p1
endif

ifeq ($(ADK_TARGET_SYSTEM_PHYTEC_IMX6),y)
BLOCKDEV:=	root=/dev/mmcblk1p1
endif

ifeq ($(ADK_TARGET_SYSTEM_PHYTEC_WEGA),y)
BLOCKDEV:=	root=/dev/mmcblk1p1
endif

ifeq ($(ADK_TARGET_SYSTEM_LEMOTE_YEELONG),y)
USBDEV:=	root=/dev/sdb1
endif

$(eval $(call rootfs_template,usb,USB,$(USBDEV) rootwait))
$(eval $(call rootfs_template,archive,ARCHIVE,$(BLOCKDEV) rootwait))
$(eval $(call rootfs_template,initramfs,INITRAMFS,rootfstype=tmpfs))
$(eval $(call rootfs_template,initramfspiggyback,INITRAMFSPIGGYBACK,rootfstype=tmpfs))
$(eval $(call rootfs_template,initramfsarchive,INITRAMFSARCHIVE,rootfstype=tmpfs))
$(eval $(call rootfs_template,squashfs,SQUASHFS,$(MTDDEV) rootfstype=squashfs))
$(eval $(call rootfs_template,ubifs,UBIFS,$(UBIDEV) rootfstype=ubifs))
$(eval $(call rootfs_template,jffs2,JFFS2,$(MTDDEV) rootfstype=jffs2))
$(eval $(call rootfs_template,nfsroot,NFSROOT,root=/dev/nfs ip=dhcp))
$(eval $(call rootfs_template,encrypted,ENCRYPTED))
$(eval $(call rootfs_template,iso,ISO))
$(eval $(call rootfs_template,genimage,GENIMAGE))

export ADK_TARGET_FS
