/*
 * Copyright (C) 2013 Ilias Stamatis <stamatis.iliass@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>     /* printf(), putchar() */
#include <string.h>    /* strlen(), strncpy(), memset() */
#include <stdlib.h>    /* srand(), rand(), system(), strtol(), exit() */
#include <stdbool.h>   /* bool, true, false */
#include <time.h>      /* time() */
#include <errno.h>

#include "con_color.h"
#include "misc.h"
#include "info.h"

#define DEBUG           0

#define MAX_INPUT     255  /* max accepted length of stdin */
#define MAXSLEN_COLOR  20  /* max string length */

#define NROWS          10  /* number of rows */
#define NCOLS           4  /* number of columns */

#define PEG_SYM      "@@"  /* peg representing symbol */
#define KEYPEG_SYM    "!"  /* key peg representing symbol */
#define KEYPEG_NULL   "."  /* null key peg representing symbol */


typedef int Color;

enum colorid {
	COL_INVALID = -2,
	COL_NULL = -1,
	COL_WHITE = 0,
	COL_BLACK,
	COL_RED,
	COL_GREEN,
	COL_YELLOW,
	COL_BLUE,
	COL_MAGENTA,
	COL_CYAN,
	MAX_COLORS  /* their total count */
};

enum commandid {
	CMD_INVALID = -1,
	CMD_SET,
	CMD_CHECK,
	CMD_EXIT
};

struct setcommand {
	int   pos;  /* position in row */
	enum colorid color;
};


/*
 * strtocolorid:
 *    Convert a c-string to color id and return it.
 */
enum colorid strtocolorid(char *colorstr)
{
	if (!strcmp(colorstr, "white"))
		return COL_WHITE;
	else if (!strcmp(colorstr, "black"))
		return COL_BLACK;
	else if (!strcmp(colorstr, "red"))
		return COL_RED;
	else if (!strcmp(colorstr, "green"))
		return COL_GREEN;
	else if (!strcmp(colorstr, "yellow"))
		return COL_YELLOW;
	else if (!strcmp(colorstr, "blue"))
		return COL_BLUE;
	else if (!strcmp(colorstr, "magenta"))
		return COL_MAGENTA;
	else if (!strcmp(colorstr, "cyan"))
		return COL_CYAN;
	else if (!strcmp(colorstr, "null"))
		return COL_NULL;
	else
		return COL_INVALID;
}

/*
 * print_peg:
 *    Display a peg symbol with the suitable foreground color.
 */
void print_peg(Color peg)
{
	register unsigned int i;

	switch(peg) {
	case COL_WHITE:
		CONOUT_PRINTF(FG_WHITE, PEG_SYM);
		break;
	case COL_BLACK:
		CONOUT_PRINTF(FG_DARKGRAY, PEG_SYM);
		break;
	case COL_RED:
		CONOUT_PRINTF(FG_DARKRED, PEG_SYM);
		break;
	case COL_GREEN:
		CONOUT_PRINTF(FG_DARKGREEN, PEG_SYM);
		break;
	case COL_YELLOW:
		CONOUT_PRINTF(FG_DARKYELLOW, PEG_SYM);
		break;
	case COL_BLUE:
		CONOUT_PRINTF(FG_DARKBLUE, PEG_SYM);
		break;
	case COL_MAGENTA:
		CONOUT_PRINTF(FG_DARKMAGENTA, PEG_SYM);
		break;
	case COL_CYAN:
		CONOUT_PRINTF(FG_DARKCYAN, PEG_SYM);
		break;
	case COL_NULL:
	default:
		for (i = 0; i < strlen(PEG_SYM); i++)
			putchar(' ');
		break;
	}
}

/*
 * print_keypeg:
 *    Display a keypeg symbol with the suitable foreground color.
 */
void print_keypeg(Color keypeg)
{
	switch(keypeg) {
	case COL_RED:
		CONOUT_PRINTF(FG_DARKRED, KEYPEG_SYM);
		break;
	case COL_YELLOW:
		CONOUT_PRINTF(FG_DARKYELLOW, KEYPEG_SYM);
		break;
	case COL_NULL:
	default:
		printf(KEYPEG_NULL);
		break;
	}
}

/*
 * print_table:
 *    Display game board with pegs and key pegs.
 */
void print_table(Color pegs[][NCOLS], Color keypegs[][NCOLS], int rows)
{
	register int i, j;

	for (i = 0; i < rows; i++) {
		printf("%2d. ", i + 1);
		/* print pegs */
		for (j = 0; j < NCOLS; j++) {
			putchar('|');
			print_peg(pegs[i][j]);
		}
		printf("|  ");
		/* print key pegs */
		for (j = 0; j < NCOLS; j++) {
			print_keypeg(keypegs[i][j]);
		}
		printf("\n    -------------\n");
	}
}

