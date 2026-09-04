#ifndef MW_WINDOWS_H
#define MW_WINDOWS_H

#include "mallow.h"

#ifdef PLATFORM_WINDOWS 
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#endif

typedef struct
{   
    texture *texture;
    HWND hwnd;
    HWND parent;
    HINSTANCE instance;
    WNDPROC wndproc;
    HBITMAP hbitmap;
    void *bitmap_info;
    HDC hdc;
    PAINTSTRUCT ps;
    bool should_close;
    bool keys[348];
    bool keys_prev[348];
    bool mouse_buttons[3];
    bool mouse_buttons_prev[3];
}mw_window_data;

void win_init_window(int width, int height, const char *title);
void win_start_drawing();
void win_end_drawing();
vec2 win_get_mouse_pos();
vec2 win_get_mouse_delta();
int win_get_mouse_wheel();
bool win_is_key_down(keyboard_key key);
bool win_is_key_pressed(keyboard_key key);
bool win_is_key_released(keyboard_key key);
bool win_is_mouse_button_down(mouse_button button);
bool win_is_mouse_button_pressed(mouse_button button);
bool win_is_mouse_button_released(mouse_button button);

#endif // MW_WINDOWS_H
