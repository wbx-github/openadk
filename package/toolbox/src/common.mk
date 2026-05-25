OBJS:=		${SRCS:.c=.o}
CFLAGS?=	-Os -Wall
CPPFLAGS+=	-I.
#CPPFLAGS+=	-D_FILE_OFFSET_BITS=64
CPPFLAGS+=	-isystem ../lib
CPPFLAGS+=	-D'__COPYRIGHT(x)=' -D'__RCSID(x)='
#CPPFLAGS+=	-D'__unused=__attribute__((__unused__))'
CPPFLAGS+=	-D'__dead=__attribute__((__noreturn__))'
CLEANFILES+=	${OBJS} ${PROG}

all:

COMPILE.c=	${CC} ${CPPFLAGS} ${CFLAGS} ${CFLAGS_$@} -c

.c.o:
	${COMPILE.c} -o $@ $<

clean:
	rm -f ${CLEANFILES}

# no depend magic; if you change a .h file, just make clean
