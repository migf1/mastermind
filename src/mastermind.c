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
#include <ctype.h>     /* tolower() */
#include <errno.h>

#include "con_color.h"
#include "colors.h"
#include "misc.h"
#include "info.h"

#define DEBUG              1

/* Dimensions of the board */
#define NROWS              10
#define NCOLS              4

/* Output-strings for displaying pegs and keypegs */
#define PEG_OUT            "@@"
#define KPEG_OUT           "*"
#define KPEG_OUT_EMPTY     "."

/* Keypeg color-indices for exact-matches,
 * approximate matches, and no-matches.
 */
#define KPEG_EXACT         IDX_RED
#define KPEG_APPROX        IDX_YELLOW
#define KPEG_NOMATCH       IDX_NOCOLOR

/* A MasterMindCode is a sequence of NCOLS color-indices. */
typedef enum ColorIdx MMCode[NCOLS];

/* For handling commands given by the user during the game. */
enum CmdId {
	CMD_INVALID_DUP_COLORS = -2,
	CMD_INVALID = -1,
	CMD_QUIT,
	CMD_SHOW_GUESS,
	CMD_CHECK_GUESS,
	CMD_SHOW_AND_CHECK_GUESS,
	CMD_HELP,
	CMD_CREDITS
};

enum ErrId {
	ERR_NONE = 0,
	ERR_NULL_ARG,
	ERR_INV_ARG,
	ERR_DUP_COLORS
};

/* The board consists of 2 sub-boards:
 * one for pegs & one for keypegs
 */
typedef struct Board {
	MMCode pegs[NROWS];
	MMCode kpegs[NROWS];
} Board;

/* --------------------------------------------------------------
 * void show_help():
 *
 * --------------------------------------------------------------
 */
void show_help( void )
{
	clear_screen();
	puts( INFO_ABOUT_PLAYING );
	press_enter();
}

/* --------------------------------------------------------------
 * void show_credits():
 *
 * --------------------------------------------------------------
 */
void show_credits( void )
{
	clear_screen();
	printf(
		CREDITS,
		APP_NAME,
		APP_VERSION,
		AUTHOR,
		AUTHOR_MAIL,
		APP_NAME,
		AUTHOR
		);
	press_enter();
}

/* --------------------------------------------------------------
 * void mmcode_init():
 *
 * Initialize the given mastermind-code with no-color indices.
 *
 * NOTE: Since no-color indices are non-0 ones,
 *       using memset() is not a good idea.
 * --------------------------------------------------------------
 */
void mmcode_init( MMCode mmcode )
{
	for (int i=0; i < NCOLS; i++) {
		mmcode[i] = IDX_NOCOLOR;
	}
}

/* --------------------------------------------------------------
 * int mmcode_lookup():
 *
 * Lookup in the specified mastermind-code (mmcode) for the specified
 * color-index element (elem). Return the element's 0-based index inside
 * the mastermind-code, or -1 if the element was not found.
 * --------------------------------------------------------------
 */
int mmcode_lookup( const MMCode mmcode, enum ColorIdx elem )
{

	for (size_t i=0; i < NCOLS; i++) {
		if  ( elem >= 0 && elem == mmcode[i] ) {
			return i;
		}
	}
	return -1;
}

/* --------------------------------------------------------------
 * enum ErrId mmcode_set_from_string():
 *
 * Set all elements of the specified mastermind-code (mmcode)
 * according to the contents of the specified c-string (string).
 * On error, mmcode gets initialized and an appropriate error-code
 * is returned. On success, ERR_NONE is returned and mmcode contains
 * the color-indices that correspond to the color-codes contained in
 * the c-string.
 *
 * NOTE: The c-string is expected to contain color-codes, as they
 *       defined in the file: colors.c (they are actually ascii-codes
 *       that uniquely identify each color).
 * --------------------------------------------------------------
 */
enum ErrId mmcode_set_from_string(
	MMCode      mmcode,
	const char  *string,
	const Color *colors
	)
{
	enum ColorIdx temp;

	/* start fresh */
	mmcode_init( mmcode );

	if ( NULL == string || NULL == colors ) {
		return ERR_NULL_ARG;
	}
	if ( NCOLS != strlen(string) ) {
		return ERR_INV_ARG;
	}

	for (size_t i=0; i < NCOLS; i++)
	{
		temp = colors_lookup_code(colors, string[i] );
		if  ( IDX_INVALID == temp ) {
			return ERR_INV_ARG;
		}
		if ( -1 != mmcode_lookup(mmcode, temp) ) {
			return ERR_DUP_COLORS;
		}
		mmcode[i] = temp;
	}

	return ERR_NONE;
}

