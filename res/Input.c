#include <SDL.h>
#include "Input.h"
int ReconnaissanceTouche(SDL_Event ev, char no)
{
    if (ev.type == SDL_WINDOWEVENT
        && ev.window.event == SDL_WINDOWEVENT_CLOSE)
    {
        ev.type = SDL_QUIT;
    }
    if (ev.type == SDL_QUIT)
    {
        return 1;
    }
    if (ev.type == SDL_KEYDOWN || (ev.type == SDL_KEYUP && !no))
    {
        switch (ev.key.keysym.sym)
        {
        case SDLK_UP:
            return 2;
            break;
        case SDLK_DOWN:
            return 3;
            break;
        case SDLK_LEFT:
            return 4;
            break;
        case SDLK_RIGHT:
            return 5;
            break;
        case SDLK_SPACE:
            return 6;
            break;
        case SDLK_BACKSPACE:
            return 7;
            break;
        case SDLK_x:
            return 8;
        case SDLK_RETURN:
            return 9;
            break;
        }
    }
    return 0;
}

int Touche()
{
    SDL_Event ev;
    int event = 0;
    do
    {
        SDL_WaitEvent(&ev);
        event = ReconnaissanceTouche(ev, 1);
    } while (event == 0);
    return event;
}

void UpdateTouche(char* touches)
{
    SDL_Event ev;
    Uint32 time = SDL_GetTicks();
    int n = 0;
    int event = 0;
    do
    {
        SDL_PollEvent(&ev);
        n = ReconnaissanceTouche(ev, 0);
        if (n > 0)
        {
            if (ev.type != SDL_KEYUP)
            {
                touches[n - 1] = 1;
            }
            else
            {
                touches[n - 1] = 0;
            }
        }
    } while (SDL_GetTicks() < time + 30);
}

int TextInput(SDL_Renderer* renderer, char* consigne, size_t length, char** result, char* letters, char* lettersprites)
{
    SDL_Event event;
    char exit = 0;
    char choix = 1;
    size_t len = 0;
    size_t i = 0;
    char* string = malloc(sizeof(char) * (length+1));
    if (!string)
    {
        return 3;
    }
    if (!(*result))
    {
        len = 0;
    }
    else
    {
        while (i < length && choix)
        {
            string[i] = (*result)[i];
            choix = (string[i] != 0);
            i++;
        }
        len = i - 1;
    }
    while (i < length)
    {
        string[i] = 0;
        i++;
    }
    cadre(renderer, 6, 200, 1012, 84, 0, 0, 255);
    rect(renderer, 14, 208, 996, 68, 0, 0, 0);
    text(renderer, 18, 212, consigne, letters, lettersprites, 255, 255, 255);
    while (!exit)
    {
        rect(renderer, 14, 244, 996, 32, 0, 0, 0);
        text(renderer, 18,244,string+(len-31)*(len>31), letters, lettersprites, 255, 255, 255);
        SDL_RenderPresent(renderer);
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT)
        {
            exit = 1;
            free(string);
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_BACKSPACE && len)
            {
                len--;
                string[len] = 0;
            }
            if (event.key.keysym.sym == SDLK_RETURN && len)
            {
                exit = 2;
                *result = string;
            }
        }
        else if (event.type == SDL_TEXTINPUT && len<length)
        {
            string[len] = *(event.text.text);
            len++;
        }
    }
    return exit;
}
