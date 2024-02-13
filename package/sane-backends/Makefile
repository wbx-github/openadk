# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		sane-backends
PKG_VERSION:=		1.2.1
PKG_RELEASE:=		1
PKG_HASH:=		f832395efcb90bb5ea8acd367a820c393dda7e0dd578b16f48928b8f5bdd0524
PKG_DESCR:=		scanner access now easy
PKG_SECTION:=		sys/misc
PKG_BUILDDEP:=		libusb libusb-compat
PKG_NEEDS:=		threads
PKG_URL:=		http://www.sane-project.org/
PKG_SITES:=		https://gitlab.com/sane-project/backends/uploads/110fc43336d0fb5e514f1fdc7360dd87/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		SANE_BACKEND SANE_BACKEND_NET SANE_BACKEND_ABATON SANE_BACKEND_AGFAFOCUS
PKG_SUBPKGS+=		SANE_BACKEND_APPLE SANE_BACKEND_ARTEC_EPLUS48U SANE_BACKEND_ARTEC SANE_BACKEND_AS6E
PKG_SUBPKGS+=		SANE_BACKEND_AVISION SANE_BACKEND_BH SANE_BACKEND_CANON630U SANE_BACKEND_CANON
PKG_SUBPKGS+=		SANE_BACKEND_COOLSCAN2 SANE_BACKEND_COOLSCAN SANE_BACKEND_DC25 SANE_BACKEND_DMC
PKG_SUBPKGS+=		SANE_BACKEND_EPSON SANE_BACKEND_FUJITSU SANE_BACKEND_GENESYS SANE_BACKEND_GT68XX
PKG_SUBPKGS+=		SANE_BACKEND_HP3500 SANE_BACKEND_HP4200 SANE_BACKEND_HP5400 SANE_BACKEND_HP
PKG_SUBPKGS+=		SANE_BACKEND_IBM SANE_BACKEND_LEO SANE_BACKEND_LEXMARK SANE_BACKEND_MA1509
PKG_SUBPKGS+=		SANE_BACKEND_MATSUSHITA SANE_BACKEND_MICROTEK2 SANE_BACKEND_MICROTEK
PKG_SUBPKGS+=		SANE_BACKEND_MUSTEK SANE_BACKEND_MUSTEK_USB SANE_BACKEND_MUSTEK_USB2
PKG_SUBPKGS+=		SANE_BACKEND_NEC SANE_BACKEND_NIASH SANE_BACKEND_PIE SANE_BACKEND_PIXMA
PKG_SUBPKGS+=		SANE_BACKEND_PLUSTEK_PP SANE_BACKEND_PLUSTEK SANE_BACKEND_RICOH
PKG_SUBPKGS+=		SANE_BACKEND_S9036 SANE_BACKEND_SCEPTRE SANE_BACKEND_SHARP SANE_BACKEND_SM3600
PKG_SUBPKGS+=		SANE_BACKEND_SM3840 SANE_BACKEND_SNAPSCAN SANE_BACKEND_SP15C SANE_BACKEND_ST400
PKG_SUBPKGS+=		SANE_BACKEND_STV680 SANE_BACKEND_TAMARACK SANE_BACKEND_TECO1 SANE_BACKEND_TECO2
PKG_SUBPKGS+=		SANE_BACKEND_TECO3 SANE_BACKEND_TEST SANE_BACKEND_U12 SANE_BACKEND_UMAX1220U
PKG_SUBPKGS+=		SANE_BACKEND_UMAX_PP SANE_BACKEND_UMAX

