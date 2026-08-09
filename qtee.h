#ifndef QTEE_H
#define QTEE_H

#include <stdint.h>
#include <stddef.h>

#define QTEE_PIXEL(canvas, x, y) (canvas.pixels[(y) * canvas.width + (x)])
#define QTEE_SWAP(T, a, b) {T t = a; a = b; b = t;}

#define QTEE_DEFAULT_FONT_WIDTH 6
#define QTEE_DEFAULT_FONT_HEIGHT 6

typedef struct qtee_canvas
{
    size_t width, height;
    uint32_t *pixels;
}qtee_canvas;

typedef struct
{
    size_t width, height;
    const char *glyphs;
}qtee_font;

extern qtee_font qtee_default_font;

qtee_canvas qtee_create_canvas(uint32_t *pixels, size_t width, size_t height);
void qtee_fill_canvas(qtee_canvas canvas, uint32_t color);
void qtee_rect(qtee_canvas canvas, int x, int y, size_t width, size_t height, uint32_t color);
void qtee_circle(qtee_canvas canvas, int cx, int cy, size_t r, uint32_t color);
void qtee_circle_outline(qtee_canvas canvas, int cx, int cy, size_t r, size_t thick,
        uint32_t color);
void qtee_triangle(qtee_canvas canvas, int x1, int y1, int x2, int y2, int x3, int y3,
        uint32_t color);
void qtee_line(qtee_canvas canvas, int x1, int y1, int x2, int y2, uint32_t color);
void qtee_text(qtee_canvas canvas, const char *text, int tx, int ty,
        qtee_font font, size_t size, uint32_t color);
void qtee_texture(qtee_canvas canvas, qtee_canvas texture, int tx, int ty, int w, int h);

uint32_t qtee_color_lerp(uint32_t color1, uint32_t color2, int t);

void qtee_write_ppm(qtee_canvas canvas, const char *path);
qtee_canvas qtee_load_texture(const char *filename);

#endif //QTEE_H
