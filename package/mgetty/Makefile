# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		mgetty
PKG_VERSION:=		1.2.1
PKG_RELEASE:=		1
PKG_HASH:=		c8a72f5ca4142e30627ad16725c40692fb09e6284514392b95ac02062cac9a89
PKG_DESCR:=		mgetty + sendfax
PKG_SECTION:=		sys/misc
PKG_SITES:=		ftp://mgetty.greenie.net/pub/mgetty/source/1.2/

PKG_CFLINE_MGETTY:=	depends on ADK_BROKEN

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,MGETTY,mgetty,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

pre-configure:
	cp ${WRKBUILD}/policy.h-dist ${WRKBUILD}/policy.h
	echo "#define	AUTO_PPP" >> ${WRKBUILD}/policy.h
	echo "#undef	FAX_NOTIFY_PROGRAM" >> ${WRKBUILD}/policy.h
	echo "#define	FAX_NOTIFY_PROGRAM \"/usr/lib/mgetty+sendfax/new_fax\"" >> ${WRKBUILD}/policy.h
	echo "#undef	DATA_FLOW" >> ${WRKBUILD}/policy.h
	echo "#define	DATA_FLOW FLOW_HARD" >> ${WRKBUILD}/policy.h
	echo "#undef	DEVICE_GROUP" >> ${WRKBUILD}/policy.h
	echo "#undef	DEVICE_OWNER" >> ${WRKBUILD}/policy.h
	echo "#define	DEVICE_OWNER \"root\"" >> ${WRKBUILD}/policy.h
	echo "#undef	FAXREC_FLOW" >> ${WRKBUILD}/policy.h
	echo "#define	FAXREC_FLOW FLOW_SOFT" >> ${WRKBUILD}/policy.h
	echo "#undef	FAXSEND_FLOW" >> ${WRKBUILD}/policy.h
	echo "#define	FAXSEND_FLOW FLOW_SOFT" >> ${WRKBUILD}/policy.h

do-build:
	${INSTALL_DIR} ${WRKINST}/usr/bin ${WRKINST}/usr/sbin
	${INSTALL_DIR} ${WRKINST}/usr/lib/mgetty+sendfax ${WRKINST}/etc/mgetty+sendfax
	${MAKE} -C ${WRKBUILD} \
		${TARGET_CONFIGURE_OPTS} \
		prefix="${WRKINST}/usr" \
		CONFDIR=/etc/mgetty+sendfax \
		bin-all
	${INSTALL_BIN} ${WRKBUILD}/mgetty ${WRKINST}/usr/sbin
	${INSTALL_BIN} ${WRKBUILD}/sendfax ${WRKINST}/usr/sbin
	${INSTALL_BIN} ${WRKBUILD}/fax/faxrunqd ${WRKINST}/usr/sbin
	${CP} ${WRKBUILD}/fax/faxq-helper ${WRKINST}/usr/lib/mgetty+sendfax
	chmod u+s ${WRKINST}/usr/lib/mgetty+sendfax/faxq-helper
	${CP} ${WRKBUILD}/fax/cour25n.pbm ${WRKINST}/usr/lib/mgetty+sendfax
	${CP} ${WRKBUILD}/fax/cour25.pbm ${WRKINST}/usr/lib/mgetty+sendfax
	${CP} ${WRKBUILD}/fax/faxq ${WRKINST}/usr/bin
	${CP} ${WRKBUILD}/fax/faxrm ${WRKINST}/usr/bin
	${CP} ${WRKBUILD}/fax/faxrunq ${WRKINST}/usr/bin
	${CP} ${WRKBUILD}/fax/faxspool ${WRKINST}/usr/bin
	${CP} ${WRKBUILD}/g3/g32pbm ${WRKINST}/usr/bin
	(cd ${WRKINST}/usr/bin;\
		ln -snf g32pbm g3topbm;\
	);
	${INSTALL_BIN} ${WRKBUILD}/g3/g3cat ${WRKINST}/usr/bin
	${INSTALL_BIN} ${WRKBUILD}/g3/pbm2g3 ${WRKINST}/usr/bin
	${INSTALL_BIN} ${WRKBUILD}/g3/sff2g3 ${WRKINST}/usr/bin
# Installation into /etc
	${CP} ${WRKBUILD}/dialin.config ${WRKINST}/etc/mgetty+sendfax
	${CP} ${WRKBUILD}/fax/faxheader ${WRKINST}/etc/mgetty+sendfax
	${CP} ${WRKBUILD}/faxrunq.config ${WRKINST}/etc/mgetty+sendfax
	${CP} ${WRKBUILD}/fax/faxspool.rules ${WRKINST}/etc/mgetty+sendfax/faxspool.rules.sample
	${WRKBUILD}/sedscript < ${WRKBUILD}/login.cfg.in > ${WRKINST}/etc/mgetty+sendfax/login.config
	${WRKBUILD}/sedscript < ${WRKBUILD}/mgetty.cfg.in > ${WRKINST}/etc/mgetty+sendfax/mgetty.config
	${WRKBUILD}/sedscript < ${WRKBUILD}/sendfax.cfg.in > ${WRKINST}/etc/mgetty+sendfax/sendfax.config

ISBIN:=${IDIR_MGETTY}/usr/sbin
IBIN:=${IDIR_MGETTY}/usr/bin
ILIB:=${IDIR_MGETTY}/usr/lib/mgetty+sendfax
IETC:=${IDIR_MGETTY}/etc/mgetty+sendfax

do-install:
	${INSTALL_DIR} ${ISBIN} ${IBIN} ${ILIB} ${IETC}
	${INSTALL_BIN} \
		${WRKINST}/usr/bin/faxq \
		${WRKINST}/usr/bin/faxrm \
		${WRKINST}/usr/bin/faxrunq \
		${WRKINST}/usr/bin/faxspool \
		${WRKINST}/usr/bin/g32pbm \
		${WRKINST}/usr/bin/g3cat \
		${WRKINST}/usr/bin/pbm2g3 \
		${WRKINST}/usr/bin/sff2g3 \
		${IBIN}
	${INSTALL_BIN} \
		${WRKINST}/usr/sbin/mgetty \
		${WRKINST}/usr/sbin/sendfax \
		${WRKINST}/usr/sbin/faxrunqd \
		${ISBIN}
	install -m4755 \
		${WRKINST}/usr/lib/mgetty+sendfax/faxq-helper \
		${ILIB}
	${INSTALL_DATA} \
		${WRKINST}/usr/lib/mgetty+sendfax/cour25n.pbm \
		${WRKINST}/usr/lib/mgetty+sendfax/cour25.pbm \
		${ILIB}
	install -m600 \
		${WRKINST}/etc/mgetty+sendfax/dialin.config \
		${WRKINST}/etc/mgetty+sendfax/faxheader \
		${WRKINST}/etc/mgetty+sendfax/faxrunq.config \
		${WRKINST}/etc/mgetty+sendfax/faxspool.rules.sample \
		${WRKINST}/etc/mgetty+sendfax/login.config \
		${WRKINST}/etc/mgetty+sendfax/mgetty.config \
		${WRKINST}/etc/mgetty+sendfax/sendfax.config \
		${IETC}

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
