# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		asterisk
PKG_VERSION:=		20.7.0
PKG_RELEASE:=		1
PKG_HASH:=		3d47889d2c4501974a8adaaba49738e6268a836dc177c7887a93a8ecf1d38b26
PKG_DESCR:=		open source pbx
PKG_SECTION:=		net/voip
PKG_DEPENDS:=		libncurses libcurl libressl libedit libuuid libjansson
PKG_DEPENDS+=		libxml2 libsqlite libxslt
PKG_BUILDDEP:=		ncurses zlib curl popt libressl libedit util-linux libjansson
PKG_BUILDDEP+=		libxml2 sqlite libxslt
PKG_NEEDS:=		threads c++
PKG_URL:=		http://www.asterisk.org/
PKG_SITES:=		http://downloads.asterisk.org/pub/telephony/asterisk/releases/
#PKG_NOPARALLEL:=	1

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_LIBC_DEPENDS:=	uclibc-ng glibc

PKG_SUBPKGS:=		ASTERISK ASTERISK_VOICEMAIL ASTERISK_SOUNDS
PKG_SUBPKGS+=		ASTERISK_CHAN_IAX2 ASTERISK_CODEC_SPEEX ASTERISK_CODEC_GSM
PKG_SUBPKGS+=		ASTERISK_PBX_DUNDI ASTERISK_RES_AGI
PKGSD_ASTERISK_VOICEMAIL:=	voicemail support
PKGSN_ASTERISK_VOICEMAIL:=	asterisk
PKGSD_ASTERISK_CODEC_GSM:=	GSM codec support
PKGSN_ASTERISK_CODEC_GSM:=	asterisk
PKGSD_ASTERISK_PBX_DUNDI:=	PBX dundi support
PKGSN_ASTERISK_PBX_DUNDI:=	asterisk
PKGSD_ASTERISK_RES_AGI:=	res agi support
PKGSN_ASTERISK_RES_AGI:=	asterisk
PKGSD_ASTERISK_CHAN_IAX2:=	support for the Inter Asterisk Protocol
PKGSN_ASTERISK_CHAN_IAX2:=	asterisk
PKGSD_ASTERISK_CODEC_SPEEX:=	speex/PCM16 Codec translator
PKGSB_ASTERISK_CODEC_SPEEX:=	speex
PKGSN_ASTERISK_CODEC_SPEEX:=	asterisk
PKGSD_ASTERISK_SOUNDS:=		various soundfiles in GSM format
PKGSN_ASTERISK_SOUNDS:=		asterisk
PKGSS_ASTERISK_SOUNDS:=		asterisk-codec-gsm

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ASTERISK,${PKG_NAME},${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,ASTERISK_VOICEMAIL,asterisk-voicemail,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_ASTERISK_VOICEMAIL},${PKG_SECTION}))
$(eval $(call PKG_template,ASTERISK_SOUNDS,asterisk-sounds,$(PKG_VERSION)-${PKG_RELEASE},${PKGSS_ASTERISK_SOUNDS},${PKGSD_ASTERISK_SOUNDS},${PKG_SECTION}))
$(eval $(call PKG_template,ASTERISK_CHAN_IAX2,asterisk-chan-iax2,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_ASTERISK_CHAN_IAX2},${PKG_SECTION}))
$(eval $(call PKG_template,ASTERISK_CODEC_SPEEX,asterisk-codec-speex,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_ASTERISK_CODEC_SPEEX},${PKG_SECTION}))
$(eval $(call PKG_template,ASTERISK_CODEC_GSM,asterisk-codec-gsm,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_ASTERISK_CODEC_GSM},${PKG_SECTION}))
$(eval $(call PKG_template,ASTERISK_PBX_DUNDI,asterisk-pbx-dundi,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_ASTERISK_PBX_DUNDI},${PKG_SECTION}))
$(eval $(call PKG_template,ASTERISK_RES_AGI,asterisk-res-agi,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_ASTERISK_RES_AGI},${PKG_SECTION}))

CONFIGURE_ARGS=		--with-z=${STAGING_TARGET_DIR}/usr \
			--with-ncurses=${STAGING_TARGET_DIR}/usr \
			--with-libedit=${STAGING_TARGET_DIR}/usr \
			--with-jansson=${STAGING_TARGET_DIR}/usr \
			--with-ssl=${STAGING_TARGET_DIR}/usr \
			--disable-xmldoc \
			--without-tonezone \
			--without-asound \
			--without-gtk2 \
			--without-h323 \
			--without-iksemel \
			--without-imap \
			--without-netsnmp \
			--without-newt \
			--without-openais \
			--without-osptk \
			--without-oss \
			--without-popt \
			--without-pri \
			--without-pwlib \
			--without-tds \
			--without-postgres

