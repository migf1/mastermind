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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "misc.h"

/* --------------------------------------------------------------
 * void clear_screen():
 *
 * Clear the terminal screen.
 * --------------------------------------------------------------
 */
void clear_screen( void )
{
	system( SYSTEM_CLEAR );
}

/* --------------------------------------------------------------
 * void press_enter():
 *
 * Prompt user to press the ENTER key, and wait until he does.
 * --------------------------------------------------------------
 */
void press_enter( void )
{
	int c = '\0';

	printf( "%s", "Press Enter..." );
	fflush( stdout );
	while ( '\n' != (c=getchar()) && EOF != c ) {
		;  /* void */
	}
}

/*
 * s_tolower:
 *    Convert all characters of a c-string to lowercase.
 *    Return the converted string on success, else NULL.
 */
char *s_tolower(char *s)
{
	char *cp;

	/* sanity checks */
	if ( NULL == s )
		return NULL;
	if (!*s)
		return s;

	for (cp=s; (*cp=tolower(*cp)); cp++)
		; /* void */

	return s;
}

/*
 * s_tokenize:
 *    Tokenize a c-string, into variable size tokens.
 *    Return the number of tokens which s was broken to on success,
 *    else 0.
 */
int s_tokenize(char *s,        /* mutable string */
               char *tokens[], /* array of strings, to be filled by the
                                 function with NUL-terminated string tokens. */
               int ntoks,      /* maximum number of desired tokens.  */
               const char *delims /* string consisting of the desired
                                     delimiter characters */
)
{
	register int i;

	/* sanity checks */
	if (s  == NULL || tokens == NULL || delims == NULL
	|| !*s || !*delims || ntoks < 1)
		return 0;

	tokens[0] = strtok(s, delims);
	if (tokens[0] == NULL)
		return 0;

	for (i = 1; i < ntoks && (tokens[i] = strtok(NULL, delims)) != NULL; i++)
		; /* void */

	return i;
}

/* --------------------------------------------------------------
 * char *s_trim():
 *
 * Trim leading & trailing blanks from a c-string. Return a pointer
 * to the modified c-string s (in case of error, it will be unchanged).
 *
 * NOTES: isspace() is used for determining blank characters.
 * --------------------------------------------------------------
 */
char *s_trim( char *s )
{
	char *cp1 = NULL;      /* for parsing the whole s */
	char *cp2 = NULL;      /* for shifting & padding  */

	/* sanity checks */
	if ( NULL == s )  {
		return s;
	}

	/* skip leading blanks, via cp1 */
	for (cp1=s; isspace( (int)(*cp1)); cp1++) {
		; /* void */
	}

	/* shift to the left remaining chars, via cp2  */
	for (cp2=s; *cp1; cp1++, cp2++) {
		*cp2 = *cp1;
	}
	*cp2-- = '\0';  /* mark end of left trimmed s */

	/* skip trailing blanks via cp2 */
	while ( cp2 > s && isspace((int)(*cp2)) ) {
		cp2--;
	}
	*++cp2 = '\0';  /* mark end of trimmed s */

	return s;
}

/* --------------------------------------------------------------
 * bool prompt_for_string():
 *
 * Prompt for a c-string. Return true on success, false otherwise.
 * The input c-string (str) must be already allocated and capable
 * of holding at least maxsz bytes, including the NUL terminating
 * one.
 * --------------------------------------------------------------
 */
bool prompt_for_string( const char *prompt, char *str, const size_t maxsz )
{
	size_t i = 0;
	int c = '\0';

	if ( !str || maxsz < 1 ) {
		return false;
	}

	/* display the prompt, if any */
	if ( NULL != prompt ) {
		printf( "%s", prompt );
		fflush( stdout );
	}

	/* read the c-string */
	memset( str, '\0', maxsz );    /* start fresh */
	for (i=0; i < maxsz-1 && '\n' != (c=getchar()) && EOF != c; i++) {
		str[i] = c;
	}

	/* if necessary, flush stdin */
	if ( str[i] && '\n' != str[i] && EOF != str[i]  ) {
		while ( '\n' != (c=getchar()) && EOF != c ) {
			;  /* void */
		}
	}

	/* NUL-terminate str */
	str[i] = '\0';

	return true;
}

/* --------------------------------------------------------------
 * int prompt_for_char():
 *
 * Prompt for character input. Return the 1st non-blank character
 * available in stdin, or '\0' on error.
 * --------------------------------------------------------------
 */
int prompt_for_char( const char *prompt )
{
	char input[MAX_INPUT+1] = {'\0'};
	int  ret = '\0';

	if ( !prompt_for_string( prompt, input, sizeof(input) )
	|| 1 != sscanf( input, " %c", (char *)&ret )
	){
		return '\0';
	}
	return ret;
}

