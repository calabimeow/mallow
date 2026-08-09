#include <windowsx.h>
#include <stdlib.h>
#include "mw_windows.h"
#include "qtee.h"

mw_window_data *window_data = NULL;
static MSG win_msg = {};

static POINT mouse_pos;
static POINT mouse_pos_prev;
static vec2 mouse_delta;
static int mouse_wheel;

static LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
        case WM_MOUSEMOVE:
            mouse_pos.x = GET_X_LPARAM(lparam);
            mouse_pos.y = GET_Y_LPARAM(lparam);
            mouse_delta.x = mouse_pos.x - mouse_pos_prev.x;
            mouse_delta.y = mouse_pos.y - mouse_pos_prev.y;
            mouse_pos_prev.x = mouse_pos.x;
            mouse_pos_prev.y = mouse_pos.y;
            return 0;
        case WM_MOUSEWHEEL:
            int mouse_wheel = GET_WHEEL_DELTA_WPARAM(wparam) / WHEEL_DELTA;
            return 0;
        case WM_LBUTTONDOWN:
            window_data->mouse_buttons[MOUSE_BUTTON_LEFT] = true;
            return 0;
        case WM_LBUTTONUP:
            window_data->mouse_buttons[MOUSE_BUTTON_LEFT] = false;
            return 0;
        case WM_RBUTTONDOWN:
            window_data->mouse_buttons[MOUSE_BUTTON_RIGHT] = true;
            return 0;
        case WM_RBUTTONUP:
            window_data->mouse_buttons[MOUSE_BUTTON_RIGHT] = false;
            return 0;
        case WM_MBUTTONDOWN:
            window_data->mouse_buttons[MOUSE_BUTTON_MIDDLE] = true;
            return 0;
        case WM_MBUTTONUP:
            window_data->mouse_buttons[MOUSE_BUTTON_MIDDLE] = false;
            return 0;

        case WM_QUIT:
            window_data->should_close = true;
            break;
        case WM_CLOSE:
            window_data->should_close = true;
            DestroyWindow(hwnd);
            return 0;


        case WM_KEYDOWN:
        {
            keyboard_key key = (keyboard_key)wparam;

            if      (key == VK_SPACE)       key = KEY_SPACE;
            else if (key == VK_ESCAPE)      key = KEY_ESCAPE;
            else if (key == VK_RETURN)      key = KEY_ENTER;
            else if (key == VK_TAB)         key = KEY_TAB;
            else if (key == VK_BACK)        key = KEY_BACKSPACE;
            else if (key == VK_INSERT)      key = KEY_INSERT;
            else if (key == VK_DELETE)      key = KEY_DELETE;
            else if (key == VK_RIGHT)       key = KEY_RIGHT;
            else if (key == VK_LEFT)        key = KEY_LEFT;
            else if (key == VK_DOWN)        key = KEY_DOWN;
            else if (key == VK_UP)          key = KEY_UP;
            else if (key == VK_PRIOR)       key = KEY_PAGE_UP;
            else if (key == VK_NEXT)        key = KEY_PAGE_DOWN;
            else if (key == VK_HOME)        key = KEY_HOME;
            else if (key == VK_END)         key = KEY_END;
            else if (key == VK_CAPITAL)     key = KEY_CAPS_LOCK;
            else if (key == VK_SCROLL)      key = KEY_SCROLL_LOCK;
            else if (key == VK_NUMLOCK)     key = KEY_NUM_LOCK;
            else if (key == VK_SNAPSHOT)    key = KEY_PRINT_SCREEN;
            else if (key == VK_PAUSE)       key = KEY_PAUSE;
            else if (key == VK_F1)          key = KEY_F1;
            else if (key == VK_F2)          key = KEY_F2;
            else if (key == VK_F3)          key = KEY_F3;
            else if (key == VK_F4)          key = KEY_F4;
            else if (key == VK_F5)          key = KEY_F5;
            else if (key == VK_F6)          key = KEY_F6;
            else if (key == VK_F7)          key = KEY_F7;
            else if (key == VK_F8)          key = KEY_F8;
            else if (key == VK_F9)          key = KEY_F9;
            else if (key == VK_F10)         key = KEY_F10;
            else if (key == VK_F11)         key = KEY_F11;
            else if (key == VK_F12)         key = KEY_F12;
            else if (key == VK_LSHIFT)      key = KEY_LEFT_SHIFT;
            else if (key == VK_LCONTROL)    key = KEY_LEFT_CONTROL;
            else if (key == VK_LMENU)       key = KEY_LEFT_ALT;
            else if (key == VK_LWIN)        key = KEY_LEFT_SUPER;
            else if (key == VK_RSHIFT)      key = KEY_RIGHT_SHIFT;
            else if (key == VK_RCONTROL)    key = KEY_RIGHT_CONTROL;
            else if (key == VK_RMENU)       key = KEY_RIGHT_ALT;
            else if (key == VK_RWIN)        key = KEY_RIGHT_SUPER;
            else if (key == VK_APPS)        key = KEY_MENU;
            
            window_data->keys[key] = true;
            return 0;
        }

        case WM_KEYUP:
        {
            keyboard_key key = (keyboard_key)wparam;

            if      (key == VK_SPACE)       key = KEY_SPACE;
            else if (key == VK_ESCAPE)      key = KEY_ESCAPE;
            else if (key == VK_RETURN)      key = KEY_ENTER;
            else if (key == VK_TAB)         key = KEY_TAB;
            else if (key == VK_BACK)        key = KEY_BACKSPACE;
            else if (key == VK_INSERT)      key = KEY_INSERT;
            else if (key == VK_DELETE)      key = KEY_DELETE;
            else if (key == VK_RIGHT)       key = KEY_RIGHT;
            else if (key == VK_LEFT)        key = KEY_LEFT;
            else if (key == VK_DOWN)        key = KEY_DOWN;
            else if (key == VK_UP)          key = KEY_UP;
            else if (key == VK_PRIOR)       key = KEY_PAGE_UP;
            else if (key == VK_NEXT)        key = KEY_PAGE_DOWN;
            else if (key == VK_HOME)        key = KEY_HOME;
            else if (key == VK_END)         key = KEY_END;
            else if (key == VK_CAPITAL)     key = KEY_CAPS_LOCK;
            else if (key == VK_SCROLL)      key = KEY_SCROLL_LOCK;
            else if (key == VK_NUMLOCK)     key = KEY_NUM_LOCK;
            else if (key == VK_SNAPSHOT)    key = KEY_PRINT_SCREEN;
            else if (key == VK_PAUSE)       key = KEY_PAUSE;
            else if (key == VK_F1)          key = KEY_F1;
            else if (key == VK_F2)          key = KEY_F2;
            else if (key == VK_F3)          key = KEY_F3;
            else if (key == VK_F4)          key = KEY_F4;
            else if (key == VK_F5)          key = KEY_F5;
            else if (key == VK_F6)          key = KEY_F6;
            else if (key == VK_F7)          key = KEY_F7;
            else if (key == VK_F8)          key = KEY_F8;
            else if (key == VK_F9)          key = KEY_F9;
            else if (key == VK_F10)         key = KEY_F10;
            else if (key == VK_F11)         key = KEY_F11;
            else if (key == VK_F12)         key = KEY_F12;
            else if (key == VK_LSHIFT)      key = KEY_LEFT_SHIFT;
            else if (key == VK_LCONTROL)    key = KEY_LEFT_CONTROL;
            else if (key == VK_LMENU)       key = KEY_LEFT_ALT;
            else if (key == VK_LWIN)        key = KEY_LEFT_SUPER;
            else if (key == VK_RSHIFT)      key = KEY_RIGHT_SHIFT;
            else if (key == VK_RCONTROL)    key = KEY_RIGHT_CONTROL;
            else if (key == VK_RMENU)       key = KEY_RIGHT_ALT;
            else if (key == VK_RWIN)        key = KEY_RIGHT_SUPER;
            else if (key == VK_APPS)        key = KEY_MENU;
            
            window_data->keys[key] = false;
            return 0;
        }

        default:
            return DefWindowProcW(hwnd, msg, wparam, lparam);
    }

    return 0;
}

