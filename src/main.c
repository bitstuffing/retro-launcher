#include "graphics.h"
#include "input.h"
#include "menu.h"

int main() {
    SDL_Surface *screen = init_graphics();
    init_input();
    
    int selected_option = 0;
    int running = 1;
    draw_menu(screen, selected_option);

    while (running) {
        InputAction action = get_input_action();
        
        if (action == INPUT_UP || action == INPUT_DOWN) {
            update_menu(action, &selected_option);
            draw_menu(screen, selected_option); 
        }

        if (action == INPUT_SELECT) {
            execute_option(selected_option);
        }
        
        SDL_Delay(16); // 60 FPS
    }
    
    TTF_Quit();
    SDL_Quit();
    return 0;
}