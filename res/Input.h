#pragma once

#ifndef Input_h
#define Input_h
#include <SDL.h>

int ReconnaissanceTouche(SDL_Event ev, char no);
int Touche();
void UpdateTouche(char* touches);
int TextInput(SDL_Renderer* renderer, char* consigne, size_t length, char** result, char* letters, char* lettersprites);

#endif