/*Chargement de la SDL, de l'écran, et lancement de la partie*/

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "Print.h"
#include "Input.h"
#include "Editor.h"
#include <io.h>

size_t filelist(char * type, char*** list, size_t count)
{
    struct _finddata_t c_file;
    intptr_t hFile;
    size_t size = count;
    do
    {
        char* test = NULL;
        if (*list)
            test = (*list)[0];
        size_t i = 0;
        while (i<count && i<size)
        {
            free((*list)[i*2]);
            free((*list)[i*2+1]);
            i++;
        }
        free((*list));
        count = size;
        size = 0;
        (*list) = malloc(sizeof(char*) * count * 2);
        if ((hFile = _findfirst(type, &c_file)) == -1L|| !(*list))
            return 0;
        do
        {
            if (size < count)
            {
                char* stringtitle = malloc(sizeof(char) * 301);
                char* stringauthor = malloc(sizeof(char) * 101);
                if (!stringtitle || !stringauthor)
                {
                    free(stringtitle);
                    free(stringauthor);
                    return size;
                }
                size_t i = 0;
                while (c_file.name[i] != '[')
                {
                    stringtitle[i] = c_file.name[i];
                    i++;
                }
                stringtitle[i] = 0;
                size_t j = 0;
                i++;
                while (c_file.name[i+j] != ']')
                {
                    stringauthor[j] = c_file.name[i+j];
                    j++;
                }
                stringauthor[j] = 0;
                (*list)[size * 2] = stringtitle;
                (*list)[size * 2 + 1] = stringauthor;
            }
            char* title = (*list)[size * 2];
            char* author = (*list)[size * 2 + 1];
            size++;
            int x = 0;
        } while (_findnext(hFile, &c_file) == 0);
        _findclose(hFile);
    } while (count != size);
    return size;
}

int FileInformation(SDL_Renderer* renderer, char* title, char* name, char* letters, char* lettersprites)
{
    cadre(renderer, 6, 200, 1012, 148, 0, 255, 0);
    size_t i1 = 0;
    size_t i2 = 0;
    while (title[i1])
    {
        i1++;
    }
    while (name[i2])
    {
        i2++;
    }
    size_t b1 = 0;
    size_t b2 = 0;
    char target = 0;
    int t = 0;
    while (t != 1 && t != 6 && t != 9)
    {
        rect(renderer, 14, 208, 996, 132, 0, 0, 0);
        text(renderer, 18, 212, "Projet :", letters, lettersprites, 255, 255*target, 255*target);
        text(renderer, 18, 244, title+b1, letters, lettersprites, 255, 255, 255);
        text(renderer, 18, 276, "Auteur :", letters, lettersprites, 255, 255*!target, 255*!target);
        text(renderer, 18, 308, name + b2, letters, lettersprites, 255, 255, 255);
        SDL_RenderPresent(renderer);
        t = Touche();
        if (t == 2 || t == 3)
        {
            target = !target;
        }
        if (t == 4)
        {
            if (!target)
            {
                b1 -= (b1 > 0);
            }
            else
            {
                b2 -= (b2 > 0);
            }
        }
        if (t==5)
        {
            if (!target)
            {
                b1 += (b1 + 31 < i1);
            }
            else
            {
                b2 += (b2 + 31 < i2);
            }
        }
    }
    return (t==1);
}

