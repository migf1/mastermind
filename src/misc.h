#ifndef MISC_H
#define MISC_H

#include <stdbool.h>

#if defined(__linux__) || defined(__unix__) || defined(__unix)
	#define SYSTEM_CLEAR "clear"
#elif defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__) \
|| defined(__TOS_WIN__)
	#define SYSTEM_CLEAR "cls"
#else
	/* fill this in with your platform-specific behaviour */
	#define SYSTEM_CLEAR ""
#endif

#define MAX_INPUT     255  /* max accepted length of stdin */

void  clear_screen( void );
void  press_enter( void );
char  *s_tolower(char *s);
int   s_tokenize(char *s, char *tokens[], int ntoks, const char *delims);
char  *s_trim( char *s );
bool  prompt_for_string( const char *prompt, char *str, const size_t maxsz );
int   prompt_for_char( const char *prompt );

#endif