/* --------------------------------------------------------------
 * bool mmcode_set_randomly():
 *
 * Set a random secret code. Each color appears only once.
 * --------------------------------------------------------------
 */
bool mmcode_set_randomly( MMCode mmcode, const Color *colors )
{
	int i;
	enum ColorIdx r;

	if ( NULL == colors ) {
		return false;
	}

	/* start fresh */
	mmcode_init( mmcode );

	/* set NCOLS unique color-indices randomly inside mmcode */
	for (i=0; i < NCOLS; i++)
	{
		r = colors_get_random_index(colors);
		if ( -1 != mmcode_lookup(mmcode, r) ) {
			--i;
			continue;
		}
		mmcode[i] = r;
	}

	return true;
}

/* --------------------------------------------------------------
 * void mmcode_copy():
 *
 * --------------------------------------------------------------
 */
void mmcode_copy( MMCode dst, MMCode src )
{
	memmove( dst, src, NCOLS * sizeof(enum ColorIdx) );
}

/* --------------------------------------------------------------
 * void mmcode_is_full():
 *
 * Return true if the specified mastermind-code contains valid
 * color-indices, and it has no empty slots.
 * --------------------------------------------------------------
 */
bool mmcode_is_full( MMCode mmcode )
{
	for (size_t i=0; i < NCOLS; i++) {
		if ( IDX_INVALID == mmcode[i] || IDX_NOCOLOR == mmcode[i] ) {
			return false;
		}
	}
	return true;
}

/* --------------------------------------------------------------
 * bool mmcode_set_as_hint():
 *
 * Set the mastermind-code specified by the 1st argument (hint), as
 * a game-hint resulting from comparing the mastermind-codes specified
 * by the last two arguments( mmc1 and mmc2, respectively).
 *
 * Return true if all the color-indices of mmc1 and mmc2 are valid,
 * non-empty and their values & order match exactly.
 * --------------------------------------------------------------
 */
bool mmcode_set_as_hint( MMCode hint, MMCode mmc1, MMCode mmc2 )
{
	int nexact, napprox;   /* count of exact & approximate matches */
	int i,j;

	/* Demand valid, non-empty color-indices in all positions
	 * of both mmc1 & mmc2.
	 */
	if ( !mmcode_is_full(mmc1) || !mmcode_is_full(mmc2) ) {
		return false;
	}

	/* Count exact & approximate matches between mmc1 and mmc2. */
	nexact = napprox = 0;
	for (int i=0; i < NCOLS; i++)
	{
		for (j=0; j < NCOLS; j++)
		{
			if ( mmc1[i] == mmc2[j] ) {
				if (i == j) {
					nexact++;   /* exact match */
				}
				else {
					napprox++;  /* approximate match */
				}
			}
		}
	}

	/* Set the hint mmcode by filling-in exact-matches first,
	 * then followed by approximate-matches. Any remaining
	 * slots to the end of the mmcode are set to no-match.
	 */
	for (i=0; i < nexact; i++) {
		hint[i] = KPEG_EXACT;
	}
	for (i=nexact; i < nexact + napprox; i++) {
		hint[i] = KPEG_APPROX;
	}
	for (j=i; j < NCOLS; j++) {
		hint[j] = KPEG_NOMATCH;
	}

	return nexact == NCOLS;
}

/* --------------------------------------------------------------
 * bool init_board():
 *
 * --------------------------------------------------------------
 */
bool init_board( Board *board, const Color *colors )
{
	if ( NULL == board || NULL == colors ) {
		return false;
	}

	for (int i=0; i < NROWS; i++) {
		mmcode_init( board->pegs[i] );
		mmcode_init( board->kpegs[i] );
	}
	return true;
}

/* --------------------------------------------------------------
 * void draw_single_peg():
 *
 * Display the specified color-index as a peg.
 *
 * The output is a PEG_OUT string, using the foreground color that
 * corresponds to the color-index (1st argument) in the specified
 * list of colors (2nd argument).
 *
 * If the color-index is invalid or a no-color one, then all chars
 * of PEG_OUT are displayed as un-colorized spaces.
 * --------------------------------------------------------------
 */
void draw_single_peg( enum ColorIdx peg, const Color *colors )
{
	if ( peg < 0 ) {  /* either IDX_NOCOLOR or IDX_INVALID */
		for (size_t i=0; i < strlen(PEG_OUT); i++) {
			putchar(' ');
		}
		fflush( stdout );
		return;
	}

	const ConSingleColor *fg = colors_get_fg_at_idx( colors, peg );
	if ( NULL == fg ) {
		for (size_t i=0; i < strlen(PEG_OUT); i++) {
			putchar(' ');
		}
		fflush( stdout );
		return;
	}

	CONOUT_PRINTF( *fg, BG_DEFAULT, PEG_OUT );
}

