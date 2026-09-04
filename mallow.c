#include "mallow.h"
#include <math.h>
#include "stb_image_write.h"

#ifndef MALLOW_BUILD
    #define MALLOW_BUILD
#endif

#ifdef PLATFORM_WINDOWS
    #include "mw_windows.h"
#endif

#ifdef PLATFORM_LINUX
    #include "mw_linux.h"
#endif

#define QTEE_IMPLEMENTATION
#include "qtee.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static ma_engine audio_engine = {};
static camera2D current_cam =
{
    .pos = {},
    .zoom = 1.0f
};

extern mw_window_data *window_data;

// window
void init_window(int width, int height, const char *title)
{
    ma_engine_init(NULL, &audio_engine);

    #ifdef PLATFORM_WINDOWS   
        win_init_window(width, height, title);
    #endif

    #ifdef PLATFORM_LINUX  
        lin_init_window(width, height, title);
    #endif
}

void close_window()
{
    window_data->should_close = true;
}

int get_screen_width()
{
    return window_data->texture->width;
}

int get_screen_height()
{
    return window_data->texture->height;
}

vec2 get_screen_size()
{
    return (vec2){window_data->texture->width, window_data->texture->height};
}

vec2 get_screen_center()
{
    return (vec2){(float)window_data->texture->width / 2, (float)window_data->texture->height / 2};
}

bool window_should_close()
{
    return window_data->should_close || is_key_pressed(KEY_ESCAPE);
}

// drawing
void start_drawing()
{
    #ifdef PLATFORM_WINDOWS
        win_start_drawing();
    #endif

    #ifdef PLATFORM_LINUX 
        lin_start_drawing();
    #endif
}

void end_drawing()
{
    #ifdef PLATFORM_WINDOWS
        win_end_drawing();
    #endif

    #ifdef PLATFORM_LINUX 
        lin_end_drawing();
    #endif
}

void clear_bg(uint32_t color)
{
    qtee_fill_texture(*(qtee_texture*)window_data->texture, color);
}

void draw_rect(int x, int y, size_t w, size_t h, uint32_t color)
{
    vec2 screen_pos = get_world_to_screen((vec2){x, y}, current_cam);
    qtee_draw_rect(*(qtee_texture*)window_data->texture, screen_pos.x, screen_pos.y, w, h, color);
}

void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color)
{
    vec2 screen_pos1 = get_world_to_screen((vec2){x1, y1}, current_cam);
    vec2 screen_pos2 = get_world_to_screen((vec2){x2, y2}, current_cam);
    vec2 screen_pos3 = get_world_to_screen((vec2){x3, y3}, current_cam);

    qtee_draw_triangle
    (
        *(qtee_texture*)window_data->texture,
        screen_pos1.x, screen_pos1.y,
        screen_pos2.x, screen_pos2.y,
        screen_pos3.x, screen_pos3.y,
        color
    );
}

void draw_circle(int x, int y, size_t r, uint32_t color)
{
    vec2 screen_pos = get_world_to_screen((vec2){x, y}, current_cam);
    qtee_draw_circle(*(qtee_texture*)window_data->texture, screen_pos.x, screen_pos.y, r, color);
}

void draw_text(char *text, int x, int y, size_t size, uint32_t color)
{
    vec2 screen_pos = get_world_to_screen((vec2){x, y}, current_cam);
    qtee_draw_text(*(qtee_texture*)window_data->texture, text, screen_pos.x, screen_pos.y,
            size, qtee_default_font, color);
}

void draw_texture(texture tex, int x, int y, size_t w, size_t h)
{
    vec2 screen_pos = get_world_to_screen((vec2){x, y}, current_cam);
    qtee_draw_subtexture(*(qtee_texture*)window_data->texture, *(qtee_texture*)&tex,
            screen_pos.x, screen_pos.y, w, h);
}

// camera
void start_2D(camera2D cam)
{
    current_cam = cam;
}

void end_2D()
{
    current_cam = (camera2D){{0, 0}, 1.0f};
}

vec2 get_screen_to_world(vec2 pos, camera2D cam)
{
    float worldX = (pos.x - get_screen_center().x) / cam.zoom + cam.pos.x;
    float worldY = (pos.y - get_screen_center().y) / cam.zoom + cam.pos.y;
    return (vec2){worldX, worldY};
}