/*
 * print_available_colors:
 *    Print all color's names and a colored peg of the corresponding color.
 */
void print_available_colors(void)
{
	register int i;
	char *colors[] = {"white", "black", "red", "green", "yellow", "blue",
	                  "magenta", "cyan"};

	for (i = 0; i < MAX_COLORS; i++) {
		printf("%s: ", colors[i]);
		print_peg(strtocolorid(colors[i]));
		printf(", ");
		if (i == 3)
			putchar('\n');
	}
	printf("null:\n\n");
}

/*
 * print_secret_code:
 *    Print cpu's secret code.
 */
void print_secret_code(Color secrcode[], int n)
{
	register int i;

	printf("My secret code was:\n\n");
	for (i = 0; i < n; i++) {
		putchar('|');
		print_peg(secrcode[i]);
	}
	putchar('|');
	printf("\n-------------\n");
}

/*
 * displa_data:
 *    Just a wrapper to call real display functions.
 */
void display_data(Color pegs[][NCOLS], Color keypegs[][NCOLS], int n)
{
	system(SYSTEM_CLEAR); /* clear screen */
	print_table(pegs, keypegs, n);
	print_available_colors();
}

/*
 * appears_in_row:
 *    Return false if color is unique in its row, else true.
 */
bool appears_in_row(Color color, Color row[], int n)
{
	register int *p;

	for (p = row; p < row + n; p++)
		if (color == *p)
			return true;

	return false;
}

/*
 * set_secret_code:
 *    Set a random secret code for cpu player.
 *    Each color should appear only once.
 */
void set_secret_code(Color secrcode[], int n, int numcolors)
{
	register int i;
	Color choice;

	for (i = 0; i < n; i++) {
		do {
			choice = rand() % numcolors;
		} while(appears_in_row(choice, secrcode, n));
		secrcode[i] = choice;
	}
}

/*
 * set_peg:
 *    Update the value of rowpegs indicated by setcmd, if requested position
 *    is not out of game board range and requested color doesn't appears
 *    in the same row.
 *
 *    Return true if update succeed, else false.
 */
bool set_peg(struct setcommand setcmd, Color rowpegs[], int n)
{
	if (setcmd.pos < 1 || setcmd.pos > n) {
		puts("Out of range. Not such column.");
		return false;
	}
	if (setcmd.color != COL_NULL && setcmd.color != rowpegs[setcmd.pos-1]
	&& appears_in_row(setcmd.color, rowpegs, n)) {
		puts("You can't put the same color twice in a row.");
		return false;
	}

	rowpegs[setcmd.pos-1] = setcmd.color;
	return true;
}


/*
 * set_keypegs:
 *    Check if user's code matches cpu's secret code and update keypegs.
 *    For every user's color that it's in the same position as in secret code
 *    one red peg should be added and for each color that appears in secret
 *    code but it is not in the correct position one yellow peg should be
 *    added. Red pegs must appear first in keypegs array, then yellow pegs,
 *    then null.
 *
 *    Return true if user's code is the same with secret code, else false.
 */
bool set_keypegs(Color secrcode[], Color pegs[], Color keypegs[], int n)
{
	register int i, j;
	int red = 0, yellow = 0;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (pegs[i] == secrcode[j]) {
				if (i == j) /* correct position */
					red++;
				else
					yellow++;
			}
	/* red pegs first, yellow second */
	for (i = 0; i < red; i++)
		keypegs[i] = COL_RED;
	for (i = red; i < red + yellow; i++)
		keypegs[i] = COL_YELLOW;

	return red == n;
}

/*
 * cancheck:
 *    Return true if there are no null fields in rowpegs, else false.
 */
bool cancheck(Color rowpegs[], int n)
{
	register int i;

	for (i = 0; i < n; i++)
		if (rowpegs[i] == COL_NULL)
			return false;
	return true;
}

/*
 * input_parser:
 *    Parse the command line arguments and check wether they corresponds
 *    to a valid command. For a set command, update setcmd values.
 *
 *    Valid commands are:
 *       - check
 *       - n color, where n is an integer and color matches a color in
 *                  colors[] array. This called as set command.
 *       - exit
 */
enum commandid input_parser(char *input, struct setcommand *setcmd)
{
	/* to be filled by s_tokenize() with NUL-terminated string tokens */
	char *tokens[3] = {NULL};
	int ntokens = 0;  /* number of tokens */
	char *p;          /* to be passed to strtol */

	ntokens = s_tokenize(input, tokens, 3, " \n");

