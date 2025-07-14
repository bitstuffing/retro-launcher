#include "menu.h"
#include "graphics.h"
#include <stdlib.h>

void draw_menu(SDL_Renderer *renderer, int selected_option) {
    draw_arcade_background(renderer);
    draw_arcade_title(renderer, "Retro Launcher");
    
    const char *options[OPTION_COUNT] = {
        "Retro Emulation",
        "IPTV",
        "X Desktop",
        "Settings",
        "Quit"
    };

    for (int i = 0; i < OPTION_COUNT; i++) {
        draw_90s_button(renderer, 200, 100 + i * 60, 200, 50, options[i], (i == selected_option));
    }

    SDL_RenderPresent(renderer);
}

void execute_option(SDL_Renderer *renderer, MenuOption option) {
    // create a surface with the same format as 'screen' (to avoid screen permissions issues)
    SDL_Texture *screenshot = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 640, 480);
    if (!screenshot) {
        fprintf(stderr, "Error al crear la textura para el screenshot: %s\n", SDL_GetError());
        return;
    }

    SDL_SetRenderTarget(renderer, screenshot);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, NULL, 0); // Leer los píxeles del renderer

    SDL_SetRenderTarget(renderer, NULL);

    pixelate(renderer, screenshot, 15, 4, 1);

    switch (option) {
        case OPTION_EMUSTATION: system("emulationstation &"); break;
        case OPTION_INTERNET:   system("./scripts/internet.sh &"); break;
        case OPTION_XSESSION:   system("startx &"); break;
        case OPTION_SETTINGS:   system("./scripts/settings.sh &"); break;
        case OPTION_QUIT:       exit(0);
        default:                break;
    }

    SDL_DestroyTexture(screenshot);
}