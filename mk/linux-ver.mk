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
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_6_4),y)
KERNEL_FILE_VER:=	6.4.12
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		cca91be956fe081f8f6da72034cded96fe35a50be4bfb7e103e354aa2159a674
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_6_1),y)
KERNEL_FILE_VER:=	6.1.49
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		c9ea14231ca4ca6e3882a9339a8c3c414e4c91519d3e50af6822f47e99057a0f
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_5_15),y)
KERNEL_FILE_VER:=	5.15.120
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		6499089eae6b271063cb3e873ab7f4ba0543cfb21dcc9c54d9bcf5357db683f6
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_5_10),y)
KERNEL_FILE_VER:=	5.10.176
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		ce072c60ba04173e05b2a1de3fefdeba5ac8b28b1958d92d21bdbf9b736ef793
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_5_4),y)
KERNEL_FILE_VER:=	5.4.239
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		a90264af0f091962cd11fa9776620c154af3000ec112abbc9e90a93d3115805b
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_4_19),y)
KERNEL_FILE_VER:=	4.19.279
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		736cc3bc3d7368651ba08fbbbedcd37b2370705a395ea87d4477ba499d9f9880
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_4_14),y)
KERNEL_FILE_VER:=	4.14.311
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		803f4ce93f081159418f725cc5e98a35df4912eb4e44fec8ebb89cf2e5cb7cd5
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
