SRCS+=		tool.c
SRCS+=		sys_linux.c
SRCS+=		replace.c
SRCS+=		compress.c
#SRCS+=		fts_debg.c
SRCS+=		cpr_get.c
SRCS+=		cpr_list.c
SRCS+=		cpr_lsth.c
SRCS+=		ft_creat.c
SRCS+=		ft_pack.c
SRCS+=		ft_packm.c
SRCS+=		fts_subs.c
SRCS+=		header.c
SRCS+=		minilzop.c
SRCS+=		unwraps.c
SRCS+=		wraps.c

# the compressor
SRCS+=		c_lzo1x1.c
CPPFLAGS+=	-Ibundled

OBJS=		${SRCS:.c=.o}

# build for the target
CPPFLAGS+=	-DSMALL -D__USE_GNU

all: fwcf.helper.out

fwcf.helper.out: ${OBJS}
	${CC} -o $@ ${OBJS} ${LDFLAGS}