/* --------------------------------------------------------------
 * void draw_single_kpeg():
 *
 * Display the specified color-index as a keypeg.
 *
 * The output is either a KPEG_OUT or a KPEG_OUT_EMPTY string,
 * depending on whether the value of color-index (kpeg) dictates
 * a match (expected to be KPEG_EXACT or KPEG_APPROX) or not,
 * respectively.
 *
 * In the former case, KPEG_OUT is displayed using the foreground
 * color that corresponds to the color-index (1st argument) in the
 * specified list of colors (2nd argument).
 *
 * In the latter case, or if color-index is invalid, KPEG_OUT_EMPTY
 * is displayed un-colorized.
 * --------------------------------------------------------------
 */
void draw_single_kpeg( enum ColorIdx kpeg, const Color *colors )
{
	const ConSingleColor *fg = colors_get_fg_at_idx( colors, kpeg );
	if ( KPEG_NOMATCH == kpeg || NULL == fg ) {
		printf( "%s", KPEG_OUT_EMPTY);
		fflush( stdout );
		return;
	}

	CONOUT_PRINTF( *fg, BG_DEFAULT, KPEG_OUT );
}

/* --------------------------------------------------------------
 * bool draw_board():
 *
 * --------------------------------------------------------------
 */
bool draw_board( const Board *board, const Color *colors )
{
	int i,j;

	if ( NULL == board || NULL == colors ) {
		return false;
	}

	for (i=0; i < NROWS; i++)
	{
		printf( "%2d. ", i+1 );

		/* print pegs */
		for (j=0; j < NCOLS; j++) {
			putchar('|');
			draw_single_peg( board->pegs[i][j], colors );
		}
		printf("|  ");

		/* print keypegs */
		for (j=0; j < NCOLS; j++) {
			draw_single_kpeg( board->kpegs[i][j], colors );
		}

		puts( "\n    -------------" );
	}
	return true;
}

/* --------------------------------------------------------------
 * void draw_color_legends():
 *
 * Display legends for all colors present in the specified list
 * of colors.
 *
 * The legend of any color consists of a peg output-string colorized
 * according to the color, followed by the color's non-colorized label.
 *
 * The function displays 3 color legends per line.
 * --------------------------------------------------------------
 */
void draw_color_legends( const Color *colors )
{
	register int i;
	const ConSingleColor *fg = NULL;

	for (i=0; i < MAXCOLORS; i++)
	{
		fg = colors_get_fg_at_idx(colors, i);
		CONOUT_PRINTF( *fg, BG_DEFAULT, "%s", PEG_OUT );
		putchar( ' ' );
		fflush( stdout );
		colors_print_label_at_idx( colors, i );
		putchar( '\t' );
		fflush( stdout );
		if (i == 3) {
			putchar('\n');
		}
	}
	putchar( '\n' );
}

/* --------------------------------------------------------------
 * void draw_secret():
 *
 * Display the secret-code, treating each of its elements as a peg.
 * --------------------------------------------------------------
 */
void draw_secret( MMCode secret, const Color *colors )
{
	int i;

	printf( "%s", "The secret-code was: " );
	fflush( stdout );

	for (i=0; i < NCOLS; i++) {
		putchar( colors_get_code_at_idx(colors, secret[i]) );
	}
	printf( "%s", " -> " );
	fflush( stdout );

	for (i=0; i < NCOLS; i++) {
		putchar('|');
		draw_single_peg( secret[i], colors );
	}
	putchar('|');
	fflush( stdout );

	putchar( '\n' );
}

/* --------------------------------------------------------------
 * void redraw_screen():
 *
 * --------------------------------------------------------------
 */
void redraw_screen(
	const Board *board,
	const Color *colors
	)
{
	clear_screen();
	draw_board( board, colors );
	draw_color_legends( colors );
}

/* --------------------------------------------------------------
 * enum CmdId parse_cmdline():
 *
 * --------------------------------------------------------------
 */
enum CmdId parse_cmdline( char *cmdline, Color *colors, MMCode guess )
{
	size_t len;
	enum ErrId err = ERR_NONE;

	if ( NULL == cmdline ) {
		return CMD_INVALID;
	}

	s_tolower( cmdline );
	s_trim( cmdline );

	if ( 0 == strcmp("quit", cmdline) || 0 == strcmp("q", cmdline)) {
		return CMD_QUIT;
	}
	if ( 0 == strcmp("check", cmdline) ) {
		return CMD_CHECK_GUESS;
	}
	if ( 0 == strcmp("help", cmdline) || 0 == strcmp("h", cmdline) ) {
		return CMD_HELP;
	}
	if ( 0 == strcmp("credits", cmdline) || 0 == strcmp("c", cmdline) ) {
		return CMD_CREDITS;
	}

