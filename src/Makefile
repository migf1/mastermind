CC=gcc
CFLAGS=-W -Wextra -Wall -std=c99 -c

mastermind: mastermind.o misc.o
	$(CC) -o mastermind mastermind.o misc.o

mastermind.o: mastermind.c con_color.h misc.h info.h
	$(CC) $(CFLAGS) mastermind.c

misc.o: misc.c misc.h
	$(CC) $(CFLAGS) misc.c

clean:
	rm -fr *\.o mastermind
