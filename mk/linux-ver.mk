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
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_6_8),y)
KERNEL_FILE_VER:=	6.8.6
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		9e723232d603ab45ebf043c34714c48f277ab195c29abcb8472f2a4c3a5a1995
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_6_6),y)
KERNEL_FILE_VER:=	6.6.30
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		b66a5b863b0f8669448b74ca83bd641a856f164b29956e539bbcb5fdeeab9cc6
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_6_1),y)
KERNEL_FILE_VER:=	6.1.90
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		83a3d72e764fceda2c1fc68a4ea6b91253a28da56a688a2b61776b0d19788e1d
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_5_15),y)
KERNEL_FILE_VER:=	5.15.158
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		f9071c83a4fd8b80af026b48cfc1869bfa25883f9148b92b5dc1e1e1e26dd5c6
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_5_10),y)
KERNEL_FILE_VER:=	5.10.213
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		84cf30223239ec3333a5f7b2a7fba2042bba70d1582a139f7543956af871ad80
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_5_4),y)
KERNEL_FILE_VER:=	5.4.272
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		3599d5959a403e64be407d7f05e56cb270d6ddd154e89a596609919ab1e2e366
endif
ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_4_19),y)
KERNEL_FILE_VER:=	4.19.310
KERNEL_RELEASE:=	1
KERNEL_VERSION:=	$(KERNEL_FILE_VER)-$(KERNEL_RELEASE)
KERNEL_HASH:=		95ec94c4ab8f46d8a54430893f9bd653c46b0f1587d216818aa8f52fd313de69
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