vec2 get_world_to_screen(vec2 pos, camera2D cam)
{
    float screenX = (pos.x - cam.pos.x) * cam.zoom + get_screen_center().x;
    float screenY = (pos.y - cam.pos.y) * cam.zoom + get_screen_center().y;
    return (vec2){screenX, screenY};
}

// mouse
vec2 get_mouse_pos()
{
    #ifdef PLATFORM_WINDOWS
        return win_get_mouse_pos();
    #endif

    #ifdef PLATFORM_LINUX
        return lin_get_mouse_pos();
    #endif
}

vec2 get_mouse_delta()
{
    #ifdef PLATFORM_WINDOWS
        return win_get_mouse_delta();
    #endif

    #ifdef PLATFORM_LINUX
        return lin_get_mouse_delta();
    #endif 
}

int get_mouse_wheel()
{
    #ifdef PLATFORM_WINDOWS
        return win_get_mouse_wheel();
    #endif

    #ifdef PLATFORM_LINUX
        return lin_get_mouse_wheel();
    #endif 
}

// input
bool is_key_down(keyboard_key key)
{
    #ifdef PLATFORM_WINDOWS
        return win_is_key_down(key);
    #endif

    #ifdef PLATFORM_LINUX
        return lin_is_key_down(key);
    #endif
}

bool is_key_pressed(keyboard_key key)
{
    #ifdef PLATFORM_WINDOWS
        return win_is_key_pressed(key);
    #endif

    #ifdef PLATFORM_LINUX
        return lin_is_key_pressed(key);
    #endif
}

bool is_key_released(keyboard_key key)
{
    #ifdef PLATFORM_WINDOWS
        return win_is_key_released(key);
    #endif

    #ifdef PLATFORM_LINUX
        return lin_is_key_released(key);
    #endif
}

bool is_mouse_button_down(mouse_button button)
{
    #ifdef PLATFORM_WINDOWS
        return win_is_mouse_button_down(button);
    #endif

    #ifdef PLATFORM_LINUX
        return lin_is_mouse_button_down(button);
    #endif
}

bool is_mouse_button_pressed(mouse_button button)
{
    #ifdef PLATFORM_WINDOWS
        return win_is_mouse_button_pressed(button);
    #endif

    #ifdef PLATFORM_LINUX
        return lin_is_mouse_button_pressed(button);
    #endif
}

bool is_mouse_button_released(mouse_button button)
{
    #ifdef PLATFORM_WINDOWS
        return win_is_mouse_button_released(button);
    #endif

    #ifdef PLATFORM_LINUX
        return lin_is_mouse_button_released(button);
    #endif
}

// sound
sound load_sound(const char *path)
{
    sound snd = {};
    snd.engine = &audio_engine;
    snd.sound = (ma_sound*)calloc(1, sizeof(ma_sound));
    ma_result result = ma_sound_init_from_file(&audio_engine, path, 0, NULL, NULL, snd.sound);

    if (result != MA_SUCCESS)
    {
        char str[64];
        sprintf(str, "couldn't load sound at \"%s\"", path);
        MALLOW_WARNING(str);

        free(snd.sound);
        snd.sound = NULL;
        snd.loaded = false;
        return snd;
    }

    snd.loaded = true;
    snd.playing = false;
    return snd;
}

void unload_sound(sound snd)
{
    if (!snd.loaded) return; 
    ma_sound_uninit(snd.sound);
    free(snd.sound);
    snd.sound = NULL;
    snd.loaded = false;
}

void play_sound(sound snd)
{
    if (!snd.loaded) return; 
    ma_sound_seek_to_pcm_frame(snd.sound, 0);
    ma_sound_start(snd.sound);
    snd.playing = true;
}

void stop_sound(sound snd)
{
    if (!snd.loaded) return; 
    ma_sound_stop(snd.sound);
    snd.playing = false;
}

void resume_sound(sound snd)
{
    if (!snd.loaded) return; 
    ma_sound_start(snd.sound);
    snd.playing = true;
}

void set_sound_volume(sound snd, float volume)
{
    if (!snd.loaded) return; 
    ma_sound_set_volume(snd.sound, volume);
}

