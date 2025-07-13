#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL/SDL.h>

// 90s color palette
typedef struct {
    Uint8 r, g, b;
} Color;

extern Color bg_color;
extern Color accent_color;
extern Color text_color;
extern Color text_highlight_color;

// Initializes SDL and creates the window/framebuffer
SDL_Surface* init_graphics();

// Draws a Windows 95 style button
void draw_90s_button(SDL_Surface *screen, int x, int y, int w, int h, const char *text, int is_selected);

// Draws pixelated text (using a bitmap font)
void draw_pixel_text(SDL_Surface *screen, int x, int y, const char *text, int is_selected);

// Draws the arcade menu background
void draw_arcade_background(SDL_Surface *screen);

// Draws the arcade menu title
void draw_arcade_title(SDL_Surface *screen, const char *title);

// Draws the arcade menu border
void draw_arcade_border(SDL_Surface *screen);

#endif