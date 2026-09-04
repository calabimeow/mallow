#ifndef QTEE_H
#define QTEE_H

#include <stdlib.h>

#define QTEE_PIXEL(texture, x, y) (texture.pixels[(y) * texture.width + (x)])
#define QTEE_SWAP(type, a, b) {type t = a; a = b; b = t;}

#define QTEE_RGBA(r, g, b, a) ((((r) & 0xFF) | (((g) & 0xFF) << 8) | (((b) & 0xFF) << 16) | (((a) & 0xFF) << 24)))

#if __STDC_VERSION__ >= 199901L
    #include <stdint.h>
#else
    typedef unsigned char uint8_t;
    typedef unsigned int uint32_t;
#endif

typedef struct
{
    size_t width, height;
    uint32_t *pixels;
}qtee_texture;

typedef struct
{
    size_t width, height;
    char *glyphs;
}qtee_font;

#define QTEE_DEFAULT_FONT_HEIGHT 6
#define QTEE_DEFAULT_FONT_WIDTH 6

static char qtee_default_glyphs[128][QTEE_DEFAULT_FONT_HEIGHT][QTEE_DEFAULT_FONT_WIDTH] =
{
    ['a'] =
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
    },
    ['b'] =
    {
        {1, 0, 0, 0, 0},
        {1, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 1, 1, 0, 0},
    },
    ['c'] = 
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
    },
    ['d'] =
    {
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
    },
    ['e'] =
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
    },
    ['f'] =
    {
        {0, 0, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
    },
    ['g'] =
    {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
    },
    ['h'] =
    {
        {1, 0, 0, 0, 0},
        {1, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
    },
    ['i'] =
    {
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
    },
    ['j'] =
    {
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
    },
    ['k'] = 
    {
        {1, 0, 0, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 0, 0, 1, 0},
    },
    ['l'] = 
    {
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
    },
    ['m'] = 
    {
        {0, 0, 0, 0, 0},
        {0, 1, 0, 1, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1},
    },
    ['n'] = 
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
    },
    ['o'] = 
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
    },
    ['p'] = 
    {
        {1, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 1, 1, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
    },
    ['q'] = 
    {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0},
    },
    ['r'] = 
    {
        {0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 0, 1},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
    },
    ['s'] = 
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 1, 0, 0},
    },
    ['t'] = 
    {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 0, 0},
    },
    ['u'] = 
    {
        {0, 0, 0, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
    },
    ['v'] = 
    {
        {0, 0, 0, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
    },
    ['w'] = 
    {
        {0, 0, 0, 0, 0},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1},
        {0, 1, 1, 1, 1},
    },
    ['x'] = 
    {
        {0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 0, 1, 0, 0},
    },
    ['y'] = 
    {
        {0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
    },
    ['z'] = 
    {
        {0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
    },
    ['A'] = 
    {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 1, 1, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
    },
    ['B'] = 
    {
        {1, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 1, 1, 0, 0},
    },
    ['C'] = 
    {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
    },
    ['D'] = 
    {
        {1, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 1, 1, 0, 0},
    },
    ['E'] = 
    {
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
    },
    ['F'] = 
    {
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
    },
    ['G'] = 
    {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
    },
    ['H'] = 
    {
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 1, 1, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
    },
    ['I'] = 
    {
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
    },
    ['J'] = 
    {
        {0, 0, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
    },
    ['K'] = 
    {
        {1, 0, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 0, 0, 1, 0},
    },
    ['L'] = 
    {
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
    },
    ['M'] = 
    {
        {1, 0, 0, 0, 1},
        {1, 1, 0, 1, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
    },
    ['N'] = 
    {
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 0, 1, 1},
        {1, 0, 0, 0, 1},
    },
    ['O'] = 
    {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
    },
    ['P'] = 
    {
        {1, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 1, 1, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
    },
    ['Q'] = 
    {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 1, 1, 0},
        {0, 1, 1, 0, 1},
    },
    ['R'] = 
    {
        {1, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 0, 0, 1, 0},
    },
    ['S'] = 
    {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 1, 0, 0},
    },
    ['T'] = 
    {
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
    },
    ['U'] = 
    {
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
    },
    ['V'] = 
    {
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
    },
    ['W'] = 
    {
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1},
        {0, 1, 1, 1, 0},
    },
    ['X'] = 
    {
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1},
    },
    ['Y'] = 
    {
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
    },
    ['Z'] = 
    {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
    },
    ['0'] = 
    {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
    },
    ['1'] = 
    {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
    },
    ['2'] = 
    {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
    },
    ['3'] = 
    {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
    },
    ['4'] = 
    {
        {0, 0, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0},
    },
    ['5'] = 
    {
        {1, 1, 1, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
    },
    ['6'] = 
    {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
    },
    ['7'] = 
    {
        {1, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
    },
    ['8'] = 
    {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},

    },
    ['9'] = 
    {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
    },

    [','] = 
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
    },

    ['.'] = 
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
    },
    ['-'] = 
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static qtee_font qtee_default_font =
{
    .width = QTEE_DEFAULT_FONT_WIDTH,
    .height = QTEE_DEFAULT_FONT_HEIGHT,
    .glyphs = &qtee_default_glyphs[0][0][0]
};

