#ifndef COLORS_H
#define COLORS_H

#include "con_color.h"

typedef struct _Color Color;

enum ColorIdx {
	IDX_INVALID = -2,
	IDX_NOCOLOR = -1,
	IDX_WHITE   = 0,
	IDX_BLACK,
	IDX_RED,
	IDX_GREEN,
	IDX_YELLOW,
	IDX_BLUE,
	IDX_MAGENTA,
	IDX_CYAN,
	MAXCOLORS      /* total count of supported colors */
};

extern Color    *new_colors( void );
extern Color    *colors_free( Color *colors );
extern int      colors_get_code_at_idx(
                        const Color   *colors,
                        enum ColorIdx idx
                        );
extern enum ColorIdx colors_get_random_index(
                        const Color *colors
                        );
extern const ConSingleColor *colors_get_fg_at_idx(
                        const Color   *colors,
                        enum ColorIdx idx
                        );
extern bool     colors_print_label_at_idx(
                        const Color   *colors,
                        enum ColorIdx idx
                        );
extern enum ColorIdx colors_lookup_code( const Color *colors, int code );

#endif
