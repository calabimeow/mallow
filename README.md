# mallow
Multimedia library written in C

## Features:

-No external dependencies

-Keyboard and mouse input

-Sound support

-Software rendering

-Works on Windows and Linux

**Note:**
this library is not done. Expect bugs

## Basic program example:
```c
#include <mallow.h>

#define WIDTH 800
#define HEIGHT 600

int main()
{
    init_window(WIDTH, HEIGHT, "<>");

    while (!window_should_close())
    {
        start_drawing();

        clear_bg(COLOR_WHITE);
        draw_circle(WIDTH / 2, HEIGHT / 2, 100, COLOR_RED);

        end_drawing();
    }
}
```
## Builing:
Write `make windows` or `make linux` depending on your OS. This will produce a shared library file in the source folder

## Linking
Put mallow.h, mallow.dll or libmallow.so files in you project directory and run this command:

`gcc main.c -o main -I"." -L"." -Wl,-rpath='.' -lmallow`
