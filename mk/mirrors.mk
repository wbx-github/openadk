# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

MASTER_SITE_BACKUP?=	http://distfiles.${ADK_HOST}/

MASTER_SITE_OPENADK?=	\
	http://distfiles.openadk.org/ \

MASTER_SITE_MIRBSD?=	\
	http://www.mirbsd.org/MirOS/distfiles/ \
	http://pub.allbsd.org/MirOS/distfiles/ \

ifeq ($(ADK_TARGET_KERNEL_NO_MIRROR),)
MASTER_SITE_KERNEL?=	\
	https://www.kernel.org/pub/linux/ \
	http://www.kernel.org/pub/linux/ \

else
MASTER_SITE_KERNEL?=	\
	http://distfiles.openadk.org/ \

endif

MASTER_SITE_GNU?=	\
	https://ftp.fau.de/gnu/ \
	https://ftp.halifax.rwth-aachen.de/gnu/ \
	https://ftp.gnu.org/gnu/ \
	http://ftp.gnu.org/gnu/ \

MASTER_SITE_SOURCEFORGE?=	\
	https://downloads.sourceforge.net/projects/ \
	http://nchc.dl.sourceforge.net/sourceforge/ \

MASTER_SITE_MYSQL?=		\
	http://sunsite.informatik.rwth-aachen.de/mysql/ \
	ftp://ftp.fu-berlin.de/unix/databases/mysql/ \
	http://mysql.easynet.be/ \

MASTER_SITE_GNOME?=	\
	https://download.gnome.org/sources/ \

