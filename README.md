# mallow
Multi-media library for C

Basic program example:
```c
#include <mallow.h>

#define WIDTH 800
#define HEIGHT 600

int main()
{
    init_window("<>", WIDTH, HEIGHT);

    while (!window_should_close())
    {
        start_drawing();

        clear_bg(COLOR_WHITE);
        draw_circle(WIDTH / 2, HEIGHT / 2, 100, COLOR_RED);

        end_drawing();
    }
}
```
