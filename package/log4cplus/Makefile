# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		log4cplus
PKG_VERSION:=		2.1.2
PKG_RELEASE:=		1
PKG_HASH:=		fbdabb4ef734fe1cc62169b23f0b480cc39127ac7b09b810a9c1229490d67e9e
PKG_DESCR:=		logging framework for c++
PKG_SECTION:=		libs/misc
PKG_NEEDS:=		threads
PKG_URL:=		http://log4cplus.sourceforge.net/
PKG_SITES:=		https://sourceforge.net/projects/log4cplus/files/log4cplus-stable/$(PKG_VERSION)/
PKG_OPTS:=		dev

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LOG4CPLUS,log4cplus,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

log4cplus-install:
	${CP} ${WRKINST}/* ${IDIR_LOG4CPLUS}

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