int FileChoice(SDL_Renderer* renderer, char* type, char* letters, char* lettersprites, char** finaltitle, char** finalauthor)
{
    rect(renderer, 0, 0, 1024, 704, 0, 0, 0);
    cadre(renderer, 4, 4, 1016, 54, 255, 0, 0);
    cadre(renderer, 4, 72, 1016, 500, 0, 0, 255);
    cadre(renderer, 4, 584, 724, 116, 255, 0, 0);
    cadre(renderer, 732, 584, 288, 116, 0, 0, 255);
    text(renderer, 190, 16, "SELECTION DE FICHIER", letters, lettersprites, 255, 255, 255);
    text(renderer, 16, 596, "ENTREE - VALIDER", letters, lettersprites, 255, 255, 255);
    text(renderer, 16, 628, "ESPACE - INFORMATIONS", letters, lettersprites, 255, 255, 255);
    text(renderer, 16, 660, "BACKSPACE - ACTUALISER", letters, lettersprites, 255, 255, 255);
    text(renderer, 744, 596, "PAGE", letters, lettersprites, 255, 255, 255);
    int x = 0;
    int t = 0;
    char** list = NULL;
    size_t count = filelist(type, &list, 0);
    size_t page = 0;
    size_t maxpage = ((count - 1) / 15 + 1)*(count!=0);
    while (t != 9 && t!=1)
    {
        int y = 0;
        rect(renderer, 12, 80, 1000, 484, 0, 0, 0);
        rect(renderer, 740, 624, 272, 68, 0, 0, 0);
        printnumber(renderer, 744, 628, page + (count != 0), 0, letters, lettersprites, 255, 255, 255);
        printnumber(renderer, 744, 660, maxpage, 0, letters, lettersprites, 255, 255, 255);
        while (y < 15 && page * 15 + y < count)
        {
            text(renderer, 20, 84 + y * 32, list[(page * 15 + y) * 2], letters, lettersprites, 255, 255*(y!=x), 255*(y!=x));
            y++;
        }
        if (count == 0)
        {
            text(renderer, 20, 308, "Aucun fichier detecte.",letters, lettersprites, 255,255,255);
        }
        SDL_RenderPresent(renderer);
        t = Touche();
        if (t == 2 && (page*15+x))
        {
            x--;
        }
        if (t == 3)
        {
            x++;
        }
        if (t == 4 && page)
        {
            page--;
        }
        if (t == 5)
        {
            page++;
        }
        if (t == 6)
        {
            size_t g = (page * 15 + x)*2;
            t = FileInformation(renderer, list[g], list[g + 1], letters, lettersprites);
            cadre(renderer, 4, 72, 1016, 500, 0, 0, 255);
        }
        if (t == 7)
        {
            rect(renderer, 12, 80, 1000, 484, 0, 0, 0);
            count = filelist(type, &list, count);
            maxpage = (count-1) / 15 +1 ;
        }
        if (x<0)
        {
            page--;
            x = 14;
        }
        if (x > 14)
        {
            page++;
            x = 0;
        }
        if (page * 15 + x >= count)
        {
            page = maxpage - 1;
            x = (count - 1) % 15;
        }
        if (!count)
        {
            page = 0;
            maxpage = 0;
            x = 0;
        }
    }
    if (count)
    {
        size_t target = page * 15 + x;
        *finaltitle = list[target * 2];
        *finalauthor = list[target * 2 + 1];
        size_t i = 0;
        while (i < count)
        {
            if (i != target)
            {
                free(list[i * 2]);
                free(list[i * 2 + 1]);
            }
            i++;
        }
    }
    else
    {
        *finaltitle = NULL;
        *finalauthor = NULL;
    }
    free(list);
    return (t==1);
}

int IntWriting(int* list, FILE* file, int size)
{
    int a = 0;
    while (a < size)
    {
        fprintf(file, "%d ", list[a]);
        a++;
    }
    fputc('\n', file);
    return a;
}

int CharWriting(char* list, FILE* file, int size)
{
    int a = 0;
    while (a < size)
    {
        fprintf(file, "%d", list[a]);
        a++;
    }
    fputc('\n', file);
    return a;
}

int CharLecture(char* list, FILE* file, int a, char IsNumber, size_t l)
{
    char b = fgetc(file);
    while (b != '\n' && b!=EOF && a < l)
    {
        list[a] = b - 48 * IsNumber;
        b = fgetc(file);
        a++;
    }
    if (b)
        return a;
    return -1;
}

int IntLecture(int* list, FILE* file, int a, size_t l)
{
    char b = fgetc(file);
    while (b != '\n' && b != EOF && a<l)
    {
        list[a] = 0;
        while (b != ' ')
        {
            list[a] = list[a] * 10 + b - 48;
            b = fgetc(file);
        }
        b = fgetc(file);
        a++;
    }
    if (b)
        return a;
    return -1;
}

