#ifndef INFO_H
#define INFO_H

/* Modified game */
#define APP_NAME        "MASTERMIND"
#define APP_VERSION     "0.2.1"
#define AUTHOR          "migf1"
#define AUTHOR_MAIL     "mig_f1@hotmail.com"
#define GITHUB          "https://github.com/migf1/mastermind/tree/migf1"

/* Original game */
#define ORG_APP_VERSION "0.1.0"
#define ORG_AUTHOR      "Ilias Stamatis"
#define ORG_AUTHOR_MAIL "stamatis.iliass@gmail.com"
#define ORG_GITHUB      "https://github.com/Ilias95/mastermind"

#define START_MENU                                   \
	"\n"                                         \
	"               %s\n"                        \
	"        ------------------------\n\n"       \
	"          S  Start the game\n\n"            \
	"          C  Show credits\n\n"              \
	"          H  Help about playing\n\n"        \
	"          Q  Quit\n\n"                      \
	"        ------------------------\n"         \
	"          "

#define CREDITS                                                            \
  "\n"                                                                     \
  "  %s\n"                                                                 \
  "\n"                                                                     \
  "  [Modified]\n"                                                         \
  "  Version:\t%s\n"                                                       \
  "  Author :\t%s <%s>\n"                                                  \
  "  Github :\t%s\n"                                                       \
  "  copyright (c) 2014 %s\n"                                              \
  "\n"                                                                     \
  "  [Original]\n"                                                         \
  "  Version:\t%s\n"                                                       \
  "  Author :\t%s <%s>\n"                                                  \
  "  Github :\t%s\n"                                                       \
  "  copyright (c) 2013 %s\n"                                              \
  "\n"                                                                     \
  "  License:\n"                                                           \
  "\n"                                                                     \
  "  %s is free software: you can redistribute it and/or modify\n"         \
  "  it under the terms of the GNU General Public License as published\n"  \
  "  by the Free Software Foundation, either version 3 of the License,\n"  \
  "  or (at your option) any later version.\n"                             \
  "\n"

#define INFO_ABOUT_PLAYING                                                 \
  "   Q U I C K  G U I D E\n"                                              \
  "\n"                                                                     \
  "   The game starts with the computer setting up a secret-code of four random,\n"\
  "   unique colors. Your task is to find the secret-code in a predefined number\n"\
  "   of tries. On each try, you enter your guess and the computer responds with\n"\
  "   hints, next to your guess.\n"                                        \
  "\n"                                                                     \
  "   RED hints for exact-position-matches are shown first, followed by YELLOW\n" \
  "   hints for different-position-matches. No hints are shown for non-matched\n" \
  "   colors. You win if you guess the secret-code before exhausting the board.\n"\
  "\n"                                                                     \
  "   All available colors are listed below the game-board. Specify a guess by\n" \
  "   typing together the indicators of the desired colors (the ones surrounded\n"\
  "   by parentheses). For example, if your guess is white-black-red-blue, type\n"\
  "   in: \"wbrl\" and hit the ENTER key on your keyboard.\n"              \
  "\n"                                                                     \
  "   Guesses can be reviewed before submitted. Append a \"-r\" at the end of the\n"\
  "   guess to review it on the board. To submit it, issue the \"check\" command.\n"\
  "   For example: \"wbrl-r\" and then \"check\".\n"                       \
  "\n"                                                                     \
  "   Other Commands: \"q\" or \"quit\" | \"h\" or \"help\" | \"c\" or \"credits\"\n"\
  "\n"                                                                     \
  "   --- ALL COMMANDS & GUESSES MUST BE ISSUED WITHOUT QUOTES AROUND THEM ---"
#endif
