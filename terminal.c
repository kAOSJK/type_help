#include <stdlib.h>

#include "terminal.h"
#include "terminal_renderer.h"
#include "terminal_input.h"
#include "terminal_row.h"
#include "terminal_interpreter.h"

#define USERNAME "edgar"
#define HOSTNAME "exp9"

int app_init_terminal(SDL_Renderer *renderer)
{
    if (init_terminal_renderer(renderer) == 1)
    {
        return 1;
    }

    reset_terminal_row_input();

    return 0;
}

int app_event_terminal(SDL_Event *event)
{
    event_terminal(event);

    return 0;
}

int app_render_terminal(SDL_Renderer *renderer)
{
    if (render_terminal(renderer, 480) == 1)
    {
        return 1;
    }

    return 0;
}

void app_quit_terminal()
{
    quit_terminal_renderer();
}
