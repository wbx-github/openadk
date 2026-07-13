# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

shellescape='$(subst ','\'',$(1))'
shellexport=$(1)=$(call shellescape,${$(1)})

ifneq ($(strip ${PKG_SITES}),)
ifeq ($(strip ${DISTFILES}),)
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.xz
endif
endif

# This is where all package operation is done in
WRKDIR?=		${WRKDIR_BASE}/w-${PKG_NAME}-${PKG_VERSION}-${PKG_RELEASE}
# This is where source code is extracted and patched
WRKDIST?=		${WRKDIR}/${PKG_NAME}-${PKG_VERSION}
# This is where the configure script is seeked (localed)
WRKSRC?=		${WRKDIST}
# This is where configure, make and make install (fake) run from
WRKBUILD?=		${WRKSRC}
# This is where make install (fake) writes to
WRKINST?=		${WRKDIR}/fake-${ADK_TARGET_CPU_ARCH}/root

ifeq ($(strip ${PKG_NOCHECKSUM}),)
_CHECKSUM_COOKIE=      ${WRKDIR}/.checksum_done
else
_CHECKSUM_COOKIE=
endif

post-extract:
ifeq ($(strip ${NO_DISTFILES}),1)
${WRKDIST}/.extract_done:
	rm -rf ${WRKDIST} ${WRKSRC} ${WRKBUILD}
	@mkdir -p ${WRKDIR} ${WRKDIST}
	${MAKE} do-extract
	@${MAKE} post-extract $(MAKE_TRACE)
	touch $@

fetch refetch checksum do-extract:

__use_generic_patch_target:=42
else ifneq ($(strip ${DISTFILES}),)
include ${ADK_TOPDIR}/mk/fetch.mk

${WRKDIST}/.extract_done: ${_CHECKSUM_COOKIE}
ifeq (${_CHECKSUM_COOKIE},)
	rm -rf ${WRKDIST} ${WRKSRC} ${WRKBUILD}
endif
ifeq ($(EXTRACT_OVERRIDE),1)
	${MAKE} do-extract
else
	${EXTRACT_CMD}
endif
	@${MAKE} post-extract $(MAKE_TRACE)
	touch $@

__use_generic_patch_target:=42
else
include ${ADK_TOPDIR}/mk/fetch.mk
${WRKDIST}/.extract_done: ${_CHECKSUM_COOKIE}
	$(MAKE) fetch
ifeq (${_CHECKSUM_COOKIE},)
	rm -rf ${WRKDIST} ${WRKSRC} ${WRKBUILD}
endif
ifeq ($(EXTRACT_OVERRIDE),1)
	${MAKE} do-extract
else
	${EXTRACT_CMD}
endif
	@${MAKE} post-extract $(MAKE_TRACE)
	touch $@
endif

ifeq ($(strip ${__use_generic_patch_target}),42)
post-patch:
${WRKDIST}/.prepared: ${WRKDIST}/.extract_done
	@# find any reject files and delete them
	@find $(WRKDIST)/ -name \*.rej -delete
	[ ! -d ./patches/${PKG_VERSION} ] || ${PREVENT_PATCH} ${PATCH} ${WRKDIST} ./patches/${PKG_VERSION} \
	    '{patch-!(*.orig),*.patch,*.${ADK_TARGET_ARCH},*.${ADK_TARGET_LIBC}}' $(MAKE_TRACE)
	${PREVENT_PATCH} ${PATCH} ${WRKDIST} ./patches \
	    '{patch-!(*.orig),*.patch,*.${ADK_TARGET_ARCH},*.${ADK_TARGET_LIBC}}' $(MAKE_TRACE)
	[ ! -d ./src ] || (cd src; $(PREVENT_PATCH) cp -Rp . ${WRKDIST}/) \
		$(MAKE_TRACE)
	@${MAKE} post-patch $(MAKE_TRACE)
	@# always use latest config.sub/config.guess from OpenADK scripts directory
	@cd ${WRKDIST}; \
	    for i in $$(find . -name config.sub);do \
		if [ -f $$i ]; then \
			${CP} ${SCRIPT_DIR}/config.sub $$i; \
		fi; \
	    done; \
	    for i in $$(find . -name config.guess);do \
		if [ -f $$i ]; then \
			${CP} ${SCRIPT_DIR}/config.guess $$i; \
		fi; \
	    done;
	touch $@
endif

update-patches host-update-patches:
ifneq (${ADK_UPDATE_PATCHES_GIT},)
	PATH='${HOST_PATH}' ${BASH} $(SCRIPT_DIR)/update-patches-git "${WRKDIST}"
else
	@test ! -d ${WRKDIR}.orig || rm -rf ${WRKDIR}.orig
	@test ! -d ${WRKDIR}.orig
ifeq ($(strip ${_IN_PACKAGE})$(strip ${_IN_CVTC}),1)
	@$(MAKE) -s V=0 patch WRKDIR=${WRKDIR}.orig PREVENT_PATCH=: PKG_NOCHECKSUM=1
else
	@$(MAKE) -s V=0 prepare WRKDIR=${WRKDIR}.orig PREVENT_PATCH=: PKG_NOCHECKSUM=1
endif
	@-test ! -r ${WRKDIR}/.autoreconf_done || \
		(wrkdist=$(WRKDIST) dir=$${wrkdist#$(WRKDIR)}; \
		cd ${WRKDIR}.orig$${dir}; \
		env ${AUTOTOOL_ENV} autoreconf -if > /dev/null 2>&1; \
		rm -rf ${WRKDIR}.orig$${dir}/autom4te.cache ) $(MAKE_TRACE)
	@# restore config.sub/config.guess
	@WRKDIST=$(call shellescape,${WRKDIST}) \
	    WRKDIR1=$(call shellescape,${WRKDIR}) \
	    PATH=$(call shellescape,${HOST_PATH}) \
	    $(call shellexport,DIFF_IGNOREFILES) \
	    mksh ${ADK_TOPDIR}/scripts/update-patches2
endif

.PHONY: update-patches host-update-patches
