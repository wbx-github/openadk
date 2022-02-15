# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.
#
# On the various kernel version variables:
#
# KERNEL_FILE_VER: version numbering used for tarball and contained top level
#                  directory (e.g. linux-4.1.2.tar.bz2 -> linux-4.1.2) (not
#                  necessary equal to kernel's version, e.g. linux-3.19
#                  contains kernel version 3.19.0)
# KERNEL_RELEASE:  OpenADK internal versioning
# KERNEL_VERSION:  final kernel version how we want to identify a specific kernel

ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_GIT),y)
KERNEL_FILE_VER:=	$(ADK_TARGET_LINUX_KERNEL_GIT)
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(ADK_TARGET_LINUX_KERNEL_GIT_VER)-$(KERNEL_RELEASE)
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_5_10),y)
KERNEL_FILE_VER:=	5.10.100
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		d56965afc9b6a3d26d53db40ccd37fd9d15f2ca6bfd54ef6f0f8b6e92c170999
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_5_4),y)
KERNEL_FILE_VER:=	5.4.179
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		2c9bdec0922a95aff34e8d53d2e0ecf7e842033cd908d2959a43d34afb5d897d
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_4_19),y)
KERNEL_FILE_VER:=	4.19.213
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		38f28c1cd6db0b54ee37a14fd17db651fe68704d08f95e141b14d32b872f4e98
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_4_14),y)
KERNEL_FILE_VER:=	4.14.252
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		933bb2e9359165da8a7eb8ae8321e88e3e070c34b827d51937ff3ba443e15908
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_4_9),y)
KERNEL_FILE_VER:=	4.9.287
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		d44128674702529dd26214d6cd1c19542c37c5cc516f352bebbb78f0a9ed97c2
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_4_4),y)
KERNEL_FILE_VER:=	4.4.302
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		35017bb40b604e0b577fc2b87e727632b46608a2ba3a4f5858b9177f58f376b3
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_3_16),y)
KERNEL_FILE_VER:=	3.16.85
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		80b1598d389c94e83fdf15d99c7da452aeb3093fbf8ed7c91584c06c09fc1fa6
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_2_6_32),y)
KERNEL_FILE_VER:=	2.6.32.70
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		d7d0ee4588711d4f85ed67b65d447b4bbbe215e600a771fb87a62524b6341c43
endif