ifneq (${ADK_PACKAGE_ASTERISK_CODEC_GSM},)
CONFIGURE_ARGS+=	--with-gsm=internal
else
CONFIGURE_ARGS+=	--without-gsm
endif
ifneq (${ADK_PACKAGE_ASTERISK_CODEC_SPEEX},)
CONFIGURE_ARGS+=	--with-speex=${STAGING_TARGET_DIR}/usr
EXTRA_CFLAGS+=		-I$(STAGING_TARGET_DIR)/usr/include/speex
endif
ifneq (${ADK_PACKAGE_ASTERISK_FORMAT_VORBIS},)
CONFIGURE_ARGS+=	--with-ogg=${STAGING_TARGET_DIR}/usr \
			--with-vorbis=${STAGING_TARGET_DIR}/usr
TARGET_LDFLAGS+=	-logg
endif
ifneq (${ADK_PACKAGE_ASTERISK_CURL},)
CONFIGURE_ARGS+=	--with-libcurl=${STAGING_TARGET_DIR}/usr
else
CONFIGURE_ARGS+=	--without-libcurl
endif

INSTALL_STYLE:=		manual

TARGET_CFLAGS+=		-fgnu89-inline
TARGET_LDFLAGS+=	-lm -ltinfo -ldl -lpthread
MAKE_ENV=		ASTCFLAGS="${TARGET_CPPFLAGS} -DHAVE_STRTOQ" \
			ASTLDFLAGS="${TARGET_LDFLAGS} -z muldefs"
MAKE_FLAGS+=		DESTDIR="$(WRKINST)" \
			OPTIMIZE="${TARGET_CFLAGS}" \
			NOISY_BUILD=1
ALL_TARGET:=		all install samples

pre-configure:
	cd "$(WRKBUILD)/menuselect"; ./configure

pre-build:
	$(MAKE) -C $(WRKBUILD)/menuselect

#post-build:
#	cd ${WRKBUILD}/sounds ; \
#	tar xzf asterisk-core-sounds-en-gsm-1.4.25.tar.gz ; \
#	rm asterisk-core-sounds-en-gsm-1.4.25.tar.gz

