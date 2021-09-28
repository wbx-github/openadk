# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		boost
PKG_VERSION:=		1.77.0
PKG_EXTRAVER:=		1_77
PKG_RELEASE:=		1
PKG_HASH:=		5347464af5b14ac54bb945dc68f1dd7c56f0dad7262816b956138fc53bcc0131
PKG_DESCR:=		portable c++ library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		python2-host
PKG_NEEDS:=		c++
PKG_URL:=		http://www.boost.org/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=boost/}
PKG_OPTS:=		dev

DISTFILES:=		boost_$(PKG_EXTRAVER)_0.tar.gz
WRKDIST=		${WRKDIR}/${PKG_NAME}_$(PKG_EXTRAVER)_0

PKG_FLAVOURS_BOOST:=	DATE_TIME GRAPH GRAPH_PARALLEL IOSTREAMS LOG MATH PROGRAM_OPTIONS PYTHON REGEX SERIALIZATION TEST WAVE

PKGFD_DATE_TIME:=	with date-time
PKGFD_PYTHON:=		with python
PKGFB_PYTHON:=		python2
PKGFS_PYTHON:=		python2
PKGFD_IOSTREAMS:=	with iostreams
PKGFD_GRAPH:=		with graph
PKGFD_GRAPH_PARALLEL:=	with graph_parallel
PKGFD_MATH:=		with math
PKGFD_LOG:=		with log
PKGFD_PROGRAM_OPTIONS:=	with program_options
PKGFD_REGEX:=		with regex
PKGFD_SERIALIZATION:=	with serialization
PKGFD_TEST:=		with test
PKGFD_WAVE:=		with wave

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,BOOST,boost,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

include ${ADK_TOPDIR}/mk/python.mk

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

CONFIGURE_ARGS+=	--target=$(GNU_TARGET_NAME) \
			--host=$(GNU_TARGET_NAME) \
			--build=$(GNU_HOST_NAME) \
			--prefix=${WRKINST}/usr \
			--ignore-site-config \
			--without-mpi \
			--without-context \
			--without-coroutine \
			--without-locale

ifneq (${ADK_PACKAGE_BOOST_IOSTREAMS},)
CONFIGURE_ARGS+=	-sNO_BZIP2=1 -sZLIB_INCLUDE=${STAGING_TARGET_DIR}/usr/include -sZLIB_LIBPATH=${STAGING_TARGET_DIR}/usr/lib
else
CONFIGURE_ARGS+=	--without-iostreams
endif
ifeq (${ADK_PACKAGE_BOOST_DATE_TIME},)
CONFIGURE_ARGS+=	--without-date_time
endif
ifeq (${ADK_PACKAGE_BOOST_PYTHON},)
CONFIGURE_ARGS+=	--without-python
endif
ifeq (${ADK_PACKAGE_BOOST_GRAPH},)
CONFIGURE_ARGS+=	--without-graph
endif
ifeq (${ADK_PACKAGE_BOOST_LOG},)
CONFIGURE_ARGS+=	--without-log
endif
ifeq (${ADK_PACKAGE_BOOST_MATH},)
CONFIGURE_ARGS+=	--without-math
endif
ifeq (${ADK_PACKAGE_BOOST_PROGRAM_OPTIONS},)
CONFIGURE_ARGS+=	--without-program_options
endif
ifeq (${ADK_PACKAGE_BOOST_REGEX},)
CONFIGURE_ARGS+=	--without-regex
endif
ifeq (${ADK_PACKAGE_BOOST_SERIALIZATION},)
CONFIGURE_ARGS+=	--without-serialization
endif
ifeq (${ADK_PACKAGE_BOOST_TEST},)
CONFIGURE_ARGS+=	--without-test
endif
ifeq (${ADK_PACKAGE_BOOST_WAVE},)
CONFIGURE_ARGS+=	--without-wave
endif

ifeq ($(ADK_TARGET_ARCH),arm)
BOOST_ARCH:=	architecture=arm
endif
ifeq ($(ADK_TARGET_CPU_MIPS_MIPS32),y)
BOOST_ARCH:=	architecture=mips32
endif
ifeq ($(ADK_TARGET_CPU_MIPS_MIPS32R2),y)
BOOST_ARCH:=	architecture=mips32r2
endif
ifeq ($(ADK_TARGET_ARCH),mips64)
BOOST_ARCH:=	architecture=mips64
endif
ifeq ($(ADK_TARGET_ARCH),ppc)
BOOST_ARCH:=	architecture=power
endif
ifeq ($(ADK_TARGET_ARCH),sparc)
BOOST_ARCH:=	architecture=sparc
endif
ifeq ($(ADK_TARGET_ARCH),x86_64)
BOOST_ARCH:=	architecture=x86
endif

ifeq ($(ADK_TARGET_ARCH),arm)
BOOST_ABI:=	abi=aapcs
endif
ifeq ($(ADK_TARGET_ARCH),mips)
BOOST_ABI:=	abi=o32
endif

# some variables for build
GPP_PATH:=	${TOOLCHAIN_DIR}/usr/bin/${GNU_TARGET_NAME}-g++
GPP_VERSION:=	"`${GPP_PATH} -v 2>&1 | tail -1 | awk '{print $$3}'`"
BJAM_PATH:=	"`find ${WRKBUILD} -type f -name "bjam$(EXEEXT)"`"
PYTHON_PATH:=	${STAGING_HOST_DIR}/usr/bin/python
PYTHON_INCLUDE:="`find ${STAGING_TARGET_DIR}/usr/include/ -maxdepth 1 -type d -name "python*" | head -1`"
PYTHON_LIB:=	"`find ${STAGING_TARGET_DIR}/usr/lib/ -maxdepth 1 -type d -name "python*" | head -1`"
USER_JAM:=	${WRKBUILD}/tools/build/user-config.jam

ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY)$(ADK_TARGET_BINFMT_FLAT),y)
LINKMODE:=	static
else
LINKMODE:=	shared
endif

pre-build:
	@echo "build bjam..."
	cd $(WRKBUILD)/tools/build/src/engine; ./build.sh gcc

do-build:
	@echo "build boost library..."
	echo "using gcc : ${GPP_VERSION} : ${GPP_PATH} : <compileflags>\"${TARGET_CFLAGS}\" ;" > ${USER_JAM};
ifneq (${ADK_PACKAGE_BOOST_PYTHON},)
	echo "using python : ${PYTHON_VERSION} : ${PYTHON_PATH} : ${PYTHON_INCLUDE} : ${PYTHON_LIB} ;" >> ${USER_JAM};
endif
	(cd ${WRKBUILD}; \
		${BJAM_PATH} \
			-d 2 \
			target-os=linux \
			variant=release \
			threading=multi \
			link=$(LINKMODE) \
			runtime-link=$(LINKMODE) \
			$(BOOST_ARCH) \
			$(BOOST_ABI) \
			binary-format=elf \
			toolset=gcc-${GPP_VERSION} \
			--user-config=${USER_JAM} \
			--layout=system \
			--disable-long-double \
			${CONFIGURE_ARGS} \
			install \
	)

boost-install:
	${INSTALL_DIR} ${IDIR_BOOST}/usr/lib
	${CP} ${WRKINST}/usr/lib/*.so* ${IDIR_BOOST}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
