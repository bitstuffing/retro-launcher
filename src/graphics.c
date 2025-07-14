#include "graphics.h"
#include "colors.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

static SDL_Window *g_window = NULL;  // Store window globally for cleanup

void take_screenshot(SDL_Surface *screen, SDL_Surface *screenshot) {
    SDL_BlitSurface(screen, NULL, screenshot, NULL);
}

void pixelate(SDL_Renderer *renderer, SDL_Texture *screenshot, int frames, int pixel_chunk, int out) {
    // 1. Basic check
    if (!renderer || !screenshot) {
        fprintf(stderr, "Error: Null texture\n");
        return;
    }

    // 2. Use the texture directly
    SDL_Texture *texture = screenshot;

    // 3. Safe processing
    for (int i = 0; i < frames; i++) {
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer); // Presentar el renderer

        pixel_chunk = out ? pixel_chunk + 2 : pixel_chunk - 2;
        if (pixel_chunk < 1) pixel_chunk = 1;
        SDL_Delay(16);
    }

    SDL_DestroyTexture(texture); // Liberar la textura
}


void draw_arcade_title(SDL_Renderer *renderer, const char *title) {
    TTF_Font *font = TTF_OpenFont("assets/fonts/PressStart2P.ttf", 36);
    if (!font) {
        fprintf(stderr, "Error al abrir la fuente: %s\n", TTF_GetError());
        return;
    }

    SDL_Color color = { 0xFF, 0x00, 0xFF, 0xFF }; // Color del texto (RGBA)
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, title, color);
    if (!text_surface) {
        fprintf(stderr, "Error al renderizar el texto: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (!text_texture) {
        fprintf(stderr, "Error al crear la textura del texto: %s\n", SDL_GetError());
        SDL_FreeSurface(text_surface);
        TTF_CloseFont(font);
        return;
    }

    SDL_Rect pos = { 50, 20, text_surface->w, text_surface->h };

    SDL_RenderCopy(renderer, text_texture, NULL, &pos);

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
}

void draw_arcade_background(SDL_Renderer *renderer) {
    // Fill background
    SDL_SetRenderDrawColor(renderer, 0x0A, 0x0A, 0x1A, 0xFF); // Color de fondo
    SDL_RenderClear(renderer); // Limpiar el renderer con el color de fondo

    // Draw grid lines
    SDL_SetRenderDrawColor(renderer, 0x30, 0x30, 0x30, 0xFF); // Color de las líneas
    for (int y = 0; y < 480; y += 2) { // Asumiendo que la altura es 480
        SDL_RenderDrawLine(renderer, 0, y, 640, y); // Asumiendo que el ancho es 640
    }

    // Borders
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF); // Color cian
    SDL_Rect border_top = { 0, 0, 640, 2 }; // Asumiendo que el ancho es 640
    SDL_RenderFillRect(renderer, &border_top); // Dibujar el borde superior

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF); // Color magenta
    SDL_Rect border_left = { 0, 0, 2, 480 }; // Asumiendo que la altura es 480
    SDL_RenderFillRect(renderer, &border_left); // Dibujar el borde izquierdo
}

SDL_Renderer* init_graphics() {
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

    // Try to detect if we're running in framebuffer mode
    const char* current_driver = SDL_GetCurrentVideoDriver();
    int is_framebuffer = (current_driver && (strcmp(current_driver, "fbcon") == 0 || strcmp(current_driver, "directfb") == 0));

    // Store original display mode
    SDL_DisplayMode originalMode;
    if (SDL_GetDisplayMode(0, 0, &originalMode) < 0) {
        fprintf(stderr, "Could not get display mode: %s\n", SDL_GetError());
    }

    // Set framebuffer config only if needed
    if (is_framebuffer) {
        // Framebuffer config (Raspberry Pi)
        setenv("SDL_VIDEODRIVER", "fbcon", 1);
        setenv("SDL_FBDEV", "/dev/fb0", 1);
    }

    // Create window with appropriate flags
    Uint32 window_flags = SDL_WINDOW_SHOWN;
    if (is_framebuffer) {
        window_flags |= SDL_WINDOW_FULLSCREEN;
    }

    g_window = SDL_CreateWindow("", 
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                640, 480,
                window_flags);
    if (!g_window) {
        fprintf(stderr, "Window creation error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return NULL;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer) {
        fprintf(stderr, "Renderer creation error: %s\n", SDL_GetError());
        SDL_DestroyWindow(g_window);
        TTF_Quit();
        SDL_Quit();
        return NULL;
    }

    return renderer;
}

void cleanup_graphics(SDL_Renderer *renderer) {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (g_window) {
        SDL_SetWindowFullscreen(g_window, 0);  // Disable fullscreen before destroying
        SDL_DestroyWindow(g_window);
    }
}

void draw_90s_button(SDL_Renderer *renderer, int x, int y, int w, int h, const char *text, int is_selected) {
    // Button background (changes if selected)
    SDL_SetRenderDrawColor(renderer, is_selected ? accent_color.r : 0x33, is_selected ? accent_color.g : 0x33, is_selected ? accent_color.b : 0x99, 0xFF);
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderFillRect(renderer, &rect); // Rellenar el fondo del botón

    // 3D border (thicker if selected)
    SDL_SetRenderDrawColor(renderer, is_selected ? 0xFF : 0x66, is_selected ? 0xFF : 0x66, 0x00, 0xFF); // Amarillo si está seleccionado
    SDL_Rect border = { x - 2, y - 2, w + 4, h + 4 };
    SDL_RenderFillRect(renderer, &border); // Rellenar el borde del botón

    // Button text
    draw_pixel_text(renderer, x + 10, y + h / 2 - 8, text, is_selected);
}

void draw_pixel_text(SDL_Renderer *renderer, int x, int y, const char *text, int is_selected) {
    // Load pixel font
    TTF_Font *font = TTF_OpenFont("assets/fonts/PerfectDOSVGA437.ttf", 16);
    if (!font) {
        fprintf(stderr, "Font load error: %s\n", TTF_GetError());
        return;
    }

    SDL_Color text_color = { 0xF4, 0xF4, 0xF4, 0xFF }; // Blanco retro
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text, text_color);
    
    if (text_surface) {
        SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        if (!text_texture) {
            fprintf(stderr, "Error al crear la textura del texto: %s\n", SDL_GetError());
            SDL_FreeSurface(text_surface);
            TTF_CloseFont(font);
            return;
        }

        SDL_Rect dest_rect = { x, y, text_surface->w, text_surface->h };

        SDL_RenderCopy(renderer, text_texture, NULL, &dest_rect);

        SDL_DestroyTexture(text_texture);
        SDL_FreeSurface(text_surface);
    }

    TTF_CloseFont(font);
}