#include "mw_linux.h"
#include <stdlib.h>
#include <string.h>
#include "qtee.h"

mw_window_data *window_data = NULL;
static vec2 mouse_pos;
static vec2 mouse_pos_prev;
static vec2 mouse_delta;
static int mouse_wheel;

void lin_init_window(int width, int height, const char *title)
{
    window_data = calloc(1, sizeof(mw_window_data));

    window_data->canvas = calloc(1, sizeof(qtee_canvas));
    window_data->canvas->width = width;
    window_data->canvas->height = height;

    window_data->display = XOpenDisplay(NULL);
    window_data->screen = DefaultScreen(window_data->display);
    window_data->window = XCreateSimpleWindow
    (
        window_data->display,
        RootWindow(window_data->display, window_data->screen),
        0, 0,
        width, height,
        1,
        BlackPixel(window_data->display, window_data->screen),
        WhitePixel(window_data->display, window_data->screen)
    );

    XStoreName(window_data->display, window_data->window, title);

    window_data->gc = XCreateGC(window_data->display, window_data->window, 0, NULL);

    window_data->image = XCreateImage
    (
        window_data->display,
        DefaultVisual(window_data->display, window_data->screen),
        DefaultDepth(window_data->display, window_data->screen),
        ZPixmap,
        0,
        (char*)window_data->canvas->pixels,
        width,
        height,
        32,
        width * sizeof(uint32_t)
    );

    XSelectInput
    (
        window_data->display, window_data->window,
        ExposureMask | 
        KeyPressMask | 
        KeyReleaseMask | 
        PointerMotionMask |
        StructureNotifyMask
    );

    XkbSetDetectableAutoRepeat(window_data->display, True, NULL);
    XMapWindow(window_data->display, window_data->window);

    XShmSegmentInfo *shminfo = calloc(1, sizeof(XShmSegmentInfo));
    window_data->image = XShmCreateImage
    (
        window_data->display,
        DefaultVisual(window_data->display, window_data->screen),
        DefaultDepth(window_data->display, window_data->screen),
        ZPixmap,
        NULL,
        shminfo,
        width,
        height
    );

    shminfo->shmid = shmget(IPC_PRIVATE, 
            window_data->image->bytes_per_line * window_data->image->height, IPC_CREAT|0777);
    shminfo->shmaddr = window_data->image->data = shmat(shminfo->shmid, 0, 0);
    shminfo->readOnly = False;
    XShmAttach(window_data->display, shminfo);

    window_data->canvas->pixels = (uint32_t*)shminfo->shmaddr;

    Atom wm_delete_window = XInternAtom(window_data->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(window_data->display, window_data->window, &wm_delete_window, 1);
}

void lin_start_drawing()
{
    memcpy(window_data->keys_prev, window_data->keys, sizeof(window_data->keys));
    memcpy(window_data->mouse_buttons_prev, window_data->mouse_buttons,
            sizeof(window_data->mouse_buttons));

    if (XPending(window_data->display) > 0)
    {
        XNextEvent(window_data->display, &window_data->event);
        
        switch (window_data->event.type)
        {
            case ButtonPress:
            {
                if (window_data->event.xbutton.button == Button1)
                {
                    window_data->mouse_buttons[MOUSE_BUTTON_LEFT] = true;
                }
                else if (window_data->event.xbutton.button == Button2)
                {
                    window_data->mouse_buttons[MOUSE_BUTTON_MIDDLE] = true;
                }
                else if (window_data->event.xbutton.button == Button3)
                {
                    window_data->mouse_buttons[MOUSE_BUTTON_RIGHT] = true;
                }
                else if (window_data->event.xbutton.button == Button4)
                {
                    mouse_wheel += 1;
                }
                else if (window_data->event.xbutton.button == Button5)
                {
                    mouse_wheel -= 1;
                }
                break;
            }

            case ButtonRelease:
            {
                if (window_data->event.xbutton.button == Button1)
                {
                    window_data->mouse_buttons[MOUSE_BUTTON_LEFT] = false;
                }
                else if (window_data->event.xbutton.button == Button2)
                {
                    window_data->mouse_buttons[MOUSE_BUTTON_MIDDLE] = false;
                }
                else if (window_data->event.xbutton.button == Button3)
                {
                    window_data->mouse_buttons[MOUSE_BUTTON_RIGHT] = false;
                }
                break;
            }

            case KeyPress:
            {
                KeySym keysym = XLookupKeysym(&window_data->event.xkey, 0);
                keyboard_key key = 0;

                if (keysym >= 'a' && keysym <= 'z')
                {
                    key = (keyboard_key)(keysym - 32);
                }
                else if (keysym >= 'A' && keysym <= 'Z')
                {
                    key = (keyboard_key)keysym;
                }
                else if (keysym >= '0' && keysym <= '9')
                {
                    key = (keyboard_key)keysym;
                }
                else if (keysym >= 32 && keysym <= 126)
                {
                    key = (keyboard_key)keysym;
                }

                if      (keysym == XK_space)        key = KEY_SPACE;
                else if (keysym == XK_Escape)       key = KEY_ESCAPE;
                else if (keysym == XK_Return)       key = KEY_ENTER;
                else if (keysym == XK_Tab)          key = KEY_TAB;
                else if (keysym == XK_BackSpace)    key = KEY_BACKSPACE;
                else if (keysym == XK_Insert)       key = KEY_INSERT;
                else if (keysym == XK_Delete)       key = KEY_DELETE;
                else if (keysym == XK_Right)        key = KEY_RIGHT;
                else if (keysym == XK_Left)         key = KEY_LEFT;
                else if (keysym == XK_Down)         key = KEY_DOWN;
                else if (keysym == XK_Up)           key = KEY_UP;
                else if (keysym == XK_Page_Up)      key = KEY_PAGE_UP;
                else if (keysym == XK_Page_Down)    key = KEY_PAGE_DOWN;
                else if (keysym == XK_Home)         key = KEY_HOME;
                else if (keysym == XK_End)          key = KEY_END;
                else if (keysym == XK_Caps_Lock)    key = KEY_CAPS_LOCK;
                else if (keysym == XK_Scroll_Lock)  key = KEY_SCROLL_LOCK;
                else if (keysym == XK_Num_Lock)     key = KEY_NUM_LOCK;
                else if (keysym == XK_Print)        key = KEY_PRINT_SCREEN;
                else if (keysym == XK_Pause)        key = KEY_PAUSE;
                else if (keysym == XK_F1)           key = KEY_F1;
                else if (keysym == XK_F2)           key = KEY_F2;
                else if (keysym == XK_F3)           key = KEY_F3;
                else if (keysym == XK_F4)           key = KEY_F4;
                else if (keysym == XK_F5)           key = KEY_F5;
                else if (keysym == XK_F6)           key = KEY_F6;
                else if (keysym == XK_F7)           key = KEY_F7;
                else if (keysym == XK_F8)           key = KEY_F8;
                else if (keysym == XK_F9)           key = KEY_F9;
                else if (keysym == XK_F10)          key = KEY_F10;
                else if (keysym == XK_F11)          key = KEY_F11;
                else if (keysym == XK_F12)          key = KEY_F12;
                else if (keysym == XK_Shift_L)      key = KEY_LEFT_SHIFT;
                else if (keysym == XK_Control_L)    key = KEY_LEFT_CONTROL;
                else if (keysym == XK_Alt_L)        key = KEY_LEFT_ALT;
                else if (keysym == XK_Super_L)      key = KEY_LEFT_SUPER;
                else if (keysym == XK_Shift_R)      key = KEY_RIGHT_SHIFT;
                else if (keysym == XK_Control_R)    key = KEY_RIGHT_CONTROL;
                else if (keysym == XK_Alt_R)        key = KEY_RIGHT_ALT;
                else if (keysym == XK_Super_R)      key = KEY_RIGHT_SUPER;
                else if (keysym == XK_Menu)         key = KEY_MENU;

                window_data->keys[key] = true;

                break;
            }
                
            case KeyRelease:
            {
                if (window_data->event.xkey.same_screen && 
                    XEventsQueued(window_data->display, QueuedAfterReading))
                {
                    XEvent next_event;
                    XPeekEvent(window_data->display, &next_event);

                    if (next_event.type == KeyPress && 
                        next_event.xkey.keycode == window_data->event.xkey.keycode &&
                        next_event.xkey.time == window_data->event.xkey.time)
                    {
                        break;
                    }
                }

                KeySym keysym = XLookupKeysym(&window_data->event.xkey, 0);
                keyboard_key key = 0;

               if (keysym >= 'a' && keysym <= 'z')
                {
                    key = (keyboard_key)(keysym - 32);
                }
                else if (keysym >= 'A' && keysym <= 'Z')
                {
                    key = (keyboard_key)keysym;
                }
                else if (keysym >= '0' && keysym <= '9')
                {
                    key = (keyboard_key)keysym;
                }
                else if (keysym >= 32 && keysym <= 126)
                {
                    key = (keyboard_key)keysym;
                }

                if ((keysym >= 32 && keysym <= 126) && keysym != 0)
                {
                    window_data->keys[keysym] = false;
                }

                if      (keysym == XK_space)        key = KEY_SPACE;
                else if (keysym == XK_Escape)       key = KEY_ESCAPE;
                else if (keysym == XK_Return)       key = KEY_ENTER;
                else if (keysym == XK_Tab)          key = KEY_TAB;
                else if (keysym == XK_BackSpace)    key = KEY_BACKSPACE;
                else if (keysym == XK_Insert)       key = KEY_INSERT;
                else if (keysym == XK_Delete)       key = KEY_DELETE;
                else if (keysym == XK_Right)        key = KEY_RIGHT;
                else if (keysym == XK_Left)         key = KEY_LEFT;
                else if (keysym == XK_Down)         key = KEY_DOWN;
                else if (keysym == XK_Up)           key = KEY_UP;
                else if (keysym == XK_Page_Up)      key = KEY_PAGE_UP;
                else if (keysym == XK_Page_Down)    key = KEY_PAGE_DOWN;
                else if (keysym == XK_Home)         key = KEY_HOME;
                else if (keysym == XK_End)          key = KEY_END;
                else if (keysym == XK_Caps_Lock)    key = KEY_CAPS_LOCK;
                else if (keysym == XK_Scroll_Lock)  key = KEY_SCROLL_LOCK;
                else if (keysym == XK_Num_Lock)     key = KEY_NUM_LOCK;
                else if (keysym == XK_Print)        key = KEY_PRINT_SCREEN;
                else if (keysym == XK_Pause)        key = KEY_PAUSE;
                else if (keysym == XK_F1)           key = KEY_F1;
                else if (keysym == XK_F2)           key = KEY_F2;
                else if (keysym == XK_F3)           key = KEY_F3;
                else if (keysym == XK_F4)           key = KEY_F4;
                else if (keysym == XK_F5)           key = KEY_F5;
                else if (keysym == XK_F6)           key = KEY_F6;
                else if (keysym == XK_F7)           key = KEY_F7;
                else if (keysym == XK_F8)           key = KEY_F8;
                else if (keysym == XK_F9)           key = KEY_F9;
                else if (keysym == XK_F10)          key = KEY_F10;
                else if (keysym == XK_F11)          key = KEY_F11;
                else if (keysym == XK_F12)          key = KEY_F12;
                else if (keysym == XK_Shift_L)      key = KEY_LEFT_SHIFT;
                else if (keysym == XK_Control_L)    key = KEY_LEFT_CONTROL;
                else if (keysym == XK_Alt_L)        key = KEY_LEFT_ALT;
                else if (keysym == XK_Super_L)      key = KEY_LEFT_SUPER;
                else if (keysym == XK_Shift_R)      key = KEY_RIGHT_SHIFT;
                else if (keysym == XK_Control_R)    key = KEY_RIGHT_CONTROL;
                else if (keysym == XK_Alt_R)        key = KEY_RIGHT_ALT;
                else if (keysym == XK_Super_R)      key = KEY_RIGHT_SUPER;
                else if (keysym == XK_Menu)         key = KEY_MENU;

                window_data->keys[key] = false;

                break;
            }

            case MotionNotify:
                mouse_pos.x = window_data->event.xmotion.x;
                mouse_pos.y = window_data->event.xmotion.y;
                mouse_delta.x = mouse_pos.x - mouse_pos_prev.x;
                mouse_delta.y = mouse_pos.y - mouse_pos_prev.y;
                mouse_pos_prev.x = mouse_pos.x;
                mouse_pos_prev.y = mouse_pos.y;
                break;

            case ClientMessage:
            {
                if (window_data->event.xclient.data.l[0] == 
                    XInternAtom(window_data->display, "WM_DELETE_WINDOW", False))
                {
                    window_data->should_close = true;
                }

                break;
            }
        }
    }
}

void lin_end_drawing()
{
    XShmPutImage
    (
        window_data->display,
        window_data->window,
        window_data->gc,
        window_data->image,
        0, 0, 0, 0,
        window_data->canvas->width,
        window_data->canvas->height,
        False
    );

    XSync(window_data->display, False);
}

vec2 lin_get_mouse_pos()
{
    return mouse_pos;
}

vec2 lin_get_mouse_delta()
{
    return mouse_delta;
}

int lin_get_mouse_wheel()
{
    return mouse_wheel;
}

bool lin_is_key_down(keyboard_key key)
{
    return window_data->keys[key];
}

bool lin_is_key_pressed(keyboard_key key)
{
    return window_data->keys[key] && !window_data->keys_prev[key];
}

bool lin_is_key_released(keyboard_key key)
{
    return !window_data->keys[key] && window_data->keys_prev[key];
}

bool lin_is_mouse_button_down(mouse_button button)
{
    return window_data->mouse_buttons[button];
}

bool lin_is_mouse_button_pressed(mouse_button button)
{
    return window_data->mouse_buttons[button] && !window_data->mouse_buttons_prev[button];
}

bool lin_is_mouse_button_released(mouse_button button)
{
    return !window_data->mouse_buttons[button] && window_data->mouse_buttons_prev[button];
}

