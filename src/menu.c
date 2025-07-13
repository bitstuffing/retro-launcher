#include "menu.h"
#include "graphics.h"
#include <stdlib.h>

void draw_menu(SDL_Surface *screen, int selected_option) {
    draw_arcade_background(screen);
    draw_arcade_title(screen, "Retro Launcher");
    
    const char *options[OPTION_COUNT] = {
        "Retro Emulation",
        "IPTV",
        "X Desktop",
        "Settings",
        "Quit"
    };

    for (int i = 0; i < OPTION_COUNT; i++) {
        draw_90s_button(screen, 200, 100 + i * 60, 200, 50, options[i], (i == selected_option));
    }

    SDL_Flip(screen);
}

void execute_option(MenuOption option) {
    switch (option) {
        case OPTION_EMUSTATION: system("emulationstation &"); break;
        case OPTION_INTERNET:   system("./scripts/internet.sh &"); break;
        case OPTION_XSESSION:   system("startx &"); break;
        case OPTION_SETTINGS:   system("./scripts/settings.sh &"); break;
        case OPTION_QUIT:       exit(0);
        default:                break;
    }
}