	if (!ntokens || ntokens > 2) /* no command with more than 2 arguments */
		return CMD_INVALID;
	if (!strcmp("check", tokens[0]) || !strcmp("exit", tokens[0])) {
		if (ntokens != 1)
			return CMD_INVALID;
		if (!strcmp("check", tokens[0]))
			return CMD_CHECK;
		return CMD_EXIT;
	}
	errno = 0;
	setcmd->pos = strtol(tokens[0], &p, 10);
	/* check if first argument is a valid integer */
	if (errno == ERANGE || *p != '\0') /* strtol failed */
		return CMD_INVALID;

	setcmd->color = strtocolorid(tokens[1]);
	/* chech if second argument is a known color */
	if (setcmd->color != COL_INVALID)
		return CMD_SET;

	return CMD_INVALID;
}

/*
 * start_menu:
 *    Print available options and prompt user for an option.
 *    Return only when user enters "s".
 *    If user enters "q" terminate program, else display program info.
 */
void start_menu(void)
{
	char input[MAX_INPUT + 1];  /* to be filled by user's input */
	char *tokens[2] = {NULL};   /* to be filled by s_tokenize() */
                                    /* with NUL-terminated string tokens */

	for (;;) {
		system(SYSTEM_CLEAR);
		printf(START_MENU, APP_NAME);

		fgets(input, sizeof(input), stdin);
		s_tolower(input); /* lowerize input */
		s_tokenize(input, tokens, 2, " \n");

		if (tokens[0] == NULL || tokens[1] != NULL)
			continue;

		if (!strcmp(tokens[0], "s")) {
			return;
		} else if (!strcmp(tokens[0], "c")) {
			system(SYSTEM_CLEAR);
			printf(CREDITS, APP_NAME, APP_VERSION, AUTHOR,
			       AUTHOR_MAIL, APP_NAME, AUTHOR);
			puts("[Press Enter.]");
			fgets(input, sizeof(input), stdin);
		} else if (!strcmp(tokens[0], "i")) {
			system(SYSTEM_CLEAR);
			puts(INFO_ABOUT_PLAYING);
			puts("[Press Enter.]");
			fgets(input, sizeof(input), stdin);
		} else if (!strcmp(tokens[0], "q"))
			exit(EXIT_SUCCESS);
	}
}


int main(void)
{
	Color pegstable[NROWS][NCOLS];    /* main game board */
	Color keypegstable[NROWS][NCOLS]; /* key pegs table */
	Color secrcode[NCOLS];            /* cpu's secret code */

	char input[MAX_INPUT + 1];        /* to be filled by user's input */
	char *tokens[2] = {NULL};         /* to be filled by s_tokenize() */
	                                  /* with NUL-terminated string tokens*/
	struct setcommand setcmd;
	int round;                    /* rounds counter */

	/* initialize pseudo-random seed */
	srand((unsigned) time(NULL));

	/* save console's color-state and initialize the interface */
	CONOUT_INIT();

	start_menu();

game_start: /* optionally multiple games */
	/* initialize tables */
	memset(pegstable, COL_NULL, sizeof(pegstable));
	memset(keypegstable, COL_NULL, sizeof(keypegstable));

	set_secret_code(secrcode, NCOLS, MAX_COLORS);
	display_data(pegstable, keypegstable, NROWS);

	round = 0;
	while (round < NROWS) {
		#if DEBUG
			print_secret_code(secrcode, NCOLS);
		#endif
		printf("> ");
		fgets(input, sizeof(input), stdin);
		s_tolower(input);  /* lowerize input */

		switch (input_parser(input, &setcmd)) {
		case CMD_SET:
			if (set_peg(setcmd, pegstable[round], NCOLS)) {
				display_data(pegstable, keypegstable, NROWS);
			}

			break;
		case CMD_CHECK:
			if (cancheck(pegstable[round], NCOLS)) {
				if (set_keypegs(secrcode, pegstable[round],
				    keypegstable[round], NCOLS)) {
					display_data(pegstable, keypegstable,
					             NROWS);
					goto game_end;
				}
				round++;
				display_data(pegstable, keypegstable, NROWS);
			} else {
				puts("There are empty fields.");
			}
			break;
		case CMD_EXIT:
			goto exit_success;
			break;
		case CMD_INVALID:
		default:
			puts("Invalid command.");
			break;
		}
	}
game_end:
	if (round == NROWS) {
		puts("You lost.");
		print_secret_code(secrcode, NCOLS);
	} else {
		puts("Congratulations! You found my secret code!");
	}

	puts("Do you want to play again? (y/n)");
	fgets(input, sizeof(input), stdin);
	s_tokenize(input, tokens, 2, " \n");
	if (tokens[0] != NULL
	&& (!strcmp(tokens[0], "y") || !strcmp(tokens[0], "yes")))
		goto game_start;

exit_success:
	/* restore console's color-state, as saved with CONOUT_INIT() */
	CONOUT_RESTORE();

	exit(EXIT_SUCCESS);
}