int EditorArea(SDL_Renderer* renderer, char* letters, char* spriteletters)
{
    //Menu de l'espace editeur
    int action = 1;
    int t = 0;
    while (action != 3 && t!=1)
    {
        action = 1;
        rect(renderer, 0, 0, 1024, 704, 0, 0, 0);
        cadre(renderer, 300, 0, 420, 70, 255, 0, 0);
        text(renderer, 320, 20, "Zone Editeur", letters, spriteletters, 255, 255, 255);
        text(renderer, 100, 300, "Charger un Niveau", letters, spriteletters, 255, 255, 255);
        text(renderer, 100, 400, "Creer un Niveau", letters, spriteletters, 255, 255, 255);
        text(renderer, 100, 500, "Retour", letters, spriteletters, 255, 255, 255);
        t = 0;
        while (t != 9 && t != 6 && t != 1)
        {
            cadre(renderer, 80, 180 + action * 100, 600, 70, 0, 0, 255);
            SDL_RenderPresent(renderer);
            cadre(renderer, 80, 180 + action * 100, 600, 70, 0, 0, 0);
            t = Touche();
            if (t == 2 && action != 1)
            {
                action--;
            }
            if (t == 3 && action != 3)
            {
                action++;
            }
        }
        if (t != 1)
        {
            char* title = NULL;
            char* name = NULL;
            if (action == 1)
            {
                t = FileChoice(renderer, "edit/*.edlz", letters, spriteletters, &title, &name);
                if (!title || !name)
                {
                    t = 3;
                }
            }
            if (action == 2)
            {
                t = TextInput(renderer, "Entrez le nom du projet :", 300, &title, letters, spriteletters);
                if (t == 2)
                {
                    t = TextInput(renderer, "Entrez votre pseudo :", 100, &name, letters, spriteletters);
                }
            }
            if (action < 3 && t!=1 && t!=3)
            {
                //Chargement des données
                //SpriteEditor(renderer, &sprites8, &colors8, numbersprites, 8, letters, spriteletters);
                t = EditorMenu(renderer, letters, spriteletters, name, title, (t==2));
            }
            free(title);
            free(name);
        }
    }
    return (t==1);
}

int main(int argc, char** argv)
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;
    window = SDL_CreateWindow("DaleZ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 704, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderClear(renderer);
    cadre(renderer, 100, 100, 824, 504, 255, 0, 0);
    //Chargement de la police
    FILE* defaultfile = fopen("settings.ddlz", "r");
    char* letters = malloc(sizeof(char) * 47);
    char* spriteletters = malloc(sizeof(char) * 47 * 64);
    if (!defaultfile || !letters || !spriteletters)
    {
        return -1;
    }
    CharLecture(letters, defaultfile, 0, 0, 47);
    CharLecture(spriteletters, defaultfile, 0, 1, 47*64);
    fclose(defaultfile);

    rect(renderer, 0, 0, 1024, 704, 0, 0, 0);

    //Menu principal
    int mode = 1;
    int t = 0;
    while (mode != 3 && t!=1)
    {
        mode = 1;
        rect(renderer, 0, 0, 1024, 704, 0, 0, 0);
        text(renderer, 432, 20, "DaleZ", letters, spriteletters, 255, 255, 255);
        text(renderer, 336, 300, "Zone Joueur", letters, spriteletters, 255, 255, 255);
        text(renderer, 320, 400, "Zone Editeur", letters, spriteletters, 255, 255, 255);
        text(renderer, 416, 500, "Fermer", letters, spriteletters, 255, 255, 255);
        t = 0;
        while (t != 9 && t!= 6 && t != 1)
        {
            cadre(renderer, 300, 180 + mode * 100,420,70,255,0,0);
            SDL_RenderPresent(renderer);
            cadre(renderer, 300, 180 + mode * 100, 420, 70, 0, 0, 0);
            t = Touche();
            if (t == 2 && mode != 1)
            {
                mode--;
            }
            if (t == 3 && mode != 3)
            {
                mode++;
            }
        }
        if (mode == 2)
        {
            t=EditorArea(renderer, letters, spriteletters);
        }
    }
    return 0;
}
