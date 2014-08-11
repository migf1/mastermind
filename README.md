Mastermind
==========

This is a slightly twisted, cross-platform, CLI implementation of the
Mastermind game, for Windows, Unix, Linux and MacOSX. The twist is that,
contrary to the rules of the original board-game, this one does not allow
guesses to contain same colors.

The source-code is written in C99, and it was originally forked from v0.1.0
at **[Ilias Stamatis's](https://github.com/Ilias95/mastermind)** repository.

Some **screen-shots** are available in the `ss/` directory (screen-shots from
Windows are taken with the `Lucida Console` font loaded in the console).

**Changes** added by this fork affect the user interface and they include:

- More tabular listing of colors, below the board.
- Guesses are typed in one go, using single letter color-indicators.
- `-r` may be appended to guesses, in order to review them on the board.
Giving the `check` command, causes the last reviewed guess to be submitted.
- The commands of the starting menu are also available in the board screen.
- Already played guesses are displayed both as pegs and as color-indicators.

**Source-wise**, a big part of the code has been rewritten, mostly due to the
introduction of the `Color` "class" (files: colors.c & color.h).

Gameplay
--------

The game is meant to be played in a console/terminal window with a **black**
background color. Otherwise, some in-game colors may blend with the background
thus becoming hard to distinguish. They may be even become invisible.

The game starts with the computer setting up a secret-code of four random,
unique colors. Your task is to find the secret-code in a predefined number
of tries. On each try, you enter your guess and the computer responds with
hints, next to your guess.

**Red hints** for exact-position-matches are shown first, followed by **Yellow**
**hints** for different-position-matches. **No hints** are shown for non-matched
colors. You win if you guess the secret-code before exhausting the board.

All available colors are listed below the game-board. Specify a **guess** by
typing together the indicators of the desired colors (the ones surrounded
by parentheses). For example, if your guess is *white-black-red-blue*, type
in: `wbrl` and hit the `ENTER` key on your keyboard.

Guesses can be **reviewed** before submitted. Append a `-r` at the end of
the guess to review it on the board, without having it checked for hints
(or example: `wbrl-r`). You may review many guesses this way. To submit
the currently reviewed guess, issue the `check` command.

Other Commands: `q` or `quit` | `h` or `help` | `c` or `credits`


Pre-compiled Binaries
---------------------

The game comes with a pre-compiled Windows 32-bit binary file, in the
*bin/* folder. It is called *mastermind_win_x86.exe*. You may freely
rename it and/or move it to any other folder.

On other platforms, you can compile the sources. See the next section.


Compiling the Sources
---------------------

It's really easy to compile the sources yourselves, assuming that a recent
gcc tool-chain is properly installed on your system (it is by default on
most Unix, Linux and older MacOSX distributions).

Recent versions of MacOSX do not include the gcc tool-chain by default,
so you may need to install it manually. See the following thread:
http://stackoverflow.com/questions/9353444/how-to-use-install-gcc-on-mac-os-x-10-8-xcode-4-4)

For Windows, you may install the [MinGW](http://www.mingw.org/) tool-chain
or any of its may variants available on the Internet (such as MinGW-64,
TDM-GCC, etc).

Note that, no matter the platform, you will need a relatively recent
version of the gcc tool-chain, one that supports the C99 features.

**Using the included Makefile**

Please note that in order to use the included *"Makefile* you need the
gcc tool-chain (unless of course you modify the *Makefile* for any other
tool-chain).

From the command-line, navigate to the *src/* directory and assuming
you are using gcc as a compiler, type: `make`

The binary file, called *mastermind*, will be generated inside the
*src/* directory. You may freely rename and/or move it to any other
directory.

You can remove the binary file and the object files from the *src/*
directory by typing: `make clean`

**Without using the included Makefile**

From the command-line, navigate to the *src/* directory and assuming
you are using gcc as your compiler, type:

`gcc -std=c99 -s -O2 *.c -o mastermind`

The binary file, called *mastermind*, will be generated inside the
*src/* directory. You may freely rename and/or move it to any other
directory.

**Using any IDE/C99-Compiler combination**

In your favorite IDE, create a console/terminal project and add to
it all the *.c* files found in the *src/* directory. Then enable
*C99 support* on the compiler. Finally, *Build & Run* the project.


License
-------

Mastermind is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License,
or (at your option) any later version.


Disclaimer
----------

Use the program at your own risk! I take no responsibility for
any damage it may cause to your system.
