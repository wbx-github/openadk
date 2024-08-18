# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

install: ${STAGING_HOST_DIR}/usr/bin/depmaker ${STAGING_HOST_DIR}/usr/bin/pkgrebuild ${STAGING_HOST_DIR}/usr/bin/dkgetsz

${STAGING_HOST_DIR}/usr/bin/depmaker: depmaker.c
	${CC_FOR_BUILD} ${FLAGS_FOR_BUILD} -w -o $@ depmaker.c

${STAGING_HOST_DIR}/usr/bin/pkgrebuild: pkgrebuild.c strmap.c
	${CC_FOR_BUILD} ${FLAGS_FOR_BUILD} -w -o $@ pkgrebuild.c strmap.c

${STAGING_HOST_DIR}/usr/bin/dkgetsz: dkgetsz.c
	${CC_FOR_BUILD} ${FLAGS_FOR_BUILD} -w -o $@ dkgetsz.c

include $(ADK_TOPDIR)/mk/tools.mk