void win_init_window(int width, int height, const char *title)
{   
    window_data = calloc(1, sizeof(mw_window_data));

    window_data->bitmap_info = calloc(1, sizeof(BITMAPINFO));
    BITMAPINFO *bmi = (BITMAPINFO*)window_data->bitmap_info;
    bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi->bmiHeader.biWidth = width;
    bmi->bmiHeader.biHeight = -height;
    bmi->bmiHeader.biPlanes = 1;
    bmi->bmiHeader.biBitCount = 32;
    bmi->bmiHeader.biCompression = BI_RGB;
    bmi->bmiHeader.biSizeImage = 0;

    window_data->canvas = calloc(1, sizeof(qtee_canvas));
    window_data->canvas->width = width;
    window_data->canvas->height = height;
    window_data->canvas->pixels = calloc(width * height, sizeof(uint32_t));

    window_data->instance = GetModuleHandle(NULL);

    WNDCLASSW wc = {0};
    wc.lpfnWndProc = window_proc;
    wc.hInstance = window_data->instance;
    wc.lpszClassName = L"mw_window_class";

    if (!RegisterClassW(&wc)) return;

    RECT rect = {0, 0, width, height};
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    window_data->hwnd = CreateWindowExA
    (
        0,
        "mw_window_class",
        title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL,
        NULL,
        window_data->instance,
        NULL
    );
}

vec2 win_get_mouse_pos()
{   
    return (vec2){mouse_pos.x, mouse_pos.y};
}

vec2 win_get_mouse_delta()
{
    return mouse_delta;
}

int win_get_mouse_wheel()
{
    return mouse_wheel;
}

void win_start_drawing()
{
    memcpy(window_data->keys_prev, window_data->keys, sizeof(window_data->keys));
    memcpy(window_data->mouse_buttons_prev, window_data->mouse_buttons,
            sizeof(window_data->mouse_buttons));

    if (PeekMessage(&win_msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&win_msg);
        DispatchMessage(&win_msg);
    }
    
    if (window_should_close()) return;
    
    window_data->hdc = GetDC(window_data->hwnd);
}

void win_end_drawing()
{
    StretchDIBits
    (
        window_data->hdc,
        0, 0, window_data->canvas->width, window_data->canvas->height,
        0, 0, window_data->canvas->width, window_data->canvas->height,
        window_data->canvas->pixels,
        window_data->bitmap_info,
        DIB_RGB_COLORS, 
        SRCCOPY
    );
    
    ReleaseDC(window_data->hwnd, window_data->hdc);
}

bool win_is_key_down(keyboard_key key)
{
    return window_data->keys[key];
}

bool win_is_key_pressed(keyboard_key key)
{
    return window_data->keys[key] && !window_data->keys_prev[key];
}

bool win_is_key_released(keyboard_key key)
{
    return !window_data->keys[key] && window_data->keys_prev[key];
}

bool win_is_mouse_button_down(mouse_button button)
{
    return window_data->mouse_buttons[button];
}

bool win_is_mouse_button_pressed(mouse_button button)
{
    return window_data->mouse_buttons[button] && !window_data->mouse_buttons_prev[button];
}

bool win_is_mouse_button_released(mouse_button button)
{
    return !window_data->mouse_buttons[button] && window_data->mouse_buttons_prev[button];
}