qtee_texture qtee_create_texture(uint32_t *pixels, size_t width, size_t height);
qtee_texture qtee_load_texture(uint8_t *data, size_t width, size_t height);
void qtee_fill_texture(qtee_texture texture, uint32_t color);
void qtee_draw_rect(qtee_texture texture, int x, int y, 
        size_t width, size_t height, uint32_t color);
void qtee_draw_circle(qtee_texture texture, int x, int y, size_t r, uint32_t color);
void qtee_draw_triangle(qtee_texture texture, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color);
void qtee_draw_line(qtee_texture texture, int x1, int y1, int x2, int y2, uint32_t color);
void qtee_draw_subtexture(qtee_texture main, qtee_texture sub, int x, int y, size_t w, size_t h);
void qtee_draw_text(qtee_texture texture, char *text, int x, int y, size_t size, qtee_font font, uint32_t color);

#ifdef QTEE_IMPLEMENTATION

qtee_texture qtee_create_texture(uint32_t *pixels, size_t width, size_t height)
{
    qtee_texture texture;
    texture.pixels = pixels;
    texture.width = width;
    texture.height = height;
    return texture;
}

qtee_texture qtee_load_texture(uint8_t *data, size_t width, size_t height)
{
    int i;
    uint32_t *pixels;

    pixels = malloc(width * height * sizeof(uint32_t));
    
    for (i = 0; (size_t)i < width * height; i++)
    {
        uint32_t r = data[i * 4];
        uint32_t g = data[i * 4 + 1];
        uint32_t b = data[i * 4 + 2];
        uint32_t a = data[i * 4 + 3];

        pixels[i] = QTEE_RGBA(b, g, r, a);
    }

    return qtee_create_texture(pixels, width, height);
}

void qtee_fill_texture(qtee_texture texture, uint32_t color)
{
    size_t x, y;

    for (y = 0; (size_t)y < texture.height; y++)
    {
        for (x = 0; (size_t)x < texture.width; x++)
        {
            QTEE_PIXEL(texture, x, y) = color;
        }
    }
}

void qtee_draw_rect(qtee_texture texture, int x, int y,
    size_t width, size_t height, uint32_t color)
{
    size_t dx, dy;
    int px, py;

    for (dy = 0; dy < height; dy++)
    {
        py = y + dy;
        if (py >= 0 && (size_t)py < texture.height)
        {
            for (dx = 0; (size_t)dx < width; dx++)
            {
                px = x + dx;
                if (px >= 0 && (size_t)px < texture.width)
                    QTEE_PIXEL(texture, px, py) = color;
            }
        }
    }
}

void qtee_draw_circle(qtee_texture texture, int x, int y, size_t r, uint32_t color)
{
    size_t cx, cy;
    int dx, dy;
    size_t dist;

    for (cy = 0; cy < texture.height; cy++)
    {
        for (cx = 0; cx < texture.width; cx++)
        {
            dx = cx - x;
            dy = cy - y;
            dist = dx * dx + dy * dy;

            if (dist < r * r)
                QTEE_PIXEL(texture, cx, cy) = color;
        }
    }
}

static void qtee_normalize_triangle(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3)
{
    if (*y1 > *y2)
    {
        QTEE_SWAP(int, *x1, *x2);
        QTEE_SWAP(int, *y1, *y2);
    }

    if (*y2 > *y3)
    {
        QTEE_SWAP(int, *x2, *x3);
        QTEE_SWAP(int, *y2, *y3);
    }

    if (*y1 > *y2)
    {
        QTEE_SWAP(int, *x1, *x2);
        QTEE_SWAP(int, *y1, *y2);
    }
}

