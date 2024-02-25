# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		nut
PKG_VERSION:=		2.8.1
PKG_RELEASE:=		1
PKG_HASH:=		7da48ee23b1f0d8d72560bb0af84f5c5ae4dbe35452b84cb49840132e47f099c
PKG_DESCR:=		network ups tools
PKG_SECTION:=		net/misc
PKG_URL:=		http://www.networkupstools.org/
PKG_SITES:=		http://www.networkupstools.org/source/2.8/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_FLAVOURS_NUT:=	WITH_SNMP WITH_USB
PKGFD_WITH_SNMP:=	enable snmp support
PKGFS_WITH_SNMP:=	libnetsnmp
PKGFB_WITH_SNMP:=	net-snmp
PKGFD_WITH_USB:=	enable usb support
PKGFS_WITH_USB:=	libusb libusb-compat
PKGFB_WITH_USB:=	libusb libusb-compat

PKG_CHOICES_NUT:=	WITH_LIBRESSL WITHOUT_SSL
PKGCD_WITH_LIBRESSL:=	use libressl for crypto
PKGCB_WITH_LIBRESSL:=	libressl
PKGCS_WITH_LIBRESSL:=	libressl ca-certificates
PKGCD_WITHOUT_SSL:=	use no ssl

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,NUT,nut,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

define DRIVER_template

DRIVERS_$${ADK_PACKAGE_NUT_DRIVER_${1}}+=${2}

endef

DRIVERS_y:=
$(eval $(call DRIVER_template,BESTUPS,bestups))
$(eval $(call DRIVER_template,APCSMART,apcsmart))
$(eval $(call DRIVER_template,EVERUPS,everups))
$(eval $(call DRIVER_template,BELKIN,belkin))
$(eval $(call DRIVER_template,MASTERGUARD,masterguard))
$(eval $(call DRIVER_template,POWERCOM,powercom))
$(eval $(call DRIVER_template,POWERPANEL,powerpanel))
$(eval $(call DRIVER_template,CYBERPOWER,cyberpower))
$(eval $(call DRIVER_template,TRIPPLITE,tripplite))
$(eval $(call DRIVER_template,VICTRONUPS,victronups))
$(eval $(call DRIVER_template,GENERICUPS,genericups))
$(eval $(call DRIVER_template,MGE_UTALK,mge-utalk))
$(eval $(call DRIVER_template,BESTUFERRUPS,bestuferrups))
$(eval $(call DRIVER_template,ISBMEX,isbmex))
$(eval $(call DRIVER_template,ETAPRO,etapro))
$(eval $(call DRIVER_template,LIEBERT,liebert))
$(eval $(call DRIVER_template,TRIPPLITESU,tripplitesu))
$(eval $(call DRIVER_template,SAFENET,safenet))
$(eval $(call DRIVER_template,BELKINUNV,belkinunv))
$(eval $(call DRIVER_template,ONEAC,oneac))
$(eval $(call DRIVER_template,METASYS,metasys))
$(eval $(call DRIVER_template,BESTFCOM,bestfcom))
$(eval $(call DRIVER_template,UPSCODE2,upscode2))
$(eval $(call DRIVER_template,SOLIS,solis))
$(eval $(call DRIVER_template,GAMATRONIC,gamatronic))
$(eval $(call DRIVER_template,MEGATEC,megatec))
$(eval $(call DRIVER_template,RHINO,rhino))

CONFIG_DRIVERS=$(shell echo ${DRIVERS_y} | tr ' ' ',')

INSTALL_DRIVERS_tmp=${DRIVERS_y}
ifneq (${ADK_PACKAGE_NUT_WITH_USB},)
INSTALL_DRIVERS_tmp+=	usbhid-ups tripplite_usb
endif
ifneq (${ADK_PACKAGE_NUT_WITH_SNMP},)
INSTALL_DRIVERS_tmp+=	snmp-ups
endif
INSTALL_DRIVERS=$(shell echo ${INSTALL_DRIVERS_tmp} | tr ' ' ',')

CONFIGURE_ARGS+=	--with-linux-hiddev=${LINUX_DIR}/include/linux/hiddev.h \
			--without-cgi \
			--with-drivers=${INSTALL_DRIVERS} \
			--with-group=0 \
			--with-user=0

ifeq (${ADK_PACKAGE_NUT_WITH_LIBRESSL},y)
CONFIGURE_ARGS+=	--with-ssl
CONFIGURE_ENV+=		CPPFLAGS="${TARGET_CPPFLAGS} ${TARGET_LDFLAGS}"
MAKE_FLAGS+=		SSL_CFLAGS="${TARGET_CPPFLAGS}" SSL_LDFLAGS="${TARGET_LDFLAGS} -lssl -lcrypto"
endif
ifneq (${ADK_PACKAGE_NUT_WITH_USB},)
CONFIGURE_ARGS+=	--with-usb
endif
ifneq (${ADK_PACKAGE_NUT_WITH_SNMP},)
CONFIGURE_ARGS+=	--with-snmp
endif

nut-install:
	${INSTALL_DIR} ${IDIR_NUT}/usr/{s,}bin ${IDIR_NUT}/etc
	${INSTALL_DIR} ${IDIR_NUT}/usr/lib
	${INSTALL_BIN} ${WRKINST}/usr/sbin/ups{d,mon,sched,drvctl} \
		${IDIR_NUT}/usr/sbin/
	${CP} ${WRKINST}/usr/lib/lib{nut,ups}client.so* ${IDIR_NUT}/usr/lib
	${INSTALL_BIN} ${WRKINST}/usr/bin/{${INSTALL_DRIVERS}} \
		${IDIR_NUT}/usr/bin/
	${INSTALL_BIN} ${WRKINST}/usr/bin/ups{c,cmd,log,rw} \
		${IDIR_NUT}/usr/bin/
	${INSTALL_DATA} ./files/ups{d,}.conf ${IDIR_NUT}/etc/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
