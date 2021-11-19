# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		subversion
PKG_VERSION:=		1.14.1
PKG_RELEASE:=		1
PKG_HASH:=		dee2796abaa1f5351e6cc2a60b1917beb8238af548b20d3e1ec22760ab2f0cad
PKG_DESCR:=		revision control program
PKG_SECTION:=		dev/scm
PKG_DEPENDS:=		zlib apr apr-util libexpat libsqlite neon liblz4
PKG_BUILDDEP:=		apr-util expat apr zlib sqlite neon lz4
PKG_URL:=		http://subversion.apache.org/
PKG_SITES:=		http://artfiles.org/apache.org/subversion/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,SUBVERSION,subversion,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_LDFLAGS+=	-ltinfo
CONFIGURE_ARGS+=	--with-apr=${STAGING_TARGET_DIR}/usr/bin/apr-1-config \
			--with-apr-util=${STAGING_TARGET_DIR}/usr/bin/apr-1-config \
			--with-utf8proc=internal \
			--disable-mod-activation \
			--disable-keychain \
			--without-apxs \
			--without-swig \
			--disable-experimental-libtool \
			--without-jikes \
			--without-jdk \
			--disable-javahl \
			--without-berkeley-db
CONFIGURE_ENV+=		LIBS='-lsqlite3 -laprutil-1 -lapr-1 -lexpat -ltinfo'

subversion-install:
	${INSTALL_DIR} ${IDIR_SUBVERSION}/usr/{bin,lib}
	${INSTALL_BIN} ${WRKINST}/usr/bin/svn ${IDIR_SUBVERSION}/usr/bin
	${CP} ${WRKINST}/usr/lib/libsvn*.so* ${IDIR_SUBVERSION}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