PKGSN_SANE_BACKEND_NET:=	sane-backend
PKGSN_SANE_BACKEND_ABATON:=	sane-backend
PKGSN_SANE_BACKEND_AGFAFOCUS:=	sane-backend
PKGSN_SANE_BACKEND_APPLE:=	sane-backend
PKGSN_SANE_BACKEND_ARTEC_EPLUS48U:=	sane-backend
PKGSN_SANE_BACKEND_ARTEC:=	sane-backend
PKGSN_SANE_BACKEND_AS6E:=	sane-backend
PKGSN_SANE_BACKEND_AVISION:=	sane-backend
PKGSN_SANE_BACKEND_BH:=		sane-backend
PKGSN_SANE_BACKEND_CANON630U:=	sane-backend
PKGSN_SANE_BACKEND_CANON:=	sane-backend
PKGSN_SANE_BACKEND_COOLSCAN:=	sane-backend
PKGSN_SANE_BACKEND_COOLSCAN2:=	sane-backend
PKGSN_SANE_BACKEND_DC25:=	sane-backend
PKGSN_SANE_BACKEND_DMC:=	sane-backend
PKGSN_SANE_BACKEND_EPSON:=	sane-backend
PKGSN_SANE_BACKEND_FUJITSU:=	sane-backend
PKGSN_SANE_BACKEND_GENESYS:=	sane-backend
PKGSN_SANE_BACKEND_GT68XX:=	sane-backend
PKGSN_SANE_BACKEND_HP3500:=	sane-backend
PKGSN_SANE_BACKEND_HP4200:=	sane-backend
PKGSN_SANE_BACKEND_HP5400:=	sane-backend
PKGSN_SANE_BACKEND_HP:=		sane-backend
PKGSN_SANE_BACKEND_IBM:=	sane-backend
PKGSN_SANE_BACKEND_LEO:=	sane-backend
PKGSN_SANE_BACKEND_LEXMARK:=	sane-backend
PKGSN_SANE_BACKEND_MA1509:=	sane-backend
PKGSN_SANE_BACKEND_MATSUSHITA:=	sane-backend
PKGSN_SANE_BACKEND_MICROTEK2:=	sane-backend
PKGSN_SANE_BACKEND_MICROTEK:=	sane-backend
PKGSN_SANE_BACKEND_MUSTEK:=	sane-backend
PKGSN_SANE_BACKEND_MUSTEK_USB:=	sane-backend
PKGSN_SANE_BACKEND_MUSTEK_USB2:=sane-backend
PKGSN_SANE_BACKEND_NEC:=	sane-backend
PKGSN_SANE_BACKEND_NIASH:=	sane-backend
PKGSN_SANE_BACKEND_PIE:=	sane-backend
PKGSN_SANE_BACKEND_PIXMA:=	sane-backend
PKGSN_SANE_BACKEND_PLUSTEK_PP:=	sane-backend
PKGSN_SANE_BACKEND_PLUSTEK:=	sane-backend
PKGSN_SANE_BACKEND_RICOH:=	sane-backend
PKGSN_SANE_BACKEND_S9036:=	sane-backend
PKGSN_SANE_BACKEND_SCEPTRE:=	sane-backend
PKGSN_SANE_BACKEND_SHARP:=	sane-backend
PKGSN_SANE_BACKEND_SM3600:=	sane-backend
PKGSN_SANE_BACKEND_SM3840:=	sane-backend
PKGSN_SANE_BACKEND_SNAPSCAN:=	sane-backend
PKGSN_SANE_BACKEND_SP15C:=	sane-backend
PKGSN_SANE_BACKEND_ST400:=	sane-backend
PKGSN_SANE_BACKEND_STV680:=	sane-backend
PKGSN_SANE_BACKEND_TAMARACK:=	sane-backend
PKGSN_SANE_BACKEND_TECO1:=	sane-backend
PKGSN_SANE_BACKEND_TECO2:=	sane-backend
PKGSN_SANE_BACKEND_TECO3:=	sane-backend
PKGSN_SANE_BACKEND_TEST:=	sane-backend 
PKGSN_SANE_BACKEND_U12:=	sane-backend 
PKGSN_SANE_BACKEND_UMAX1220U:=	sane-backend
PKGSN_SANE_BACKEND_UMAX_PP:=	sane-backend
PKGSN_SANE_BACKEND_UMAX:=	sane-backend

include ${ADK_TOPDIR}/mk/package.mk

define PKG_mod_template

INSTALL_MODS_$${ADK_PACKAGE_${1}}+=    ${2}-install

${2}-install:
ifneq (${3},n)
	${INSTALL_DIR} $$(IDIR_$(1))/etc/sane.d
	${CP} $(WRKINST)/etc/sane.d/$(2).conf $$(IDIR_$(1))/etc/sane.d
endif
	${INSTALL_DIR} $$(IDIR_$(1))/usr/lib/sane
	${CP} $(WRKINST)/usr/lib/sane/libsane-$(2).so* $$(IDIR_$(1))/usr/lib/sane

endef

