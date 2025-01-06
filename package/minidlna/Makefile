# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		minidlna
PKG_VERSION:=		1.3.3
PKG_RELEASE:=		1
PKG_HASH:=		39026c6d4a139b9180192d1c37225aa3376fdf4f1a74d7debbdbb693d996afa4
PKG_DESCR:=		DLNA/UPnP-AV compliant media server
PKG_SECTION:=		mm/video
PKG_DEPENDS:=		libffmpeg libjpeg-turbo libexif libid3tag libogg libflac libvorbis libsqlite libiconv
PKG_BUILDDEP:=		ffmpeg libjpeg-turbo libexif libid3tag libogg flac libvorbis sqlite libiconv
PKG_URL:=		http://sourceforge.net/projects/minidlna/
PKG_SITES:=		$(MASTER_SITE_SOURCEFORGE:=minidlna/)
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MINIDLNA,minidlna,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

minidlna-install:
	$(INSTALL_DIR) $(IDIR_MINIDLNA)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/minidlnad \
		$(IDIR_MINIDLNA)/usr/sbin
	$(INSTALL_DIR) $(IDIR_MINIDLNA)/etc/
	$(INSTALL_DATA) $(WRKSRC)/minidlna.conf $(IDIR_MINIDLNA)/etc/

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
