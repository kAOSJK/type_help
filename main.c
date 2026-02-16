#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>

#include "terminal.h"
#include "terminal_renderer.h"

#define POINTS_COUNT 200
#define MIN_PIXELS_PER_SECOND 10
#define MAX_PIXELS_PER_SECOND 20

static SDL_Window *window = NULL;
static int win_w = 0;
static int win_h = 0;
static SDL_Renderer *renderer = NULL;
static Uint64 last_time = 0;
static SDL_FPoint points[POINTS_COUNT];
static float points_speeds[POINTS_COUNT];

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    int i;

    SDL_SetAppMetadata("TYPE: HELP", "0.1", "com.edgar.typehelp");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couln't initialize SDL: %s", SDL_GetError()); 
        return SDL_APP_FAILURE;
    }

    int *wh = open_terminal_font();
    if (wh == NULL)
    {
        SDL_Log("Couln't open terminal font");
        return SDL_APP_FAILURE;
    }
    
    win_w = *(wh);
    win_h = *(wh+1);

    window = SDL_CreateWindow("Terminal", win_w, win_h, 0);
    if (window == NULL)
    {
        SDL_Log("Couldn't create window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL)
    {
        SDL_Log("Couldn't create renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    SDL_SetRenderLogicalPresentation(renderer, win_w, win_h, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    app_init_terminal(renderer);
    
    for (i = 0; i < SDL_arraysize(points); i++)
    {
        points[i].x = SDL_randf() * ((float)win_w);
        points[i].y = SDL_randf() * ((float)win_h);
        points_speeds[i] = MIN_PIXELS_PER_SECOND + (SDL_randf() * (MAX_PIXELS_PER_SECOND - MIN_PIXELS_PER_SECOND));
    }

    last_time = SDL_GetTicks();

    SDL_StartTextInput(window);
    
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }

    app_event_terminal(event);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    const Uint64 now = SDL_GetTicks();
    const float elapsed = ((float)(now - last_time)) / 1000.0f;
    int i;

    SDL_FRect rect;
    rect.x = rect.y = 0;
    rect.w = rect.h = win_h;

    for (i = 0; i < SDL_arraysize(points); i++)
    {
        const float distance = elapsed * points_speeds[i];
        points[i].x += distance;
        points[i].y += distance;

        if ((points[i].x >= win_w) || (points[i].y >= win_h))
        {
            if (SDL_rand(2))
            {
                points[i].x = SDL_randf() * ((float)win_w);
                points[i].y = 0.0f;
            }
            else
            {
                points[i].x = 0.0f;
                points[i].y = SDL_randf() * ((float)win_h);
            }

            points_speeds[i] = MIN_PIXELS_PER_SECOND + (SDL_randf() * (MAX_PIXELS_PER_SECOND - MIN_PIXELS_PER_SECOND));
        }
    }

    last_time = now;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderPoints(renderer, points, SDL_arraysize(points));

    app_render_terminal(renderer);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    app_quit_terminal();

    SDL_StopTextInput(window);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
}
