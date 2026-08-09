#ifndef MALLOW_H
#define MALLOW_H

#define MALLOW_VERSION_MAJOR 0
#define MALLOW_VERSION_MINOR 1
#define MALLOW_VERSION_PATCH 0

#if defined (_WIN32) | defined (_WIN64)
    #define PLATFORM_WINDOWS

    #ifdef MALLOW_BUILD
        #define MALAPI __declspec(dllexport)
    #endif
    
    #ifdef MALLOW_USE
        #define MALAPI __declspec(dllimport)
    #endif
    
#elif defined (__linux__)
    #define PLATFORM_LINUX
    #define MALAPI __attribute__((visibility("default")))
#endif

#ifndef MALAPI
    #define MALAPI
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MALLOW_EXIT(msg) do\
{\
    fprintf(stderr, "[ERROR]: %s\n", msg);\
    exit(EXIT_FAILURE);\
} while(0);

#define MALLOW_WARNING(msg) do\
{\
    fprintf(stderr, "[WARNING]: %s\n", msg);\
} while(0);

#define PI 3.14159265358979323846f
#define DEG2RAD (PI/180.0f)
#define RAD2DEG (180.0f/PI)

// mallow uses ARGB color format
#define COLOR_WHITE   (0xFFFFFFFF)
#define COLOR_BLACK   (0xFF000000)
#define COLOR_RED     (0xFFFF0000)
#define COLOR_YELLOW  (0xFFFFFF00)
#define COLOR_GREEN   (0xFF00FF00)
#define COLOR_BLUE    (0xFF0000FF)
#define COLOR_CYAN    (0xFF00FFFF)
#define COLOR_MAGENTA (0xFFFF00FF)
#define COLOR_ORANGE  (0xFFFF8040)
#define COLOR_PINK    (0xFFFF0080)

typedef enum keyboard_key
{
    KEY_SPACE = 32,
    KEY_APOSTROPHE = 39,
    KEY_COMMA = 44,
    KEY_MINUS = 45,
    KEY_PERIOD = 46,
    KEY_SLASH = 47,
    KEY_0 = 48,
    KEY_1 = 49,
    KEY_2 = 50,
    KEY_3 = 51,
    KEY_4 = 52,
    KEY_5 = 53,
    KEY_6 = 54,
    KEY_7 = 55,
    KEY_8 = 56,
    KEY_9 = 57,
    KEY_SEMICOLON = 59,
    KEY_EQUAL = 61,
    KEY_A = 65,
    KEY_B = 66,
    KEY_C = 67,
    KEY_D = 68,
    KEY_E = 69,
    KEY_F = 70,
    KEY_G = 71,
    KEY_H = 72,
    KEY_I = 73,
    KEY_J = 74,
    KEY_K = 75,
    KEY_L = 76,
    KEY_M = 77,
    KEY_N = 78,
    KEY_O = 79,
    KEY_P = 80,
    KEY_Q = 81,
    KEY_R = 82,
    KEY_S = 83,
    KEY_T = 84,
    KEY_U = 85,
    KEY_V = 86,
    KEY_W = 87,
    KEY_X = 88,
    KEY_Y = 89,
    KEY_Z = 90,
    KEY_LEFT_BRACKET = 91,
    KEY_BACKSLASH = 92,
    KEY_RIGHT_BRACKET = 93,
    KEY_GRAVE_ACCENT = 96,
    KEY_ESCAPE = 256,
    KEY_ENTER = 257,
    KEY_TAB = 258,
    KEY_BACKSPACE = 259,
    KEY_INSERT = 260,
    KEY_DELETE = 261,
    KEY_RIGHT = 262,
    KEY_LEFT = 263,
    KEY_DOWN = 264,
    KEY_UP = 265,
    KEY_PAGE_UP = 266,
    KEY_PAGE_DOWN = 267,
    KEY_HOME = 268,
    KEY_END = 269,
    KEY_CAPS_LOCK = 280,
    KEY_SCROLL_LOCK = 281,
    KEY_NUM_LOCK = 282,
    KEY_PRINT_SCREEN = 283,
    KEY_PAUSE = 284,
    KEY_F1 = 290,
    KEY_F2 = 291,
    KEY_F3 = 292,
    KEY_F4 = 293,
    KEY_F5 = 294,
    KEY_F6 = 295,
    KEY_F7 = 296,
    KEY_F8 = 297,
    KEY_F9 = 298,
    KEY_F10 = 299,
    KEY_F11 = 300,
    KEY_F12 = 301,
    KEY_LEFT_SHIFT = 340,
    KEY_LEFT_CONTROL = 341,
    KEY_LEFT_ALT = 342,
    KEY_LEFT_SUPER = 343,
    KEY_RIGHT_SHIFT = 344,
    KEY_RIGHT_CONTROL = 345,
    KEY_RIGHT_ALT = 346,
    KEY_RIGHT_SUPER = 347,
    KEY_MENU = 348
}keyboard_key;

