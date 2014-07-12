/*
 * This is a variant of migf1's <mig_f1@hotmail.com> CON_COLOR_H.
 * I modified this header to fit my needs. Actually, I kept only the bare
 * essentials for my program. I don't hold any copyright.
 *
 * If you're looking for the original file, check:
 *    http://x-karagiannis.gr/prg/c-prog/c-misc/con_color-h/
 */

#ifndef CON_COLOR_H
#define CON_COLOR_H

#include <string.h>

#if defined(__linux__) || defined(__unix__) || defined(__unix)
	#define CON_COLOR_ANSI
#elif defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__) \
|| defined(__TOS_WIN__)
	#define CON_COLOR_WIN32
#endif

#if defined(CON_COLOR_ANSI)

	/* ANSI Foreground Colors */
	#define FG_NOCHANGE     "\033[0;39m"

	#define FG_WHITE        "\033[1;37m"
	#define FG_DARKGRAY     "\033[1;30m"
	#define FG_DARKRED      "\033[0;31m"
	#define FG_DARKGREEN    "\033[0;32m"
	#define FG_DARKYELLOW   "\033[0;33m"
	#define FG_DARKBLUE     "\033[0;34m"
	#define FG_DARKMAGENTA  "\033[0;35m"
	#define FG_DARKCYAN     "\033[0;36m"

	#define CONOUT_INIT()
	#define CONOUT_RESTORE()  printf("\033[0m")
	#define CONOUT_RESET()    printf("\033[0m")

	#define CONOUT_PRINTF(fg, ...)                   \
		do {                                     \
			if (strcmp((fg), FG_NOCHANGE))   \
				printf((fg));            \
			printf( __VA_ARGS__ );           \
			if (strcmp((fg), FG_NOCHANGE))   \
				CONOUT_RESET();          \
		} while(0)

#elif defined(CON_COLOR_WIN32)

	#include <windows.h>

	HANDLE                       hStdout;
	CONSOLE_SCREEN_BUFFER_INFO   csbiCurrent, csbiOriginal, csbiTemp;

	/* Win32 Foreground Colors */
	#define FG_NOCHANGE     0xFF

	#define FG_WHITE        (FOREGROUND_RED|FOREGROUND_GREEN|     \
	                         FOREGROUND_BLUE|FOREGROUND_INTENSITY)
	#define FG_DARKGRAY     (FOREGROUND_INTENSITY)
	#define FG_DARKRED      (FOREGROUND_RED)
	#define FG_DARKGREEN    (FOREGROUND_GREEN)
	#define FG_DARKYELLOW   (FOREGROUND_RED|FOREGROUND_GREEN)
	#define FG_DARKBLUE     (FOREGROUND_BLUE)
	#define FG_DARKMAGENTA  (FOREGROUND_RED|FOREGROUND_BLUE)
	#define FG_DARKCYAN     (FOREGROUND_GREEN|FOREGROUND_BLUE)


	#define CONOUT_INIT()                                               \
		do {                                                        \
			hStdout = GetStdHandle(STD_OUTPUT_HANDLE);          \
			if (hStdout != INVALID_HANDLE_VALUE)                \
			{                                                   \
				GetConsoleScreenBufferInfo(hStdout,         \
				                           &csbiCurrent);   \
				memcpy(&csbiOriginal, &csbiCurrent,         \
				       sizeof(CONSOLE_SCREEN_BUFFER_INFO)); \
			}                                                   \
			else                                                \
				printf("*** CONOUT_INIT failed: %d!\n",     \
				       GetLastError());                     \
		} while(0)

	#define CONOUT_RESTORE()                                                \
		SetConsoleTextAttribute(hStdout, csbiOriginal.wAttributes)

	#define CONOUT_RESET()                                                  \
		do {                                                            \
			SetConsoleTextAttribute(hStdout, csbiTemp.wAttributes); \
			memcpy(&csbiCurrent, &csbiTemp,                         \
			       sizeof(CONSOLE_SCREEN_BUFFER_INFO));             \
		}while(0)

	#define CONOUT_PRINTF(fg, ...)                              \
		do {                                                \
			if ((WORD)(fg) != (WORD)FG_NOCHANGE)        \
				CONOUT_SET_COLOR((fg));             \
			printf( __VA_ARGS__);                       \
			if ( (WORD)(fg) != (WORD)FG_NOCHANGE)       \
				CONOUT_RESET();                     \
			fflush(stdout);                             \
		} while(0)

	#define CONOUT_SET_COLOR(fg)                                \
		do {                                                \
			memcpy(&csbiTemp, &csbiCurrent,             \
			       sizeof(CONSOLE_SCREEN_BUFFER_INFO)); \
			csbiCurrent.wAttributes = (fg);             \
			SetConsoleTextAttribute(hStdout, (fg));     \
		} while(0)
#endif

#endif
