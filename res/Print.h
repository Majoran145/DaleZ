#pragma once
#ifndef Print_h
#define Print_h
#include "Input.h"
#include <SDL.h>
void rect(SDL_Renderer* renderer, int x, int y, int w, int h, int r, int g, int b);

void cadre(SDL_Renderer* renderer, int x, int y, int w, int h, int r, int g, int b);

void sprite(SDL_Renderer* renderer, int x, int y, char* sprite, int* colors, int size);
void text(SDL_Renderer* renderer, int x, int y, char* t, char* letters, char* lettersprites, int r, int g, int b);
void printnumber(SDL_Renderer* renderer, int x, int y, int t, int l, char* letters, char* lettersprites, int r, int g, int b);
int FileError(SDL_Renderer* renderer, char* letters, char* lettersprites);

#endif