	/* is it a plain guess? */
	len = strlen( cmdline );
	if ( NCOLS == len )
	{
		err = mmcode_set_from_string(guess, cmdline, colors);
		if ( ERR_DUP_COLORS == err ) {
			return CMD_INVALID_DUP_COLORS;
		}
		if ( ERR_NONE != err ) {
			return CMD_INVALID;
		}
		return CMD_SHOW_GUESS;
	}

	/* is it a guess with embed check-request? */
	if ( NCOLS + 2 == len )
	{
		if ( 0 != strcmp("-c", &cmdline[len-2]) ) {
			return CMD_INVALID;
		}

		len = NCOLS;
		cmdline[len] = '\0';

		err = mmcode_set_from_string(guess, cmdline, colors);
		if ( ERR_DUP_COLORS == err ) {
			return CMD_INVALID_DUP_COLORS;
		}
		if ( ERR_NONE != err ) {
			return CMD_INVALID;
		}
		return CMD_SHOW_AND_CHECK_GUESS;
	}

	return CMD_INVALID;
}

/* --------------------------------------------------------------
 * void do_intro_menu():
 *
 * Print available options and prompt user for an option.
 * Return only when user enters "s".
 * If user enters "q" terminate program, else display program info.
 * --------------------------------------------------------------
 */
void do_intro_menu( void )
{
	for (;;) {
		clear_screen();
		printf(START_MENU, APP_NAME);

		int c = tolower( prompt_for_char(NULL) );
		switch ( c )
		{
			case 's':
				return;

			case 'c':
				show_credits();
				break;

			case 'h':
				show_help();
				break;

			case 'q':
				exit(EXIT_SUCCESS);
				break;
		}
	}
}

/* --------------------------------------------------------------
 * Application's entry point.
 * --------------------------------------------------------------
 */
int main( void )
{
	Color *colors = NULL;
	Board board;
	MMCode secret;
	MMCode guess;

	enum CmdId cmd = CMD_INVALID;
	char input[MAX_INPUT + 1];        /* to be filled by user's input */
	int round;                        /* rounds counter */
	bool haswon;                      /* indicates if player won */

	/* initialize pseudo-random seed */
	srand((unsigned) time(NULL));

	/* save console's color-state and initialize the interface */
	CONOUT_INIT();

	colors = new_colors();
	if ( NULL == colors ) {
		goto exit_failure;
	}

	do_intro_menu();

	do { /* optionally multiple games */

		init_board( &board, colors );
		mmcode_set_randomly( secret, colors );
		mmcode_init( guess );

		round = 0;
		haswon = false;
		while ( round < NROWS && !haswon )
		{

			redraw_screen( &board, colors );
#if DEBUG
			draw_secret( secret, colors );
#endif
			prompt_for_string( "> ", input, sizeof(input) );
			cmd = parse_cmdline( input, colors, guess );

			switch( cmd ) {
				case CMD_QUIT:
					goto exit_success;

				case CMD_SHOW_GUESS:
					mmcode_copy(board.pegs[round], guess);
					break;

				case CMD_CHECK_GUESS:
					if ( !mmcode_is_full(guess) ) {
						break;
					}
					/* else fallback */
				case CMD_SHOW_AND_CHECK_GUESS:
					haswon = mmcode_set_as_hint(
							board.kpegs[round],
							guess,
							secret
							);
					mmcode_copy( board.pegs[round], guess);
					mmcode_init( guess );
					round++;
					break;

				case CMD_CREDITS:
					show_credits();
					break;

				case CMD_HELP:
					show_help();
					break;

				case CMD_INVALID_DUP_COLORS:
					puts( "Only guesses with unique colors are allowed." );
					press_enter();
					break;

				case CMD_INVALID:
				default:
					puts( "invalid command" );
					press_enter();
					break;
			}

		}

		if ( haswon ) {
			redraw_screen( &board, colors );
			puts( "Congratulations! You found the secret code!" );
		}
		else {
			puts("You lost.");
			draw_secret( secret, colors );
		}

	} while (
		'y' == tolower(
			prompt_for_char( "Wanna play again (y/)? ")
			)
		);

exit_success:
	colors_free( colors );

	/* restore console's color-state, as saved with CONOUT_INIT() */
	CONOUT_RESTORE();
	exit(EXIT_SUCCESS);

exit_failure:
	CONOUT_RESTORE();
	exit(EXIT_FAILURE);
}
