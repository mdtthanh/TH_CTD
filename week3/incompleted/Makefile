CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: parser

parser: main.o parser.o scanner.o reader.o charcode.o token.o error.o
	${CC} main.o parser.o scanner.o reader.o charcode.o token.o error.o -o parser -w

main.o: main.c
	${CC} ${CFLAGS} main.c -w

scanner.o: scanner.c
	${CC} ${CFLAGS} scanner.c -w

parser.o: parser.c
	${CC} ${CFLAGS} parser.c -w

reader.o: reader.c
	${CC} ${CFLAGS} reader.c -w

charcode.o: charcode.c
	${CC} ${CFLAGS} charcode.c -w

token.o: token.c
	${CC} ${CFLAGS} token.c -w
 
error.o: error.c
	${CC} ${CFLAGS} error.c -w

clean:
	rm -f *.o *~

