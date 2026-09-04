#ifndef MW_LINUX_H
#define MW_LINUX_H

#include "mallow.h"

#ifdef PLATFORM_LINUX
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/keysym.h>
    #include <X11/XKBlib.h>
    #include <X11/extensions/XShm.h>
    #include <sys/shm.h>
#endif

typedef struct
{
    texture *texture;
    Display *display;
    Window window;
    XEvent event;
    int screen;
    GC gc;
    XImage *image;
    bool should_close;
    bool keys[348];
    bool keys_prev[348];
    bool mouse_buttons[3];
    bool mouse_buttons_prev[3];
}mw_window_data;

void lin_init_window(int width, int height, const char *title);
void lin_start_drawing();
void lin_end_drawing();
vec2 lin_get_mouse_pos();
vec2 lin_get_mouse_delta();
int lin_get_mouse_wheel();
bool lin_is_key_down(keyboard_key key);
bool lin_is_key_pressed(keyboard_key key);
bool lin_is_key_released(keyboard_key key);
bool lin_is_mouse_button_down(mouse_button button);
bool lin_is_mouse_button_pressed(mouse_button button);
bool lin_is_mouse_button_released(mouse_button button);

#endif // MW_LINUX_H
