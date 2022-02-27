# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		fstrcmp
PKG_VERSION:=		0.7
PKG_RELEASE:=		1
PKG_HASH:=		e4018e850f80700acee8da296e56e15b1eef711ab15157e542e7d7e1237c3476
PKG_DESCR:=		make fuzzy comparisons of strings
PKG_SECTION:=		libs/misc
PKG_SITES:=		http://fstrcmp.sourceforge.net/
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).D001.tar.gz
WRKDIST=		$(WRKDIR)/$(PKG_NAME)-$(PKG_VERSION).D001

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FSTRCMP,fstrcmp,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

fstrcmp-install:

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