void qtee_draw_triangle(qtee_texture texture, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color)
{
    int dx12, dy12;
    int dx13, dy13;
    int dx32, dy32;
    int dx31, dy31;
    int x, y;
    int s1, s2;

    qtee_normalize_triangle(&x1, &y1, &x2, &y2, &x3, &y3);

    dx12 = x2 - x1;
    dy12 = y2 - y1;
    dx13 = x3 - x1;
    dy13 = y3 - y1;
    
    for (y = y1; y <= y2; y++)
    {
        if (y >= 0 && (size_t)y < texture.height)
        {
            s1 = dy12 != 0 ? (y - y1) * dx12 / dy12 + x1 : x1;
            s2 = dy13 != 0 ? (y - y1) * dx13 / dy13 + x1 : x1;

            if (s1 > s2) QTEE_SWAP(int, s1, s2);
            
            for (x = s1; x <= s2; x++)
            {
                if (x >= 0 && (size_t)x < texture.width) QTEE_PIXEL(texture, x, y) = color;
            }
        }
    }

    dx32 = x2 - x3;
    dy32 = y2 - y3;
    dx31 = x1 - x3;
    dy31 = y1 - y3;

    for (y = y2; y <= y3; y++)
    {
        if (y >= 0 && (size_t)y < texture.height)
        {
            s1 = dy32 != 0 ? (y - y3) * dx32 / dy32 + x3 : x3;
            s2 = dy31 != 0 ? (y - y3) * dx31 / dy31 + x3 : x3;

            if (s1 > s2) QTEE_SWAP(int, s1, s2);
            
            for (x = s1; x <= s2; x++)
            {
                if (x >= 0 &&(size_t)x < texture.width) QTEE_PIXEL(texture, x, y) = color;
            }
        }
    }

}

void qtee_draw_line(qtee_texture texture, int x1, int y1, int x2, int y2, uint32_t color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int sy1, sy2;
    int x, y;
    int c;

    if (dx != 0)
    {
        c = y1 - dy * x1 / dx;

        if (x1 > x2) QTEE_SWAP(int, x1, x2);

        for (x = x1; x < x2; x++)
        {
            if (x >= 0 && (size_t)x < texture.width)
            {
                sy1 = dy * x / dx + c;
                sy2 = dy * (x + 1) / dx + c;
                if (sy1 > sy2) QTEE_SWAP(int, sy1, sy2);
                
                for (y = sy1; y <= sy2; y++)
                {
                    if (y >= 0 && (size_t)y < texture.height) QTEE_PIXEL(texture, x, y) = color;
                }
            }
        }
    }

    else
    {
        x = x1;
        if (x >= 0 && (size_t)x < texture.width)
        {
            if (y1 > y2) QTEE_SWAP(int, y1, y2);
            
            for (y = y1; y <= y2; y++)
            {
                if (y >= 0 && (size_t)y < texture.height) QTEE_PIXEL(texture, x, y) = color;
            }
        }
    }
}

void qtee_draw_subtexture(qtee_texture main, qtee_texture sub, int x, int y, size_t w, size_t h)
{
    size_t dx, dy;
    size_t sx, sy;

    for (dy = 0; dy < h; dy++)
    {
        int py = y + dy;

        if (py < 0 || (size_t)py >= main.height)
            continue;

        for (dx = 0; dx < w; dx++)
        {
            int px = x + dx;

            if (px < 0 || (size_t)px >= main.width)
                continue;

            sx = dx * sub.width / w;
            sy = dy * sub.height / h;

            QTEE_PIXEL(main, px, py) = QTEE_PIXEL(sub, sx, sy);
        }
    }
}

void qtee_draw_text(qtee_texture texture, char *text, int x, int y, size_t size, qtee_font font, uint32_t color)
{
    int gx, gy;
    size_t i;
    for (i = 0; *text; i++, text++)
    {
        int dx, dy;

        gx = x + i * font.width * size;
        gy = y;

        char *glyph = &font.glyphs[(*text) * font.width * font.height];

        for (dy = 0; (size_t)dy < font.height; dy++)
        {
            for (dx = 0; (size_t)dx < font.width; dx++)
            {
                int px = gx + dx * size;
                int py = gy + dy * size;

                if (px >= 0 && (size_t)px < texture.width && py >= 0 && (size_t)py < texture.height)
                {
                    if (glyph[dy * font.width + dx])
                        qtee_draw_rect(texture, px, py, size, size, color);
                }
            }
        }
    }
}

#endif /* QTEE_IMPLEMENTATION */
#endif /* QTEE_H */
