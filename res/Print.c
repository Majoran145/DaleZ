#include "Print.h"

void rect(SDL_Renderer* renderer, int x, int y, int w, int h, int r, int g, int b)
{
    SDL_Rect rect;
    rect.x = x; rect.y = y; rect.w = w; rect.h = h;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void cadre(SDL_Renderer* renderer, int x, int y, int w, int h, int r, int g, int b)
{
    rect(renderer, x + 4, y, w - 8, 8, r, g, b);
    rect(renderer, x + 4, y + h - 8, w - 8, 8, r, g, b);
    rect(renderer, x + w - 8, y + 4, 8, h - 8, r, g, b);
    rect(renderer, x , y + 4, 8, h - 8, r, g, b);
}

void sprite(SDL_Renderer* renderer, int x, int y, char* sprite, int* colors, int size)
{
    char* color = sprite;
    int dy = 0;
    while (dy < size)
    {
        int dx = 0;
        while (dx < size)
        {
            if (*color)
            {
                char espion = (*color - 1) * 3;
                rect(renderer, x + dx * 4, y + dy * 4, 4, 4, colors[(*color-1) * 3], colors[(*color - 1) * 3 + 1], colors[(*color - 1) * 3 + 2]);
            }
            dx++;
            color++;
        }
        dy++;
    }
}

void text(SDL_Renderer* renderer, int x, int y, char* t, char* letters, char* lettersprites, int r, int g, int b)
{
    int* colors[] = { r,g,b };
    while (*t && x<994)
    {
        size_t i = 0;
        char c = *t;
        if (c >= 'a' && c <= 'z')
        {
            c += 'A' - 'a';
        }
        while (c != letters[i] && i<46)
        {
            i++;
        }
        sprite(renderer, x, y, lettersprites+(i * 64), colors, 8);
        x += 32;
        t++;
    }
}

void printnumber(SDL_Renderer* renderer, int x, int y, int t, int l, char* letters, char* lettersprites, int r, int g, int b)
{
    if (!l)
    {
        int t2 = t;
        while (t2)
        {
            t2 /= 10;
            l++;
        }
    }
    char* string = malloc(sizeof(char) * (l + 1));
    if (string)
    {
        string[l] = 0;
        while (l)
        {
            l--;
            string[l] = t % 10 + 48;
            t /= 10;
        }
        text(renderer, x, y, string, letters, lettersprites, r, g, b);
    }
    free(string);
}

int FileError(SDL_Renderer* renderer, char* letters, char* lettersprites)
{
    cadre(renderer, 62, 200, 900, 270, 255, 0, 0);
    rect(renderer, 70, 208, 884, 254, 0, 0, 0);
    text(renderer, 82, 220, "Le fichier n'a pas pu etre", letters, lettersprites, 255, 255, 255);
    text(renderer, 82, 252, "charge.", letters, lettersprites, 255, 255, 255);
    text(renderer, 82, 284, "Causes possibles :", letters, lettersprites, 255, 255, 255);
    text(renderer, 82, 316, "- Le fichier n'existe plus.", letters, lettersprites, 255, 255, 255);
    text(renderer, 82, 348, "- La RAM est trop faible.", letters, lettersprites, 255, 255, 255);
    text(renderer, 82, 380, "- Le fichier ne correspond", letters, lettersprites, 255, 255, 255);
    text(renderer, 82, 412, "  pas au format actuel.", letters, lettersprites, 255, 255, 255);
    int t = 0;
    SDL_RenderPresent(renderer);
    while (t == 0)
    {
        t = Touche();
    }
    return(t == 1);
}