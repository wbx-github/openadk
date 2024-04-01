# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

ifneq ($(strip ${DIST_SUBDIR}),)
FULLDISTDIR?=		${DL_DIR}/${DIST_SUBDIR}
else
FULLDISTDIR?=		${DL_DIR}
endif

FULLDISTFILES=		$(patsubst %,${FULLDISTDIR}/%,${DISTFILES})

FETCH_STYLE?=		auto
do-fetch:
fetch:
ifneq ($(filter auto,${FETCH_STYLE}),)
	${MAKE} ${FULLDISTFILES}
else
	${MAKE} do-fetch
endif

refetch:
	-rm -f ${FULLDISTFILES}
	${MAKE} fetch

_CHECKSUM_COOKIE?=	${WRKDIR}/.checksum_done
checksum: ${_CHECKSUM_COOKIE}
ifeq ($(strip ${PKG_NOCHECKSUM}),)
${_CHECKSUM_COOKIE}: ${FULLDISTFILES}
	-rm -rf ${WRKDIR}
ifneq ($(ADK_DISABLE_CHECKSUM),y)
	@if [ ! -e $(firstword ${FULLDISTFILES}).nohash ]; then \
	OK=n; \
	allsums="$(strip ${PKG_HASH})"; \
	($${SHA256} ${FULLDISTFILES}; echo exit) | while read sum name; do \
		if [[ $$sum = exit ]]; then \
			[[ $$OK = n ]] && echo >&2 "==> No distfile found!" || :; \
			[[ $$OK = 1 ]] || exit 1; \
			break; \
		fi; \
		cursum="$${allsums%% *}"; \
		allsums="$${allsums#* }"; \
		if [[ $$sum = "$$cursum" ]]; then \
			[[ $$OK = 0 ]] || OK=1; \
			continue; \
		fi; \
		echo >&2 "==> Checksum mismatch for $${name##*/} (SHA256)"; \
		echo >&2 ":---> should be '$$cursum'"; \
		echo >&2 ":---> really is '$$sum'"; \
		OK=0; \
	done; \
	fi
endif
	mkdir -p ${WRKDIR}
	touch ${_CHECKSUM_COOKIE}
endif

# GNU make's poor excuse for loops
define FETCH_template
$(1):
	@fullname='$(1)'; \
	filename=$$$${fullname##*/}; \
	mkdir -p "$$$${fullname%%/$$$$filename}"; \
	cd "$$$${fullname%%/$$$$filename}"; \
	for url in "${PKG_SITES}"; do case $$$$url in \
	   file://*|git://*|*.git) \
		echo "Trying to downloading from backup site first"; \
		if $${FETCHCMD} $$$$filename $${MASTER_SITE_BACKUP}/$$$$filename $(DL_TRACE); then \
			touch $$$$filename.nohash; \
			: check the size here; \
			[[ ! -e $$$$filename ]] || exit 0; \
		fi; \
		rm -rf $${PKG_NAME}-$${PKG_VERSION}; \
		if [ ! -z "$${PKG_GIT}" ]; then \
		  echo "Using git ${PKG_GIT}: $${PKG_VERSION}" $(DL_TRACE); \
		  case "$${PKG_GIT}" in \
		    tag|branch) \
			git clone --progress --depth 1 --branch $${PKG_VERSION} $${PKG_SITES} $${PKG_NAME}-$${PKG_VERSION} $(DL_TRACE); \
			if [ $$$$? -ne 0 ]; then echo "git clone error"; exit 1; fi; \
			;; \
		    hash) \
			git clone --progress $${PKG_SITES} $${PKG_NAME}-$${PKG_VERSION} $(DL_TRACE); \
			if [ $$$$? -ne 0 ]; then echo "git clone error"; exit 1; fi; \
			(cd $${PKG_NAME}-$${PKG_VERSION}; git checkout $${PKG_VERSION}) $(DL_TRACE); \
			if [ $$$$? -ne 0 ]; then echo "git checkout error"; exit 1; fi; \
			;; \
		  esac ;\
		else \
		  git clone --progress --depth 1 $${PKG_SITES} $${PKG_NAME}-$${PKG_VERSION} $(DL_TRACE); \
		  if [ $$$$? -ne 0 ]; then echo "git clone error"; exit 1; fi; \
		fi; \
		if [ ! -z "$${PKG_GIT_SUBMODULE}" ]; then \
			(cd $${PKG_NAME}-$${PKG_VERSION}; git submodule update --init --recursive) $(DL_TRACE); \
		fi; \
		rm -rf $${PKG_NAME}-$${PKG_VERSION}/.git; \
		PATH='$(HOST_PATH)' tar czf $${PKG_NAME}-$${PKG_VERSION}.tar.gz $${PKG_NAME}-$${PKG_VERSION}; \
		touch $$$${filename}.nohash; \
		rm -rf $${PKG_NAME}-$${PKG_VERSION}; \
		: check the size here; \
		[[ ! -e $$$$filename ]] || exit 0; \
		;; \
	    http://*|https://*|ftp://*) \
		for site in $${PKG_SITES} $${MASTER_SITE_BACKUP}; do \
			echo "$${FETCHCMD} $$$$site$$$$filename" $(DL_TRACE); \
			rm -f "$$$$filename"; \
			if $${FETCHCMD} $$$$filename $$$$site$$$$filename $(DL_TRACE); then \
				: check the size here; \
				[[ ! -e $$$$filename ]] || exit 0; \
			fi; \
		done; \
		;; \
	   *) \
		echo url schema not known; \
		false ;; \
	esac; \
	done
endef

$(foreach distfile,${FULLDISTFILES},$(eval $(call FETCH_template,$(distfile))))