bool is_sound_playing(sound snd)
{
    return snd.playing;
}

// files
/*void save_texture(const char *path, texture *texture)
{
    texture texture = qtee_create_texture(texture->pixels, texture->width, texture->height);
    qtee_write_ppm(texture, path);
}*/

texture *load_texture(char *path)
{
    int w, h, ch;
    uint8_t *data = stbi_load(path, &w, &h, &ch, 4);

    qtee_texture qtee_tex = qtee_load_texture(data, w, h);

    texture *tex = malloc(sizeof(*tex));
    *tex = *(texture*)&qtee_tex;

    stbi_image_free(data);

    return tex;
}

// math
float lerp(float start, float end, float amount)
{
    return (1.0f - amount) * start + amount * end;
}

float clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

vec2 vec2_lerp(vec2 start, vec2 end, float amount)
{
    return (vec2)
    {
        (1.0f - amount) * start.x + amount * end.x,
        (1.0f - amount) * start.y + amount * end.y,
    };
}


vec2 vec2_add(vec2 v1, vec2 v2)
{
    return (vec2){v1.x + v2.x, v1.y + v2.y};
}

vec2 vec2_sub(vec2 v1, vec2 v2)
{
    return (vec2){v1.x - v2.x, v1.y - v2.y};
}

vec2 vec2_mul(vec2 v1, vec2 v2)
{
    return (vec2){v1.x * v2.x, v1.y * v2.y};
}

vec2 vec2_div(vec2 v1, vec2 v2)
{
    return (vec2)
    {
        v2.x == 0 ? 0 : v1.x / v2.x,
        v2.y == 0 ? 0 : v1.y / v2.y
    };
}

vec2 vec2_scale(vec2 v, float value)
{
    return(vec2){v.x * value, v.y * value};
}

vec2 vec2_normalize(vec2 v)
{
    float length = vec2_length(v);
    if (length == 0.0f) return (vec2){0, 0};
    return (vec2){v.x / length, v.y / length};
}

vec2 vec2_negate(vec2 v)
{
    return (vec2){-v.x, -v.y};
}

vec2 vec2_dir(vec2 v1, vec2 v2)
{
    return vec2_sub(v2, v1);
}

float vec2_dot(vec2 v1, vec2 v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}

float vec2_cross(vec2 v1, vec2 v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}

float vec2_length(vec2 v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

float vec2_dist(vec2 v1, vec2 v2)
{
    return sqrtf(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
}


vec3 vec3_lerp(vec3 start, vec3 end, float amount)
{
    return (vec3)
    {
        (1.0f - amount) * start.x + amount * end.x,
        (1.0f - amount) * start.y + amount * end.y,
        (1.0f - amount) * start.z + amount * end.z,
    };
}

vec3 vec3_add(vec3 v1, vec3 v2)
{
    return (vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

vec3 vec3_sub(vec3 v1, vec3 v2)
{
    return (vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

vec3 vec3_mul(vec3 v1, vec3 v2)
{
    return (vec3){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}

vec3 vec3_div(vec3 v1, vec3 v2)
{
    return (vec3)
    {
        v2.x == 0 ? 0 : v1.x / v2.x,
        v2.y == 0 ? 0 : v1.y / v2.y,
        v2.z == 0 ? 0 : v1.z / v2.z
    };
}

vec3 vec3_scale(vec3 v, float value)
{
    return(vec3){v.x * value, v.y * value, v.z * value};
}

vec3 vec3_normalize(vec3 v)
{
    float length = vec3_length(v);
    if (length == 0.0f) return (vec3){0, 0, 0};
    return (vec3){v.x / length, v.y / length, v.z / length};
}

vec3 vec3_negate(vec3 v)
{
    return (vec3){-v.x, -v.y, -v.z};
}

vec3 vec3_cross(vec3 v1, vec3 v2)
{
    return (vec3)
    {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}

vec3 vec3_dir(vec3 v1, vec3 v2)
{
    return vec3_sub(v2, v1);
}

float vec3_dot(vec3 v1, vec3 v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}


float vec3_length(vec3 v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

float vec3_dist(vec3 v1, vec3 v2)
{
    return sqrtf(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) + pow(v2.z - v1.z, 2));
}

