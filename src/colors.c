#include <stdio.h>     /* printf(), putchar() */
#include <string.h>    /* strlen(), strncpy(), memset() */
#include <stdlib.h>    /* srand(), rand(), system(), strtol(), exit() */
#include <stdbool.h>   /* bool, true, false */

#include "con_color.h"
#include "colors.h"

#define _VALID_IDX(idx)  ( (idx) >= 0 && (idx) < MAXCOLORS )

struct _Color {
	const char *label;  /* has a '&' before the char to be used as code*/
	int code;           /* ascii-code uniquely identifying this color */
	ConSingleColor fg;  /* foreground color to be displayed */
};

static const char *_g_labels[MAXCOLORS] = {
	"&white",  "&black", "&red", "&green",
	"&yellow", "b&lue", "&magenta", "&cyan"
};
static const ConSingleColor _g_concolors[MAXCOLORS] = {
	FG_WHITE,  FG_DARKGREY, FG_RED, FG_GREEN,
	FG_YELLOW, FG_BLUE, FG_MAGENTA, FG_CYAN
};

/* --------------------------------------------------------------
 * int _label_to_code():
 *
 * --------------------------------------------------------------
 */
int _label_to_code( const char *label )
{
	char *cp = NULL;

	if ( NULL == label ) {
		return '\0';
	}

	/* get a pointer to the 1st occurrence of '&' in label */
	if ( NULL == (cp = strchr(label, '&')) ) {
		fprintf(
			stderr,
			"*** error: %s",
			"& indicator was not found in specified color-string\n"
			);
		return '\0';
	}

	/* return ascii-code of character next to '&' */
	if ( '\0' == *++cp ) {
		fprintf(
			stderr,
			"*** error: %s",
			"No valid character found after & indicator\n"
			);
		return '\0';
	}
	return *cp;
}

/* --------------------------------------------------------------
 * Color *new_colors():
 *
 * --------------------------------------------------------------
 */
Color *new_colors( void )
{
	int i=0;

	Color *colors = calloc( MAXCOLORS, sizeof(*colors) );
	if ( NULL == colors ) {
		return NULL;
	}

	for (i=0; i < MAXCOLORS; i++) {
		colors[i].label = _g_labels[i];
		colors[i].code  = _label_to_code( colors[i].label );
		CONOUT_CPYCLR( colors[i].fg, _g_concolors[i] );
	}

	return colors;
}

/* --------------------------------------------------------------
 * Color *colors_free():
 *
 * --------------------------------------------------------------
 */
Color *colors_free( Color *colors )
{
	if ( colors ) {
		free( colors );
	}
	return NULL;
}

/* --------------------------------------------------------------
 * int colors_get_code_at_idx():
 *
 * --------------------------------------------------------------
 */
int colors_get_code_at_idx( const Color *colors, enum ColorIdx idx )
{
	if ( NULL == colors || !_VALID_IDX(idx) ) {
		return '\0';
	}

	return colors[idx].code;
}

/* --------------------------------------------------------------
 * enum ColorIdx colors_get_random_index():
 *
 * --------------------------------------------------------------
 */
enum ColorIdx colors_get_random_index( const Color *colors )
{
	if ( NULL == colors ) {
		return IDX_INVALID;
	}

	return rand() % MAXCOLORS;
}

/* --------------------------------------------------------------
 * ConSingleColor *colors_get_fg_at_idx():
 *
 * --------------------------------------------------------------
 */
const ConSingleColor *colors_get_fg_at_idx( const Color *colors, enum ColorIdx idx )
{
	if ( NULL == colors || !_VALID_IDX(idx) ) {
		return NULL;
	}

	return &colors[idx].fg;
}

/* --------------------------------------------------------------
 * enum ColorIdx colors_code_to_idx():
 *
 * --------------------------------------------------------------
 */
enum ColorIdx colors_lookup_code( const Color *colors, int code )
{
	if ( NULL == colors ) {
		return IDX_INVALID;
	}

	for (enum ColorIdx i=0; i < MAXCOLORS; i++) {
		if (code == colors[i].code) {
			return i;
		}
	}
	return IDX_INVALID;
}

/* --------------------------------------------------------------
 * bool colors_print_label_at_idx():
 *
 * --------------------------------------------------------------
 */
bool colors_print_label_at_idx( const Color *colors, enum ColorIdx idx )
{
	const char *cp = NULL;

	if ( NULL == colors
	|| !_VALID_IDX(idx)
	|| NULL == colors[idx].label
	){
		return false;
	}

	if ( NULL == (cp = strchr(colors[idx].label,'&')) ) {
		fprintf(
			stderr,
			"*** error: %s",
			"NULL color-string or & indicator was not found\n"
			);
		return false;
	}

	for (cp=colors[idx].label; *cp; cp++)
	{
		if ( '&' == *cp ) {
			putchar( '(' );
			putchar( *++cp );
			putchar( ')' );
		}
		else {
			putchar( *cp );
		}
	}
	fflush( stdout );

	return true;
}