typedef enum mouse_button
{
    MOUSE_BUTTON_LEFT = 0,
    MOUSE_BUTTON_RIGHT = 1,
    MOUSE_BUTTON_MIDDLE = 2
}mouse_button;

typedef struct texture
{
    size_t width, height;
    uint32_t *pixels;
}texture;

typedef struct vec2 {float x, y;} vec2;
typedef struct vec3 {float x, y, z;} vec3;

typedef struct ma_sound ma_sound;
typedef struct ma_engine ma_engine;

typedef struct qtee_canvas qtee_canvas;

typedef struct sound
{
    ma_sound *sound;
    ma_engine *engine;
    bool loaded;
    bool playing;
}sound;

typedef struct camera2D
{
    vec2 pos;
    float zoom;
}camera2D;

// window
MALAPI void init_window(int width, int height, const char *title);
MALAPI void close_window();
MALAPI void toggle_fullscreen();
MALAPI int get_screen_width();
MALAPI int get_screen_height();
MALAPI vec2 get_screen_size();
MALAPI vec2 get_screen_center();
MALAPI bool window_should_close();

// drawing
MALAPI void start_drawing();
MALAPI void end_drawing();
MALAPI void clear_bg(uint32_t color);
MALAPI void draw_rect(int x, int y, size_t w, size_t h, uint32_t color);
MALAPI void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color);
MALAPI void draw_circle(int x, int y, size_t r, uint32_t color);
MALAPI void draw_circle_outline(int x, int y, size_t r, int thick, uint32_t color);
MALAPI void draw_text(const char *text, int x, int y, size_t size, uint32_t color);

// camera
MALAPI void start_2D(camera2D cam);
MALAPI void end_2D();
MALAPI vec2 get_screen_to_world(vec2 pos, camera2D cam);
MALAPI vec2 get_world_to_screen(vec2 pos, camera2D cam);

// mouse
MALAPI vec2 get_mouse_pos();
MALAPI vec2 get_mouse_delta();
MALAPI int get_mouse_wheel();

// input
MALAPI bool is_key_down(keyboard_key key);
MALAPI bool is_key_pressed(keyboard_key key);
MALAPI bool is_key_released(keyboard_key key);
MALAPI bool is_mouse_button_down(mouse_button button);
MALAPI bool is_mouse_button_pressed(mouse_button button);
MALAPI bool is_mouse_button_released(mouse_button button);

// sound
MALAPI sound load_sound(const char *path);
MALAPI void unload_sound(sound snd);
MALAPI void play_sound(sound snd);
MALAPI void stop_sound(sound snd);
MALAPI void resume_sound(sound snd);
MALAPI void set_sound_volume(sound snd, float volume);
MALAPI bool is_sound_playing(sound snd);

// files
MALAPI void write_ppm(const char *path, texture *texture);
MALAPI texture load_texture(const char *path);

// math
MALAPI float lerp(float start, float end, float amount);
MALAPI float clamp(float value, float min, float max);

MALAPI vec2 vec2_lerp(vec2 start, vec2 end, float amount);
MALAPI vec2 vec2_add(vec2 v1, vec2 v2);
MALAPI vec2 vec2_sub(vec2 v1, vec2 v2);
MALAPI vec2 vec2_mul(vec2 v1, vec2 v2);
MALAPI vec2 vec2_div(vec2 v1, vec2 v2);
MALAPI vec2 vec2_scale(vec2 v, float value);
MALAPI vec2 vec2_normalize(vec2 v);
MALAPI vec2 vec2_negate(vec2 v);
MALAPI vec2 vec2_dir(vec2 v1, vec2 v2);
MALAPI float vec2_dot(vec2 v1, vec2 v2);
MALAPI float vec2_cross(vec2 v1, vec2 v2);
MALAPI float vec2_length(vec2 v);
MALAPI float vec2_dist(vec2 v1, vec2 v2);

MALAPI vec3 vec3_lerp(vec3 start, vec3 end, float amount);
MALAPI vec3 vec3_add(vec3 v1, vec3 v2);
MALAPI vec3 vec3_sub(vec3 v1, vec3 v2);
MALAPI vec3 vec3_mul(vec3 v1, vec3 v2);
MALAPI vec3 vec3_div(vec3 v1, vec3 v2);
MALAPI vec3 vec3_scale(vec3 v, float value);
MALAPI vec3 vec3_normalize(vec3 v);
MALAPI vec3 vec3_negate(vec3 v);
MALAPI vec3 vec3_dir(vec3 v1, vec3 v2);
MALAPI float vec3_dot(vec3 v1, vec3 v2);
MALAPI vec3 vec3_cross(vec3 v1, vec3 v2);
MALAPI float vec3_length(vec3 v);
MALAPI float vec3_dist(vec3 v1, vec3 v2);

#endif // MALLOW_H
