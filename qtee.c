#include "qtee.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

const char qtee_default_glyphs[128][QTEE_DEFAULT_FONT_WIDTH][QTEE_DEFAULT_FONT_HEIGHT] = 
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
    ['r'] = {

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

    ['A'] = {0},
    ['B'] = {0},
    ['C'] = {0},
    ['D'] = {0},
    ['E'] = {0},
    ['F'] = {0},
    ['G'] = {0},
    ['H'] = {0},
    ['I'] = {0},
    ['J'] = {0},
    ['K'] = {0},
    ['L'] = {0},
    ['M'] = {0},
    ['N'] = {0},
    ['O'] = {0},
    ['P'] = {0},
    ['Q'] = {0},
    ['R'] = {0},
    ['S'] = {0},
    ['T'] = {0},
    ['U'] = {0},
    ['V'] = {0},
    ['W'] = {0},
    ['X'] = {0},
    ['Y'] = {0},
    ['Z'] = {0},

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

qtee_font qtee_default_font =
{
    .width = QTEE_DEFAULT_FONT_WIDTH,
    .height = QTEE_DEFAULT_FONT_HEIGHT,
    .glyphs = &qtee_default_glyphs[0][0][0]
};

qtee_canvas qtee_create_canvas(uint32_t *pixels, size_t width, size_t height)
{
    qtee_canvas c = 
    {
        .pixels = pixels,
        .width = width,
        .height = height,
    };

    return c;
}

void qtee_fill_canvas(qtee_canvas canvas, uint32_t color)
{
    for (size_t y = 0; y < canvas.height; y++)
    {
        for (size_t x = 0; x < canvas.width; x++)
        {
           QTEE_PIXEL(canvas, x, y) = color;
        }
    }
}

void qtee_rect(qtee_canvas canvas, int x, int y, size_t width, size_t height, uint32_t color)
{
    for (size_t dy = 0; dy < height; dy++)
    {
        int py = y + dy;

        if (py >= 0 && py < canvas.height)
        {
            for (size_t dx = 0; dx < width; dx++)
            {
                int px = x + dx;
                
                if (px >= 0 && px < canvas.width)
                    QTEE_PIXEL(canvas, px, py) = color;
            }
        }
    }
}

void qtee_circle(qtee_canvas canvas, int cx, int cy, size_t r, uint32_t color)
{
    for (size_t y = 0; y < canvas.height; y++)
    {
        for (size_t x = 0; x < canvas.width; x++)
        {
            int dx = x - cx;
            int dy = y - cy;
            size_t dist = dx * dx + dy * dy;

            if (dist < r * r) QTEE_PIXEL(canvas, x, y) = color;
        }
    }
}

void qtee_circle_outline(qtee_canvas canvas, int cx, int cy, size_t r, size_t thick,
        uint32_t color)
{
    for (size_t y = 0; y < canvas.height; y++)
    {
        for (size_t x = 0; x < canvas.width; x++)
        {
            int dx = x - cx;
            int dy = y - cy;
            size_t dist = dx * dx + dy * dy;

            if (dist < (r + thick / 2) * (r + thick / 2)
                    && dist >= (r - thick / 2) * (r - thick / 2))
                QTEE_PIXEL(canvas, x, y) = color;
        }
    }
}

static void normalize_triangle(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3)
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

void qtee_triangle(qtee_canvas canvas, int x1, int y1, int x2, int y2, int x3, int y3,
        uint32_t color)
{
    normalize_triangle(&x1, &y1, &x2, &y2, &x3, &y3);

    int dx12 = x2 - x1;
    int dy12 = y2 - y1;
    int dx13 = x3 - x1;
    int dy13 = y3 - y1;

    for (int y = y1; y <= y2; y++)
    {
        if (y >= 0 && y < canvas.height)
        {
            int s1 = dy12 != 0 ? (y - y1) * dx12 / dy12 + x1 : x1;
            int s2 = dy13 != 0 ? (y - y1) * dx13 / dy13 + x1 : x1;

            if (s1 > s2) QTEE_SWAP(int, s1, s2);

            for (int x = s1; x <= s2; x++)
            {
                if (x >= 0 && x < canvas.width) QTEE_PIXEL(canvas, x, y) = color;
            }
        }
    }

    int dx32 = x2 - x3;
    int dy32 = y2 - y3;
    int dx31 = x1 - x3;
    int dy31 = y1 - y3;

    for (int y = y2; y <= y3; y++)
    {
        if (y >= 0 && y < canvas.height)
        {
            int s1 = dy32 != 0 ? (y - y3) * dx32 / dy32 + x3 : x3;
            int s2 = dy31 != 0 ? (y - y3) * dx31 / dy31 + x3 : x3;

            if (s1 > s2) QTEE_SWAP(int, s1, s2);

            for (int x = s1; x <= s2; x++)
            {
                if (x >= 0 && x < canvas.width) QTEE_PIXEL(canvas, x, y) = color;
            }
        }
    }
}

void qtee_line(qtee_canvas canvas, int x1, int y1, int x2, int y2, uint32_t color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (dx != 0)
    {
        int c = y1 - dy * x1 / dx;

        if (x1 > x2) QTEE_SWAP(int, x1, x2);
        for (int x = x1; x < x2; x++)
        {
            if (x >= 0 && x < canvas.width)
            {
                int sy1 = dy * x / dx + c;
                int sy2 = dy * (x + 1) / dx + c;
                if (sy1 > sy2) QTEE_SWAP(int, sy1, sy2);

                for (int y = sy1; y <= sy2; y++)
                {
                    if (y >= 0 && y < canvas.height) QTEE_PIXEL(canvas, x, y) = color;
                }
            }
        }
    }

    else
    {
        int x = x1;

        if (x >= 0 && x < canvas.width)
        {
            if (y1 > y2) QTEE_SWAP(int, y1, y2);

            for (int y = y1; y <= y2; y++)
            {
                if (y >= 0 && y < canvas.height) QTEE_PIXEL(canvas, x, y) = color;
            }
        }
    }
}

void qtee_text(qtee_canvas canvas, const char *text, int tx, int ty,
        qtee_font font, size_t size, uint32_t color)
{
    for (size_t i = 0; *text; i++, text++)
    {
        int gx = tx + i * font.width * size;
        int gy = ty;
        const char *glyph = &font.glyphs[(*text) * font.width * font.height];

        for (int dy = 0; dy < font.height; dy++)
        {
            for (int dx = 0; dx < font.width; dx++)
            {
                int px = gx + dx * size;
                int py = gy + dy * size;

                if (px >= 0 && px < canvas.width && py >= 0 && py < canvas.height)
                {
                    if (glyph[dy * font.width + dx])
                        qtee_rect(canvas, px, py, size, size, color);
                }
            }
        }
    }
}

void qtee_texture(qtee_canvas canvas, qtee_canvas texture, int tx, int ty, int w, int h)
{
    for (int y = 0; y < canvas.height; y++)
    {
        for (int x = 0; x < canvas.width; x++)
        {
            int sx = (x - tx) * texture.width / w;
            int sy = (y - ty) * texture.height / h;

            if (sx >= 0 && sx < texture.width && sy >= 0 && sy < texture.height)
            {
                QTEE_PIXEL(canvas, x, y) = QTEE_PIXEL(texture, sx, sy);
            }
        }
    }
}

uint32_t qtee_color_lerp(uint32_t color1, uint32_t color2, int t)
{
    uint8_t r1 = (color1 >> 16) & 0xFF; 
    uint8_t g1 = (color1 >> 8) & 0xFF; 
    uint8_t b1 = color1 & 0xFF;

    uint8_t r2 = (color2 >> 16) & 0xFF; 
    uint8_t g2 = (color2 >> 8) & 0xFF; 
    uint8_t b2 = color2 & 0xFF;

    uint8_t r = r1 + t * (r2 - r1);
    uint8_t g = g1 + t * (g2 - g1);
    uint8_t b = b1 + t * (b2 - b1);

    return (r << 16) | (g << 8) | b;
}

void qtee_write_ppm(qtee_canvas canvas, const char *path)
{
    FILE *f = fopen(path, "wb");

    fprintf(f, "P6\n%zu %zu 255\n", canvas.width, canvas.height);

    for (size_t i = 0; i < canvas.width * canvas.height; i++)
    {
        uint32_t pixel = canvas.pixels[i];
        uint8_t bytes[3] =
        {
            (pixel >> 16) & 0xFF,
            (pixel >> 8) & 0xFF,
             pixel & 0xFF
        };

        fwrite(bytes, sizeof(bytes), 1, f);
    }

    fclose(f);
}

qtee_canvas qtee_load_texture(const char *filename)
{
    int channels = 0;
    int width, height;
    uint8_t *data = stbi_load(filename, &width, &height, &channels, 4);
    uint32_t *pixels = malloc(width * height * sizeof(uint32_t));

    for (int i = 0; i < width * height; ++i)
    {
        uint8_t r = data[i * 4 + 0];
        uint8_t g = data[i * 4 + 1];
        uint8_t b = data[i * 4 + 2];
        uint8_t a = data[i * 4 + 3];

        pixels[i] = ((uint32_t)a << 24) | ((uint32_t)r << 16) |
            ((uint32_t)g << 8) | (uint32_t)b;
    }

    return qtee_create_canvas(pixels, width, height);
}
