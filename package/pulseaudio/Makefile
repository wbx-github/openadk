# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		pulseaudio
PKG_VERSION:=		15.0
PKG_RELEASE:=		1
PKG_HASH:=		a40b887a3ba98cc26976eb11bdb6613988f145b19024d1b6555c6a03c9cba1a0
PKG_DESCR:=		sound system
PKG_SECTION:=		mm/audio
PKG_DEPENDS:=		libltdl json-c libsndfile libspeex libncurses
PKG_DEPENDS+=		libflac libvorbis libogg libuuid libsndfile
PKG_DEPENDS+=		alsa-lib libICE libSM libxtst glib
PKG_BUILDDEP:=		libtool json-c libsndfile speex check meson-host
PKG_BUILDDEP+=		flac libvorbis libogg util-linux ncurses alsa-lib
PKG_BUILDDEP+=		libICE libSM libXtst glib
PKG_NEEDS:=		threads
PKG_URL:=		http://www.freedesktop.org/wiki/Software/PulseAudio/
PKG_SITES:=		http://freedesktop.org/software/pulseaudio/releases/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,PULSEAUDIO,pulseaudio,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

TARGET_CPPFLAGS+=	-D_GNU_SOURCE -D_POSIX_SOURCE

MESON_FLAGS+=		-Ddatabase=simple \
			-Ddoxygen=false \
			-Dgcov=false \
			-Dtests=false

pulseaudio-install:
	$(INSTALL_DIR) $(IDIR_PULSEAUDIO)/etc/pulse
	$(CP) ./files/*.{conf,pa} \
		$(IDIR_PULSEAUDIO)/etc/pulse
	$(INSTALL_DIR) $(IDIR_PULSEAUDIO)/usr/bin
	$(CP) $(WRKINST)/usr/bin/* \
		$(IDIR_PULSEAUDIO)/usr/bin
	$(INSTALL_DIR) $(IDIR_PULSEAUDIO)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libpulse*.so* \
		$(IDIR_PULSEAUDIO)/usr/lib
	$(INSTALL_DIR) $(IDIR_PULSEAUDIO)/usr/lib/pulseaudio
	$(CP) $(WRKINST)/usr/lib/pulseaudio/libpulse*.so* \
		$(IDIR_PULSEAUDIO)/usr/lib/pulseaudio
	$(INSTALL_DIR) $(IDIR_PULSEAUDIO)/usr/lib/pulse-$(PKG_VERSION)/modules
	$(CP) $(WRKINST)/usr/lib/pulse-$(PKG_VERSION)/modules/*.so \
		$(IDIR_PULSEAUDIO)/usr/lib/pulse-$(PKG_VERSION)/modules
	# pa uses $HOME from root user otherwise
	mv $(IDIR_PULSEAUDIO)/usr/bin/pacmd $(IDIR_PULSEAUDIO)/usr/bin/pacmd.bin
	echo "#!/bin/sh" > $(IDIR_PULSEAUDIO)/usr/bin/pacmd
	echo 'PULSE_RUNTIME_PATH=/var/run/pulse pacmd.bin "$$@"' >> $(IDIR_PULSEAUDIO)/usr/bin/pacmd
	chmod 755 $(IDIR_PULSEAUDIO)/usr/bin/pacmd

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
