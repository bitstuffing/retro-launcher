#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>

// Menu options
typedef enum {
    OPTION_EMUSTATION,  // 0
    OPTION_INTERNET,    // 1
    OPTION_XSESSION,    // 2
    OPTION_SETTINGS,    // 3
    OPTION_QUIT,        // 4
    OPTION_COUNT        // 5 (total number of options)
} MenuOption;

// Draws the complete menu
void draw_menu(SDL_Renderer *screen, int selected_option);

// Executes the selected option
void execute_option(SDL_Renderer *screen, MenuOption option);

#endif