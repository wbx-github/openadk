# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

# This is where all package operation is done in
ifneq (,$(findstring host,$(MAKECMDGOALS)))
WRKDIR?=		${HOST_BUILD_DIR}/w-${PKG_NAME}-${PKG_VERSION}-${PKG_RELEASE}-host
endif

HOST_AUTOTOOL_ENV+=	PATH='${HOST_PATH}' \
			PKG_CONFIG_LIBDIR='${STAGING_HOST_DIR}/usr/lib/pkgconfig:${STAGING_HOST_DIR}/usr/share/pkgconfig' \
			PKG_CONFIG_SYSROOT_DIR='${STAGING_HOST_DIR}' \
			${COMMON_ENV}

# this is environment for 'configure'
HOST_CONFIGURE_ENV?=	PATH='${HOST_PATH}' \
			${COMMON_ENV} \
			${HOST_ENV} \
			PKG_CONFIG_LIBDIR='${STAGING_HOST_DIR}/usr/lib/pkgconfig:${STAGING_HOST_DIR}/usr/share/pkgconfig:${STAGING_HOST_DIR}/usr/lib/${GNU_HOST_NAME}/pkgconfig' \
			PKG_CONFIG_SYSROOT_DIR='${STAGING_HOST_DIR}' \
			PKG_CONFIG_ALLOW_SYSTEM_CFLAGS=1

# this is environment for 'make all' and 'make install'
HOST_MAKE_ENV?=
# this is arguments for 'make all' and 'make install'
HOST_XAKE_FLAGS?=
# this is arguments for 'make all' ONLY
HOST_MAKE_FLAGS?=
# this is arguments for 'make install' ONLY
HOST_FAKE_FLAGS?=
HOST_ALL_TARGET?=	all
HOST_INSTALL_TARGET?=	install

HOST_MAKE_ENV+=		PATH='${HOST_PATH}' \
			${COMMON_ENV} \
			${HOST_ENV}
HOST_MAKE_FLAGS+=	${HOST_XAKE_FLAGS} V=1
HOST_FAKE_FLAGS+=	${HOST_XAKE_FLAGS}

HOST_WRKINST=		${WRKDIR}/fake

_HOST_EXTRACT_COOKIE=	${WRKDIST}/.extract_done
_HOST_PATCH_COOKIE=	${WRKDIST}/.prepared
_HOST_CONFIGURE_COOKIE=	${WRKDIR}/.host_configure_done
_HOST_BUILD_COOKIE=	${WRKDIR}/.host_build_done
_HOST_FAKE_COOKIE=	${HOST_WRKINST}/.host_fake_done
_HOST_COOKIE=		${STAGING_PKG_DIR}/stamps/${PKG_NAME}${PKG_VERSION}-${PKG_RELEASE}-host

hostextract: ${_HOST_EXTRACT_COOKIE}
hostpatch: ${_HOST_PATCH_COOKIE}
hostconfigure: ${_HOST_CONFIGURE_COOKIE}
hostbuild: ${_HOST_BUILD_COOKIE}
hostfake: ${_HOST_FAKE_COOKIE}

# there are some parameters to the HOST_template function
# 1.) Config.in identifier ADK_PACKAGE_$(1)
# 2.) name of the package, for single package mostly $(PKG_NAME)
# 3.) package version (upstream version) and package release (adk version),
#     always $(PKG_VERSION)-$(PKG_RELEASE)

define HOST_template
ALL_PKGOPTS+=	$(1)
PKGNAME_$(1)=	$(2)
HOSTDIR_$(1)=	$(WRKDIR)/fake
ALL_HOSTDIRS+=	$${HOSTDIR_$(1)}
ALL_HOSTINST+=	$(2)-hostinstall

$$(HOSTDIR_$(1)): ${_HOST_PATCH_COOKIE} ${_HOST_FAKE_COOKIE}

endef

.PHONY:	all hostextract hostpatch hostconfigure \
	hostbuild hostpackage hostfake hostclean
