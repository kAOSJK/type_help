#include <SDL3/SDL.h>
#include <stdlib.h>

#include "terminal_input.h"
#include "terminal_row.h"
#include "terminal_interpreter.h"

void event_terminal(SDL_Event *event)
{
    if (event->key.key == SDLK_RETURN &&
        event->key.down == true)
    {
        const Row *row = append_terminal_row(row_input.str, 0);
        reset_terminal_row_input();
        terminal_interpret(row);
    }
    else if (event->type == SDL_EVENT_TEXT_INPUT)
    {
        add_terminal_row_input(*(event->text.text));
    }
    else if (event->key.key == SDLK_BACKSPACE &&
        event->key.down == true)
    {
        remove_terminal_row_input(); 
    }
}