$(eval $(call PKG_template,SANE_BACKEND,sane-backend,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_NET,sane-backend-net,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_ABATON,sane-backend-abaton,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_AGFAFOCUS,sane-backend-agfafocus,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_APPLE,sane-backend-apple,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_ARTEC_EPLUS48U,sane-backend-artec-eplus48u,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_ARTEC,sane-backend-artec,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_AS6E,sane-backend-as6e,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_AVISION,sane-backend-avision,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_BH,sane-backend-bh,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_CANON630U,sane-backend-canon630u,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_CANON,sane-backend-canon,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_COOLSCAN2,sane-backend-coolscan2,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_COOLSCAN,sane-backend-coolscan,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_DC25,sane-backend-dc25,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_DMC,sane-backend-dmc,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_EPSON,sane-backend-epson,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_FUJITSU,sane-backend-fujitsu,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_GENESYS,sane-backend-genesys,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_GT68XX,sane-backend-gt68xx,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_HP3500,sane-backend-hp3500,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_HP4200,sane-backend-hp4200,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_HP5400,sane-backend-hp5400,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_HP,sane-backend-hp,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_IBM,sane-backend-ibm,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_LEO,sane-backend-leo,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_LEXMARK,sane-backend-lexmark,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_MA1509,sane-backend-ma1509,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_MATSUSHITA,sane-backend-matsushita,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_MICROTEK2,sane-backend-microtek2,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_MICROTEK,sane-backend-microtek,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_MUSTEK,sane-backend-mustek,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_MUSTEK_USB,sane-backend-mustek-usb,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_NEC,sane-backend-nec,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_NIASH,sane-backend-niash,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_PIE,sane-backend-pie,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_PIXMA,sane-backend-pixma,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_PLUSTEK_PP,sane-backend-plustek-pp,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_PLUSTEK,sane-backend-plustek,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_RICOH,sane-backend-ricoh,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_S9036,sane-backend-s9036,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_SCEPTRE,sane-backend-sceptre,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_SHARP,sane-backend-sharp,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_SM3600,sane-backend-sm3600,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_SM3840,sane-backend-sm3840,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_SNAPSCAN,sane-backend-snapscan,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_SP15C,sane-backend-sp15c,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_ST400,sane-backend-st400,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_STV680,sane-backend-stv680,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_TAMARACK,sane-backend-tamarack,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_TECO1,sane-backend-teco1,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_TECO2,sane-backend-teco2,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_TECO3,sane-backend-teco3,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_TEST,sane-backend-test,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_U12,sane-backend-u12,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_UMAX1220U,sane-backend-umax1220u,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_UMAX_PP,sane-backend-umax-pp,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,SANE_BACKEND_UMAX,sane-backend-umax,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

$(eval $(call PKG_mod_template,SANE_BACKEND_NET,net))
$(eval $(call PKG_mod_template,SANE_BACKEND_ABATON,abaton))
$(eval $(call PKG_mod_template,SANE_BACKEND_AGFAFOCUS,agfafocus))
$(eval $(call PKG_mod_template,SANE_BACKEND_APPLE,apple))
$(eval $(call PKG_mod_template,SANE_BACKEND_ARTEC_EPLUS48U,artec_eplus48u))
$(eval $(call PKG_mod_template,SANE_BACKEND_ARTEC,artec))
$(eval $(call PKG_mod_template,SANE_BACKEND_AS6E,as6e,n))
$(eval $(call PKG_mod_template,SANE_BACKEND_AVISION,avision))
$(eval $(call PKG_mod_template,SANE_BACKEND_BH,bh))
$(eval $(call PKG_mod_template,SANE_BACKEND_CANON630U,canon630u))
$(eval $(call PKG_mod_template,SANE_BACKEND_CANON,canon))
$(eval $(call PKG_mod_template,SANE_BACKEND_COOLSCAN2,coolscan2))
$(eval $(call PKG_mod_template,SANE_BACKEND_COOLSCAN,coolscan))
$(eval $(call PKG_mod_template,SANE_BACKEND_DC25,dc25))
$(eval $(call PKG_mod_template,SANE_BACKEND_DMC,dmc))
$(eval $(call PKG_mod_template,SANE_BACKEND_EPSON,epson))
$(eval $(call PKG_mod_template,SANE_BACKEND_FUJITSU,fujitsu))
$(eval $(call PKG_mod_template,SANE_BACKEND_GENESYS,genesys))
$(eval $(call PKG_mod_template,SANE_BACKEND_GT68XX,gt68xx))
$(eval $(call PKG_mod_template,SANE_BACKEND_HP3500,hp3500,n))
$(eval $(call PKG_mod_template,SANE_BACKEND_HP4200,hp4200))
$(eval $(call PKG_mod_template,SANE_BACKEND_HP5400,hp5400))
$(eval $(call PKG_mod_template,SANE_BACKEND_HP,hp))
$(eval $(call PKG_mod_template,SANE_BACKEND_IBM,ibm))
$(eval $(call PKG_mod_template,SANE_BACKEND_LEO,leo))
$(eval $(call PKG_mod_template,SANE_BACKEND_LEXMARK,lexmark))
$(eval $(call PKG_mod_template,SANE_BACKEND_MA1509,ma1509))
$(eval $(call PKG_mod_template,SANE_BACKEND_MATSUSHITA,matsushita))
$(eval $(call PKG_mod_template,SANE_BACKEND_MICROTEK2,microtek2))
$(eval $(call PKG_mod_template,SANE_BACKEND_MICROTEK,microtek))
$(eval $(call PKG_mod_template,SANE_BACKEND_MUSTEK,mustek))
$(eval $(call PKG_mod_template,SANE_BACKEND_MUSTEK_USB,mustek_usb))
$(eval $(call PKG_mod_template,SANE_BACKEND_NEC,nec))
$(eval $(call PKG_mod_template,SANE_BACKEND_NIASH,niash,n))
$(eval $(call PKG_mod_template,SANE_BACKEND_PIE,pie))
$(eval $(call PKG_mod_template,SANE_BACKEND_PIXMA,pixma))
$(eval $(call PKG_mod_template,SANE_BACKEND_PLUSTEK_PP,plustek_pp))
$(eval $(call PKG_mod_template,SANE_BACKEND_PLUSTEK,plustek))
$(eval $(call PKG_mod_template,SANE_BACKEND_RICOH,ricoh))
$(eval $(call PKG_mod_template,SANE_BACKEND_S9036,s9036))
$(eval $(call PKG_mod_template,SANE_BACKEND_SCEPTRE,sceptre))
$(eval $(call PKG_mod_template,SANE_BACKEND_SHARP,sharp))
$(eval $(call PKG_mod_template,SANE_BACKEND_SM3600,sm3600,n))
$(eval $(call PKG_mod_template,SANE_BACKEND_SM3840,sm3840))
$(eval $(call PKG_mod_template,SANE_BACKEND_SNAPSCAN,snapscan))
$(eval $(call PKG_mod_template,SANE_BACKEND_SP15C,sp15c))
$(eval $(call PKG_mod_template,SANE_BACKEND_ST400,st400))
$(eval $(call PKG_mod_template,SANE_BACKEND_STV680,stv680))
$(eval $(call PKG_mod_template,SANE_BACKEND_TAMARACK,tamarack))
$(eval $(call PKG_mod_template,SANE_BACKEND_TECO1,teco1))
$(eval $(call PKG_mod_template,SANE_BACKEND_TECO2,teco2))
$(eval $(call PKG_mod_template,SANE_BACKEND_TECO3,teco3))
$(eval $(call PKG_mod_template,SANE_BACKEND_TEST,test))
$(eval $(call PKG_mod_template,SANE_BACKEND_U12,u12))
$(eval $(call PKG_mod_template,SANE_BACKEND_UMAX1220U,umax1220u))
$(eval $(call PKG_mod_template,SANE_BACKEND_UMAX_PP,umax_pp))
$(eval $(call PKG_mod_template,SANE_BACKEND_UMAX,umax))

TARGET_CFLAGS+=		-D_GNU_SOURCE
CONFIGURE_ENV+=		ac_cv_func_ioperm=no \
			have_libv4l1=no \
			ac_cv_func_mmap_fixed_mapped=yes
CONFIGURE_ARGS+=	--disable-translations \
			--without-gphoto2 \
			--enable-libusb

post-install: ${INSTALL_MODS_y} ${INSTALL_MODS_m}
	${INSTALL_DIR} ${IDIR_SANE_BACKEND}/etc/sane.d
	${INSTALL_DIR} ${IDIR_SANE_BACKEND}/usr/lib
	${INSTALL_DIR} ${IDIR_SANE_BACKEND}/usr/sbin
	${CP} ${WRKINST}/etc/sane.d/dll.conf ${IDIR_SANE_BACKEND}/etc/sane.d
	${CP} ${WRKINST}/etc/sane.d/saned.conf ${IDIR_SANE_BACKEND}/etc/sane.d
	${CP} ${WRKINST}/usr/sbin/saned ${IDIR_SANE_BACKEND}/usr/sbin
	${CP} ${WRKINST}/usr/lib/libsane*.so* ${IDIR_SANE_BACKEND}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
