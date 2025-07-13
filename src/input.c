#include "menu.h"
#include "graphics.h"
#include "input.h"

void update_menu(InputAction action, int *selected_option) {
    switch (action) {
        case INPUT_UP:
            *selected_option = (*selected_option - 1 + OPTION_COUNT) % OPTION_COUNT;
            break;
        case INPUT_DOWN:
            *selected_option = (*selected_option + 1) % OPTION_COUNT;
            break;
        case INPUT_SELECT:
            // TODO
            break;
        default:
            break;
    }
}

// get_input_action() function to handle input events
InputAction get_input_action() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return INPUT_BACK;  // quit
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP: return INPUT_UP;
                case SDLK_DOWN: return INPUT_DOWN; 
                case SDLK_RETURN: return INPUT_SELECT;
                case SDLK_ESCAPE: return INPUT_BACK;
                default: return INPUT_NONE;
            }
        }
        if (event.type == SDL_JOYBUTTONDOWN) {
            if (event.jbutton.button == 0) return INPUT_SELECT;  // A
            if (event.jbutton.button == 1) return INPUT_BACK; // B
            if (event.jbutton.button == 4) return INPUT_UP;
            if (event.jbutton.button == 5) return INPUT_DOWN;
        }
    }
    return INPUT_NONE;  // No input detected
}

// init_input() function to initialize input handling
void init_input() {
    if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0) {
        fprintf(stderr, "Error initializing joystick: %s\n", SDL_GetError());
    } else {
        SDL_JoystickEventState(SDL_ENABLE);
        if (SDL_NumJoysticks() > 0) {
            SDL_Joystick *joystick = SDL_JoystickOpen(0);
            if (!joystick) {
                fprintf(stderr, "Error opening joystick: %s\n", SDL_GetError());
            } else {
                printf("Joystick initialized: %s\n", SDL_JoystickName(joystick));
            }
        } else {
            printf("No joysticks found.\n");
        }
    }
}