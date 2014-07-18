CC=gcc
CFLAGS=-W -Wextra -Wall -std=c99 -s -O2 -c

mastermind: mastermind.o colors.o misc.o
	$(CC) -o mastermind mastermind.o misc.o colors.o

mastermind.o: mastermind.c con_color.h colors.h misc.h info.h
	$(CC) $(CFLAGS) mastermind.c

colors.o: colors.c colors.h con_color.h
	$(CC) $(CFLAGS) colors.c

misc.o: misc.c misc.h
	$(CC) $(CFLAGS) misc.c

clean:
	rm -fr *\.o mastermind
