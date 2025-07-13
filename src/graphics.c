#include "graphics.h"
#include "colors.h"
#include <SDL/SDL_ttf.h>

void draw_arcade_title(SDL_Surface *screen, const char *title) {
    TTF_Font *font = TTF_OpenFont("assets/fonts/PressStart2P.ttf", 36);
    SDL_Color color = { 0xFF, 0x00, 0xFF }; 

    SDL_Surface *text = TTF_RenderText_Solid(font, title, color);
    SDL_Rect pos = { 50, 20, text->w, text->h };
    SDL_BlitSurface(text, NULL, screen, &pos);
    SDL_FreeSurface(text);
}

void draw_arcade_background(SDL_Surface *screen) {
    // Fill background
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x0A, 0x0A, 0x1A));

    // Draw grid lines
    for (int y = 0; y < screen->h; y += 2) {
        SDL_Rect line = { 0, y, screen->w, 1 };
        SDL_FillRect(screen, &line, SDL_MapRGB(screen->format, 0x30, 0x30, 0x30));
    }

    // Neon borders
    SDL_Rect border_top = { 0, 0, screen->w, 2 };
    SDL_FillRect(screen, &border_top, SDL_MapRGB(screen->format, 0x00, 0xFF, 0xFF)); // Cyan

    SDL_Rect border_left = { 0, 0, 2, screen->h };
    SDL_FillRect(screen, &border_left, SDL_MapRGB(screen->format, 0xFF, 0x00, 0xFF)); // Magenta
}

SDL_Surface* init_graphics() {
    // Initialize SDL Video and SDL_ttf
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL init error: %s\n", SDL_GetError());
        return NULL;
    }

    if (TTF_Init() == -1) {
        fprintf(stderr, "SDL_ttf init error: %s\n", TTF_GetError());
        SDL_Quit();
        return NULL;
    }

    // Framebuffer config (Raspberry Pi)
    setenv("SDL_VIDEODRIVER", "fbcon", 1);
    setenv("SDL_FBDEV", "/dev/fb0", 1);

    SDL_Surface *screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);
    if (!screen) {
        fprintf(stderr, "Surface creation error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return NULL;
    }

    return screen;
}

void draw_90s_button(SDL_Surface *screen, int x, int y, int w, int h, const char *text, int is_selected) {
    // Button background (changes if selected)
    SDL_Rect rect = { x, y, w, h };
    SDL_FillRect(screen, &rect, is_selected 
        ? SDL_MapRGB(screen->format, accent_color.r, accent_color.g, accent_color.b)
        : SDL_MapRGB(screen->format, 0x33, 0x33, 0x99));

    // 3D border (thicker if selected)
    SDL_Rect border = { x - 2, y - 2, w + 4, h + 4 };
    SDL_FillRect(screen, &border, is_selected 
        ? SDL_MapRGB(screen->format, 0xFF, 0xFF, 0x00)  // Yellow if selected
        : SDL_MapRGB(screen->format, 0x66, 0x66, 0xFF));

    // Button text
    draw_pixel_text(screen, x + 10, y + h/2 - 8, text, is_selected);
}

void draw_pixel_text(SDL_Surface *screen, int x, int y, const char *text, int is_selected) {
    // Load pixel font
    TTF_Font *font = TTF_OpenFont("assets/fonts/PerfectDOSVGA437.ttf", 16);
    if (!font) {
        fprintf(stderr, "Font load error: %s\n", TTF_GetError());
        return;
    }

    SDL_Color text_color = { 0xF4, 0xF4, 0xF4 }; // Retro white
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text, text_color);
    
    if (text_surface) {
        SDL_Rect dest_rect = { x, y, text_surface->w, text_surface->h };
        SDL_BlitSurface(text_surface, NULL, screen, &dest_rect);
        SDL_FreeSurface(text_surface);
    }

    TTF_CloseFont(font);
}