do-install:
	$(CP) $(WRKINST)/* $(IDIR_ASTERISK)
	rm -rf $(IDIR_ASTERISK)/usr/sbin/astgenkey
	rm -rf $(IDIR_ASTERISK)/usr/bin
	rm -rf $(IDIR_ASTERISK)/usr/share
	rm -rf $(IDIR_ASTERISK)/usr/include
	rm -rf $(IDIR_ASTERISK)/var
	(cd $(IDIR_ASTERISK)/usr/lib/asterisk; \
		rm -rf agi-bin; \
		rm -rf images; \
		rm -rf keys/*; \
		rm -rf mohmp3/*.mp3; \
		rm -rf sounds/*; \
		ln -s /tmp sounds/priv-callerintros; \
		cd modules; \
		rm -rf	*adsi* *festival* *modem* *meetme* *oss* \
			*phone* *intercom* *mp3* *nbscat* *mysql* \
			*postgres* *pgsql* *voicemail* *speex* \
			*zapateller* *jpeg*; \
		rm -f chan_bluetooth.so ; \
		rm -f chan_h323.so ; \
		rm -f chan_iax2.so ; \
		rm -f chan_mgcp.so ; \
		rm -f chan_skinny.so ; \
		rm -f {codec,format}_ilbc.so ; \
		rm -f codec_gsm.so ; \
		rm -f codec_lpc10.so ; \
		rm -f pbx_dundi.so ; \
		rm -f res_agi.so ; \
	)
	(cd $(IDIR_ASTERISK)/etc/asterisk; \
		rm -f 	*iax* *odbc* *mysql* *postgres* *pgsql* \
			*voicemail* *adsi* *oss* *alsa* \
			*festival* *modem* *meetme* *phone* *tds* \
			*vofr* *rpt* *vpb* \
			*zapata*; \
		rm -f bluetooth.conf ; \
		rm -f mgcp.conf ; \
		rm -f gtalk.conf ; \
		rm -f skinny.conf ; \
		rm -f dundi.conf ; \
		$(SED) '/^astdatadir /s#/var/#/usr/#' asterisk.conf ; \
		$(SED) '/^\[directories\]/s/(!)//' asterisk.conf ; \
	)
	${INSTALL_DATA} ./files/modules.conf $(IDIR_ASTERISK)/etc/asterisk/
	$(SED) 's|/var/lib/asterisk|/usr/lib/asterisk|g' \
		$(WRKINST)/etc/asterisk/musiconhold.conf

asterisk-sounds-install:
	${INSTALL_DIR} $(IDIR_ASTERISK_SOUNDS)/usr/lib/asterisk/sounds
	$(CP) $(WRKBUILD)/sounds/* \
		$(IDIR_ASTERISK_SOUNDS)/usr/lib/asterisk/sounds/
	(cd $(IDIR_ASTERISK_SOUNDS)/usr/lib/asterisk/sounds; \
		rm -f *.mp3 vm-*; \
		rm -f CHANGES* CREDITS* LICENSE* *.txt ; \
		rm -f *.tar.gz Makefile ; \
	)

asterisk-voicemail-install:
	${INSTALL_DIR} $(IDIR_ASTERISK_VOICEMAIL)/etc/asterisk
	${INSTALL_DIR} $(IDIR_ASTERISK_VOICEMAIL)/usr/lib/asterisk/modules
	${INSTALL_DATA} $(WRKBUILD)/configs/samples/voicemail.conf.sample \
		$(IDIR_ASTERISK_VOICEMAIL)/etc/asterisk/voicemail.conf
	${CP} $(WRKBUILD)/apps/*voicemail.so \
		$(IDIR_ASTERISK_VOICEMAIL)/usr/lib/asterisk/modules/
	${INSTALL_BIN} $(WRKBUILD)/res/res_adsi.so \
		$(IDIR_ASTERISK_VOICEMAIL)/usr/lib/asterisk/modules/

asterisk-chan-iax2-install:
	${INSTALL_DIR} $(IDIR_ASTERISK_CHAN_IAX2)/etc/asterisk
	${INSTALL_DIR} $(IDIR_ASTERISK_CHAN_IAX2)/usr/lib/asterisk/modules
	${INSTALL_DATA} $(WRKBUILD)/configs/samples/iax.conf.sample \
		$(IDIR_ASTERISK_CHAN_IAX2)/etc/asterisk/iax.conf
	${INSTALL_DATA} $(WRKBUILD)/configs/samples/iaxprov.conf.sample \
		$(IDIR_ASTERISK_CHAN_IAX2)/etc/asterisk/iaxprov.conf
	${INSTALL_BIN} $(WRKBUILD)/channels/chan_iax2.so \
		$(IDIR_ASTERISK_CHAN_IAX2)/usr/lib/asterisk/modules/

asterisk-codec-speex-install:
	${INSTALL_DIR} $(IDIR_ASTERISK_CODEC_SPEEX)/usr/lib/asterisk/modules
	${INSTALL_BIN} $(WRKBUILD)/codecs/codec_speex.so \
		$(IDIR_ASTERISK_CODEC_SPEEX)/usr/lib/asterisk/modules/

asterisk-codec-gsm-install:
	${INSTALL_DIR} $(IDIR_ASTERISK_CODEC_GSM)/usr/lib/asterisk/modules/
	${INSTALL_BIN} $(WRKBUILD)/codecs/codec_gsm.so \
		$(IDIR_ASTERISK_CODEC_GSM)/usr/lib/asterisk/modules/

asterisk-pbx-dundi-install:
	${INSTALL_DIR} $(IDIR_ASTERISK_PBX_DUNDI)/etc/asterisk
	${INSTALL_DATA} $(WRKBUILD)/configs/samples/dundi.conf.sample \
		$(IDIR_ASTERISK_PBX_DUNDI)/etc/asterisk/dundi.conf
	${INSTALL_DIR} $(IDIR_ASTERISK_PBX_DUNDI)/usr/lib/asterisk/modules
	${INSTALL_BIN} $(WRKBUILD)/pbx/pbx_dundi.so \
		$(IDIR_ASTERISK_PBX_DUNDI)/usr/lib/asterisk/modules/

asterisk-res-agi-install:
	${INSTALL_DIR} $(IDIR_ASTERISK_RES_AGI)/usr/lib/asterisk/agi-bin
	${INSTALL_DIR} $(IDIR_ASTERISK_RES_AGI)/usr/lib/asterisk/modules
	${INSTALL_BIN} $(WRKBUILD)/res/res_agi.so \
		$(IDIR_ASTERISK_RES_AGI)/usr/lib/asterisk/modules/

asterisk-meetme-install:
	${INSTALL_DIR} ${IDIR_ASTERISK_MEETME}/etc/asterisk/
	${INSTALL_DIR} ${IDIR_ASTERISK_MEETME}/usr/lib/asterisk/modules
	${INSTALL_DATA} ${WRKBUILD}/configs/samples/meetme.conf.sample \
		${IDIR_ASTERISK_MEETME}/etc/asterisk/meetme.conf
	${INSTALL_BIN} ${WRKBUILD}/apps/app_meetme.so \
		${IDIR_ASTERISK_MEETME}/usr/lib/asterisk/modules

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
