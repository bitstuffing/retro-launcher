#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// 90s color palette
typedef struct {
    Uint8 r, g, b;
} Color;

extern Color bg_color;
extern Color accent_color;
extern Color text_color;
extern Color text_highlight_color;

// Initializes SDL and creates the window/framebuffer
SDL_Renderer* init_graphics();
void cleanup_graphics(SDL_Renderer *renderer);

// Draws a Windows 95 style button
void draw_90s_button(SDL_Renderer *renderer, int x, int y, int w, int h, const char *text, int is_selected);

// Draws pixelated text (using a bitmap font)
void draw_pixel_text(SDL_Renderer *renderer, int x, int y, const char *text, int is_selected);

// Draws the arcade menu background
void draw_arcade_background(SDL_Renderer *renderer);

// Draws the arcade menu title
void draw_arcade_title(SDL_Renderer *screen, const char *title);

// Draws the arcade menu border
void draw_arcade_border(SDL_Surface *screen);

// pixelate effect functions
void take_screenshot(SDL_Surface *screen, SDL_Surface *screenshot);
void pixelate(SDL_Renderer *renderer, SDL_Texture *screenshot, int frames, int pixel_chunk, int out);

#endif