#ifndef INFO_H
#define INFO_H

#define APP_NAME        "Mastermind"
#define APP_VERSION     "0.1.0"
#define AUTHOR          "Ilias Stamatis"
#define AUTHOR_MAIL     "stamatis.iliass@gmail.com"

#define START_MENU                               \
	"           %s\n"                        \
	"    ------------------------\n\n"       \
	"      S  Start the game\n\n"            \
	"      C  Show credits\n\n"              \
	"      I  Info about playing\n\n"        \
	"      Q  Quit\n\n"                      \

#define CREDITS                                                                  \
	"Name: %s\n"                                                             \
	"Version: %s\n\n"                                                        \
	"Copyright (C) 2013 %s <%s>\n\n"                                         \
	"%s is free software: you can redistribute it and/or modify\n"           \
	"it under the terms of the GNU General Public License as published by\n" \
	"the Free Software Foundation, either version 3 of the License, or\n"    \
	"(at your option) any later version.\n\n"                                \
	"Written by %s.\n\n"                                                     \

#define INFO_ABOUT_PLAYING                                                                     \
	"Info about playing\n"                                                                 \
	"-------------------\n"                                                                \
	"At the beginning of the game computer chooses a secret code consisting of\n"          \
	"4 unique colors in a random row. Your goal is to find this code and to do so\n"       \
	"you have a specified number of tries. For each try computer gives you some\n"         \
	"information. For each color that exists in your code in exact the same position\n"    \
	"as in computer's secret code a red mark will be sown and for each color in your\n"    \
	"code that appears in secret code too but not in the correct position, a yellow\n"     \
	"mark will be sown. If you find the secret code before the game is over, you win.\n\n" \
	"Only three commands are understood by the program:\n"                                 \
	" - n color, Put color which should be a known color (a list of all colors\n"          \
	"            will be displayed) in column n (an integer from 1 to 4).\n"               \
	"            If null is given instead of a color the cell will become empty.\n"        \
	"            Examples: 1 red, 3 yellow, 1 null\n"                                      \
	" - check,   Check your code and set marks.\n"                                         \
	" - exit,    Quit program.\n\n"                                                        \
	" Have fun!\n"                                                                         \

#endif
