#ifndef MISC_H
#define MISC_H

#include <string.h> /* strtok() */
#include <ctype.h>  /* tolower() */

#if defined(__linux__) || defined(__unix__) || defined(__unix)      \
|| defined(__CYGWIN__) || defined(__GNU__) || defined(__MINGW32__)  \
|| defined(__MINGW64__)
	#define SYSTEM_CLEAR "clear"
#elif defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)   \
|| defined(__TOS_WIN__)
	#define SYSTEM_CLEAR "cls"
#else
	/* fill this in with your platform-specific behaviour */
	#define SYSTEM_CLEAR ""
#endif


char *s_tolower(char *s);
int s_tokenize(char *s, char *tokens[], int ntoks, const char *delims);

#endif

