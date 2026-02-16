#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL3/SDL_stdinc.h>

#include "terminal_interpreter.h"
#include "terminal_row.h"

void dispatch_use_cmd(const char *str);
void append_terminal_cmd(char *str);
void append_terminal_error(const char *str);

void terminal_interpret(const Row *row)
{
    if (*(row->str) == '\0')
    {
        return;
    }

    if (strcmp(row->str, "clear") == 0)
    {
        clear_terminal_row();
        return;
    }

    if (strcmp(row->str, "cat report01.txt") == 0)
    {
        dispatch_use_cmd(REPORT01);
        return;
    }

    if (strcmp(row->str, "cat report02.txt") == 0)
    {
        dispatch_use_cmd(REPORT02);
        return;
    }

    if (strcmp(row->str, "cat report03.txt") == 0)
    {
        dispatch_use_cmd(REPORT03);
        return;
    }
    
    if (strcmp(row->str, "cat report04.txt") == 0)
    {
        dispatch_use_cmd(REPORT04);
        return;
    }
    
    if (strcmp(row->str, "cat report05.txt") == 0)
    {
        dispatch_use_cmd(REPORT05);
        return;
    }


    append_terminal_error(row->str);
}

void dispatch_use_cmd(const char *cmd)
{
    char buffer[1024];
    SDL_strlcpy(buffer, cmd, sizeof(buffer));
    append_terminal_cmd(buffer);
}

void append_terminal_cmd(char *cmd)
{
    char **saveptr = (char **)malloc(sizeof(char *));
    char *str = SDL_strtok_r(cmd, "\n", saveptr);
    while (str != NULL)
    {
        append_terminal_row(str, 1);
        str = SDL_strtok_r(NULL, "\n", saveptr);
    }
}

void append_terminal_error(const char *str)
{
    char buffer[100];
    char begin[] = "bash: ";
    char end[] = ": command not found";

    SDL_strlcpy(buffer, begin, sizeof(buffer));
    SDL_strlcat(buffer, str, sizeof(buffer));
    SDL_strlcat(buffer, end, sizeof(buffer));
    
    append_terminal_row(buffer, 1);
}
