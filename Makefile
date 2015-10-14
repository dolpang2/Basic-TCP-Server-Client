CC = gcc
LIB = -lnsl

all : server client

server : serv.o readn.o writen.o readline.o error.o
	$(CC) -g -o echoserv serv.o readn.o writen.o readline.o error.o $(LIB)

client : cli.o readn.o writen.o readline.o error.o
	$(CC) -g -o echocli cli.o readn.o writen.o readline.o error.o $(LIB)

serv : serv.c inet.h
	$(CC) -g -c serv.c

cli : cli.c inet.h
	$(CC) -g -c cli.c

readn : readn.c
	$(CC) -g -c readn.c

writen : writen.c
	$(CC) -g -c writen.c

readline : readline.c
	$(CC) -g -c readline.c

error : error.c
	$(CC) -g -c error.c

clean :
	\rm -f *.o echoserv echocli core
