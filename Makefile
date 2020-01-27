# free Makefile
# Public Domain

CC ?=		cc
CFLAGS ?=	-g -O2 -Wall
CFLAGS +=	-lutil
PREFIX ?=	/usr/local

all:
	${CC} ${CFLAGS} ${LDFLAGS} -o free free.c

install:
	install -c -s -m 555 free ${PREFIX}/bin
	install -c -m 444 free.1 ${PREFIX}/man/man1

clean:
	rm -f free
