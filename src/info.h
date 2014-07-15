#ifndef INFO_H
#define INFO_H

#define APP_NAME        "Mastermind"
#define APP_VERSION     "0.1.0"
#define AUTHOR          "Ilias Stamatis"
#define AUTHOR_MAIL     "stamatis.iliass@gmail.com"

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
  "  Name: %s\n"                                                           \
  "  Version: %s\n\n"                                                      \
  "  Copyright (C) 2013 %s <%s>\n\n"                                       \
  "  %s is free software: you can redistribute it and/or modify\n"         \
  "  it under the terms of the GNU General Public License as published\n"  \
  "  by the Free Software Foundation, either version 3 of the License,\n"  \
  "  or (at your option) any later version.\n"                             \
  "\n"                                                                     \
  "  Written  by %s.\n"                                                    \
  "  Modified by Harry Karayannis.\n"                                      \
  "\n"

#define INFO_ABOUT_PLAYING                                                         \
  "   Q U I C K  G U I D E\n"                                                      \
  "\n"                                                                             \
  "   The game starts with the computer setting up a secret-code of four random,\n"\
  "   unique colors. Your task is to find the secret-code in a predefined number\n"\
  "   of tries. On each try, you enter your guess and the computer responds with\n"\
  "   hints, next to your guess.\n"                                                \
  "\n"                                                                             \
  "   RED hints for exact-position-matches are shown first, followed by YELLOW\n"  \
  "   hints for different-position-matches. No hints are shown for non-matched\n"  \
  "   colors. You win if you guess the secret-code before exhausting the board.\n" \
  "\n"                                                                             \
  "   All available colors are listed below the game-board. Specify a guess by\n"  \
  "   typing together the indicators of the desired colors (the ones surrounded\n" \
  "   by parentheses). For example, if your guess is white-black-red-blue, type\n" \
  "   in: \"wbrl\" and hit the ENTER key on your keyboard.\n"                      \
  "\n"                                                                             \
  "   Guesses are NOT checked for hints until you give the \"check\" command. It\n"\
  "   is useful for reviewing a guess before submitting it. To skip this extra\n"  \
  "   step, append \"-c\" at the end of the guess. For example: \"wbrl-c\"\n"      \
  "\n"                                                                             \
  "   Other Commands: \"q\" or \"quit\" | \"h\" or \"help\" | \"c\" or \"credits\"\n"\
  "\n"                                                                             \
  "   --- ALL COMMANDS & GUESSES MUST BE ISSUED WITHOUT QUOTES AROUND THEM ---"
#endif
