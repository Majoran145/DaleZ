#pragma once
#ifndef Editor_h
#define Editor_h
#include <SDL.h>
#include "Input.h"
#include "Print.h"

int ColorChoice(SDL_Renderer* renderer, int* colors, char* letters, char* lettersprites);
int SpriteModifier(SDL_Renderer* renderer, char* sprite, int* colors, size_t size, char* letters, char* lettersprites);
int SpriteEditor(SDL_Renderer* renderer, char** sprites, int** colors, size_t* nombresprite, size_t size, char* letters, char* lettersprites);
int EditorMenu(SDL_Renderer* renderer, char* letters, char* spriteletters, char* name, char* title, char newlevel);
#endif