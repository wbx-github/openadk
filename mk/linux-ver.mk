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
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_6_6),y)
KERNEL_FILE_VER:=	6.6.18
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		4e43d8c5fba14f7c82597838011648056487b7550fd83276ad534559e8499b1d
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_6_1),y)
KERNEL_FILE_VER:=	6.1.77
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		3b54ec567716cdfb3618caf38c58a8aab1372cc41c16430633febe9ccdb3f91d
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_5_15),y)
KERNEL_FILE_VER:=	5.15.146
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		5a807a5fa2a80ada957d8079681dfb5cc196ec26f43244d1c8a4fd7af592d192
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_5_10),y)
KERNEL_FILE_VER:=	5.10.206
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		c43d613216e6c5197519a4e979de5c1b510100858ff591963931c99e59c7485b
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_5_4),y)
KERNEL_FILE_VER:=	5.4.265
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		4dae99e49f466d4689e128ec023754908147159d7462019a83c7da1f25df9b15
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_4_19),y)
KERNEL_FILE_VER:=	4.19.303
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		022dce3935eadec7c31093992cc101c905fd4ffbb8afce92f3e41fdd0fa18b36
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_4_14),y)
KERNEL_FILE_VER:=	4.14.334
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		8a1d520cfa71e9faebae9d8c24101f5bffe48fcb897dede4cecad5af67c34a45
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
