# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		openssh
PKG_VERSION:=		9.8p1
PKG_RELEASE:=		1
PKG_HASH:=		dd8bd002a379b5d499dfb050dd1fa9af8029e80461f4bb6c523c49973f5a39f3
PKG_DESCR:=		secure shell implementation
PKG_SECTION:=		net/security
PKG_BUILDDEP:=		zlib
PKG_BUILDDEP_GLIBC:=	libxcrypt
PKG_DEPENDS:=		zlib
PKG_NEEDS:=		threads
PKG_URL:=		http://www.openssh.com/
PKG_SITES:=		http://ftp.openbsd.org/pub/OpenBSD/OpenSSH/portable/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		OPENSSH OPENSSH_SERVER OPENSSH_CLIENT OPENSSH_CLIENT_UTILS
PKG_SUBPKGS+=		OPENSSH_SFTP_CLIENT OPENSSH_SFTP_SERVER

PKGSD_OPENSSH_SERVER:=		secure shell server
PKGSN_OPENSSH_SERVER:=		openssh
PKGSD_OPENSSH_CLIENT:=		secure shell client
PKGSN_OPENSSH_CLIENT:=		openssh
PKGSD_OPENSSH_CLIENT_UTILS:=	client utilities
PKGSN_OPENSSH_CLIENT_UTILS:=	openssh
PKGSD_OPENSSH_SFTP_CLIENT:=	sftp client
PKGSN_OPENSSH_SFTP_CLIENT:=	openssh
PKGSD_OPENSSH_SFTP_SERVER:=	sftp server
PKGSN_OPENSSH_SFTP_SERVER:=	openssh

PKG_FLAVOURS_OPENSSH:=	WITH_KRB5
PKGFD_WITH_KRB5:=	enable kerberos 5 support
PKGFS_WITH_KRB5:=	libkrb5 libcom-err
PKGFB_WITH_KRB5:=	krb5

PKG_CHOICES_OPENSSH:=	WITH_LIBRESSL WITH_OPENSSL
PKGCD_WITH_LIBRESSL:=	with libressl
PKGCS_WITH_LIBRESSL:=	libressl
PKGCB_WITH_LIBRESSL:=	libressl
PKGCD_WITH_OPENSSL:=	with openssl
PKGCS_WITH_OPENSSL:=	libopenssl
PKGCB_WITH_OPENSSL:=	openssl


include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,OPENSSH,openssh,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSSH_SERVER,openssh-server,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_OPENSSH_SERVER},${PKGSD_OPENSSH_SERVER},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSSH_CLIENT,openssh-client,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_OPENSSH_CLIENT},${PKGSD_OPENSSH_CLIENT},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSSH_CLIENT_UTILS,openssh-client-utils,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_OPENSSH_CLIENT_UTILS},${PKGSD_OPENSSH_CLIENT_UTILS},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSSH_SFTP_CLIENT,openssh-sftp-client,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_OPENSSH_SFTP_CLIENT},${PKGSD_OPENSSH_SFTP_CLIENT},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSSH_SFTP_SERVER,openssh-sftp-server,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_OPENSSH_SFTP_SERVER},${PKGSD_OPENSSH_SFTP_SERVER},${PKG_SECTION}))

ifeq ($(ADK_PACKAGE_OPENSSH_WITH_KRB5),y)
CONFIGURE_ARGS+=	--with-kerberos5="${STAGING_TARGET_DIR}/usr"
endif

ifeq ($(ADK_TARGET_USE_SSP),y)
CONFIGURE_ARGS+=	--with-stackprotect
else
CONFIGURE_ARGS+=	--without-stackprotect
endif

ifeq ($(ADK_TARGET_USE_PIE),y)
CONFIGURE_ARGS+=	--with-pie
else
CONFIGURE_ARGS+=	--without-pie
endif

CONFIGURE_ENV+=		LD='${TARGET_CC}' \
			LDFLAGS='$(TARGET_LDFLAGS) -latomic' \
			ac_cv_func_setlogin=no \
			ac_cv_have_decl_PR_SET_NO_NEW_PRIVS=no \
			ac_cv_lib_nsl_yp_match=no
CONFIGURE_ARGS+=	--disable-strip \
			--disable-etc-default-login \
			--disable-lastlog \
			--without-hardening \
			--with-sandbox=no \
			--disable-utmp \
			--disable-utmpx \
			--disable-wtmp \
			--disable-wtmpx \
			--without-bsd-auth \
			--without-rpath \
			--without-pam \
			--without-zlib-version-check \
			--sysconfdir=/etc/ssh \
			--with-privsep-user=sshd \
			--with-privsep-path=/var/run/sshd \
			--with-ssl-dir="${STAGING_TARGET_DIR}/usr"

openssh-install:
	${INSTALL_DIR} ${IDIR_OPENSSH}/etc/ssh
	chmod 0700 ${IDIR_OPENSSH}/etc/ssh

openssh-server-install:
	${INSTALL_DIR} ${IDIR_OPENSSH_SERVER}/etc/ssh
	${INSTALL_DIR} ${IDIR_OPENSSH_SERVER}/usr/bin
	${INSTALL_DIR} ${IDIR_OPENSSH_SERVER}/usr/sbin
	${INSTALL_DIR} ${IDIR_OPENSSH_SERVER}/usr/libexec
	${CP} ./files/sshd_config ${IDIR_OPENSSH_SERVER}/etc/ssh
	${INSTALL_BIN} ${WRKINST}/usr/bin/ssh-keygen \
		${IDIR_OPENSSH_SERVER}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/sshd \
	 	${IDIR_OPENSSH_SERVER}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/libexec/sshd-session \
		${IDIR_OPENSSH_SERVER}/usr/libexec
	# ssh pubkey
	test -z $(ADK_RUNTIME_SSH_PUBKEY) || ( \
		mkdir -p $(IDIR_OPENSSH_SERVER)/etc/ssh; \
		echo $(ADK_RUNTIME_SSH_PUBKEY) \
		>$(IDIR_OPENSSH_SERVER)/etc/ssh/authorized_keys; \
        )

openssh-client-install:
	${INSTALL_DIR} ${IDIR_OPENSSH_CLIENT}/etc/ssh
	${INSTALL_DIR} ${IDIR_OPENSSH_CLIENT}/usr/bin
	${INSTALL_DATA} ${WRKINST}/etc/ssh/ssh_config \
	    ${IDIR_OPENSSH_CLIENT}/etc/ssh
	${INSTALL_BIN} ${WRKINST}/usr/bin/{ssh,scp} \
	    ${IDIR_OPENSSH_CLIENT}/usr/bin

openssh-client-utils-install:
	${INSTALL_DIR} ${IDIR_OPENSSH_CLIENT_UTILS}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/ssh-{add,agent,keyscan} \
	    ${IDIR_OPENSSH_CLIENT_UTILS}/usr/bin

openssh-sftp-client-install:
	${INSTALL_DIR} ${IDIR_OPENSSH_SFTP_CLIENT}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/sftp \
		${IDIR_OPENSSH_SFTP_CLIENT}/usr/bin

openssh-sftp-server-install:
	${INSTALL_DIR} ${IDIR_OPENSSH_SFTP_SERVER}/usr/libexec
	${INSTALL_BIN} ${WRKINST}/usr/libexec/sftp-server \
		${IDIR_OPENSSH_SFTP_SERVER}/usr/libexec

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
