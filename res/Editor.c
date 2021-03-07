#pragma once
#include <SDL.h>
#include <stdio.h>
#include "Input.h"
#include "Print.h"
#include "Editor.h"
#include <io.h>

int ColorChoice(SDL_Renderer* renderer, int* colors, char* letters, char* lettersprites)
{
	cadre(renderer, 350, 150, 324, 404, 255, 0, 0);
	rect(renderer, 358, 158, 308, 390, 0, 0, 0);
	rect(renderer, 368, 350, 96, 50, 255, 0, 0);
	rect(renderer, 464, 350, 96, 50, 0, 255, 0);
	rect(renderer, 560, 350, 96, 50, 0, 0, 255);
	text(renderer, 368, 474, "ENTREE", letters, lettersprites, 255, 255, 255);
	text(renderer, 368, 506, "VALIDER", letters, lettersprites, 255, 255, 255);
	int t = 0;
	int x = 0;
	while (t != 9 && t!=1)
	{
		rect(renderer, 368, 180, 288, 140, colors[0], colors[1], colors[2]);
		rect(renderer, 368+32*x, 436, 32, 4, 255, 255, 255);
		rect(renderer, 368, 400, 288, 32, 0, 0, 0);
		printnumber(renderer, 368, 404, colors[0], 3, letters, lettersprites, 255, 0, 0);
		printnumber(renderer, 464, 404, colors[1], 3, letters, lettersprites, 0, 255, 0);
		printnumber(renderer, 560, 404, colors[2], 3, letters, lettersprites, 0, 0, 255);
		SDL_RenderPresent(renderer);
		t = Touche();
		rect(renderer, 368 + 32 * x, 436, 32, 4, 0, 0, 0);
		if (t == 4 && x)
		{
			x--;
		}
		if (t == 5 && x<8)
		{
			x++;
		}
		if (t == 3 || t == 2)
		{
			int delta = 100;
			if (x % 3 == 2)
			{
				delta = 1;
			}
			if (x % 3 == 1)
			{
				delta = 10;
			}
			if (t == 3)
			{
				delta *= -1;
			}
			colors[x / 3]+=delta;
			if (colors[x / 3] < 0)
			{
				colors[x / 3] = 0;
			}
			if (colors[x / 3] > 255)
			{
				colors[x / 3] = 255;
			}
			int result = colors[x / 3];
			result += 0;
		}
	}
	return (t == 1);
}

int SpriteModifier(SDL_Renderer* renderer, char* sprite, int* colors, size_t size, char* letters, char* lettersprites)
{
	char actualcolor = 0;
	size_t pixelsize = 320 / size;
	int t = 0;
	while (t != 9 && t!=1)
	{
		rect(renderer, 0, 0, 1024, 704, 100, 100, 100);
		text(renderer, 500, 8, "ESPACE", letters, lettersprites, 255, 255, 255);
		text(renderer, 500, 40, "APPLIQUER LA", letters, lettersprites, 255, 255, 255);
		text(renderer, 500, 72, "COULEUR", letters, lettersprites, 255, 255, 255);
		text(renderer, 500, 168, "BACKSPACE", letters, lettersprites, 255, 255, 255);
		text(renderer, 500, 200, "MODIFIER UNE", letters, lettersprites, 255, 255, 255);
		text(renderer, 500, 232, "COULEUR", letters, lettersprites, 255, 255, 255);
		text(renderer, 500, 328, "ENTREE", letters, lettersprites, 255, 255, 255);
		text(renderer, 500, 360, "VALIDER", letters, lettersprites, 255, 255, 255);
		char* color = sprite;
		size_t dy = 0;
		while (dy < size)
		{
			size_t dx = 0;
			while (dx < size)
			{
				if (*color)
				{
					rect(renderer, 8+dx * pixelsize, 8+dy * pixelsize, pixelsize, pixelsize, colors[(*color-1) * 3], colors[(*color - 1) * 3 + 1], colors[(*color - 1) * 3 + 2]);
				}
				dx++;
				color++;
			}
			dy++;
		}
		dy = 0;
		while (dy < 9)
		{
			rect(renderer, 400, 48 + dy * 40, 30, 30, colors[dy * 3], colors[dy * 3 + 1], colors[dy * 3 + 2]);
			dy++;
		}
		cadre(renderer, 392, actualcolor * 40, 46, 46, 0, 0, 255);
		SDL_RenderPresent(renderer);
		t = Touche();
		if (t == 2 && actualcolor)
		{
			actualcolor--;
		}
		if (t == 3 && actualcolor < 9)
		{
			actualcolor++;
		}
		if (t == 7 && actualcolor)
		{
			t = ColorChoice(renderer, colors + (actualcolor-1) * 3,letters, lettersprites);
		}
		if (t == 6)
		{
			size_t x = 0;
			size_t y = 0;
			while (t != 9 && t!= 1)
			{
				rect(renderer, 0, 0, 336, 336, 100, 100, 100);
				color = sprite;
				dy = 0;
				while (dy < size)
				{
					size_t dx = 0;
					while (dx < size)
					{
						if (*color)
						{
							rect(renderer, 8 + dx * pixelsize, 8 + dy * pixelsize, pixelsize, pixelsize, colors[(*color - 1) * 3], colors[(*color - 1) * 3 + 1], colors[(*color - 1) * 3 + 2]);
						}
						dx++;
						color++;
					}
					dy++;
				}
				cadre(renderer, x * pixelsize, y * pixelsize, pixelsize+16, pixelsize+16, 255, 0, 0);
				SDL_RenderPresent(renderer);
				t = Touche();
				if (t == 2 && y)
				{
					y--;
				}
				if (t == 3 && y<size-1)
				{
					y++;
				}
				if (t == 4 && x)
				{
					x--;
				}
				if (t == 5 && x<size-1)
				{
					x++;
				}
				if (t == 6)
				{
					sprite[y * size + x] = actualcolor;
				}
			}
			t = (t==1);
		}
	}
	int couleur = colors[26];
	return (t==1);
}

int SpriteEditor(SDL_Renderer* renderer, char** sprites, int** colors, size_t* nombresprite, size_t size, char* letters, char* lettersprites) //Les couleurs par défaut des sprites. Elles ne sont pas mises dans le fichier de jeu final.
{
	size_t x = 0;
	size_t y = 0;
	size_t ycamera = 0;
	size_t ecart = 88;
	size_t xmax = 7;
	size_t ymax = 7;
	if (size == 8)
	{
		ecart = 56;
		xmax = 11;
		ymax = 10;
	}
	if (size == 32)
	{
		ecart = 152;
		xmax = 4;
		ymax = 4;
	}
	int t = 0;
	while (t!=9 && t!=1)
	{
		rect(renderer, 0, 0, 1024, 704, 50, 50, 50);
		cadre(renderer, 20 + x * ecart, 20 + y * ecart, ecart-8, ecart-8, 0, 0, 255);
		cadre(renderer, 660, 20 , 320, 632, 255, 0, 0);
		text(renderer, 680, 40, "ESPACE", letters, lettersprites, 255, 255, 255);
		text(renderer, 680, 72, "MODIFIER", letters, lettersprites, 255, 255, 255);
		text(renderer, 680, 104, "UN SPRITE", letters, lettersprites, 255, 255, 255);
		text(renderer, 680, 200, "BACKSPACE", letters, lettersprites, 255, 255, 255);
		text(renderer, 680, 232, "CREER UN", letters, lettersprites, 255, 255, 255);
		text(renderer, 680, 264, "SPRITE", letters, lettersprites, 255, 255, 255);
		text(renderer, 680, 366, "ENTRER", letters, lettersprites, 255, 255, 255);
		text(renderer, 680, 398, "VALIDER", letters, lettersprites, 255, 255, 255);
		size_t iy = ycamera;
		while (iy < ymax)
		{
			size_t ix = 0;
			while (ix < xmax)
			{
				if (iy * xmax + ix < *nombresprite)
				{
					int espion = iy * 7 + ix;
					sprite(renderer, ix * ecart + 28, (iy-ycamera) * ecart + 28, *sprites + (iy * xmax + ix) * size * size,*colors + (iy * xmax + ix) * 27, size);
				}
				ix++;
			}
			iy++;
		}
		SDL_RenderPresent(renderer);
		t = Touche();
		if (t == 3)
		{
			if (y + 1 == ymax)
			{
				ycamera++;
			}
			else
			{
				y++;
			}
		}
		if (t == 2 && y)
		{
			if (y == 1 && ycamera)
			{
				ycamera--;
			}
			else
			{
				y--;
			}
		}
		if (t == 4 && x)
		{
			x--;
		}
		if (t == 5 && x + 1 < xmax)
		{
			x++;
		}
		if (t == 6 && y * xmax + x < *nombresprite )
		{
			SpriteModifier(renderer, *sprites + (y* xmax +x)*size*size, *colors + (y * xmax + x) * 27, size, letters, lettersprites);
		}
		if (t == 7)
		{
			char* newsprites;
			int* newcolors;
			if (*nombresprite>0 && *sprites!=NULL && *colors!=NULL)
			{
				newsprites = realloc(*sprites, (*nombresprite+1) * sizeof(char) * size * size);
				newcolors = realloc(*colors, (*nombresprite+1) * sizeof(int) * 27);
			}
			else
			{
				newsprites = malloc(sizeof(char) * size * size);
				newcolors = malloc((*nombresprite + 1) * sizeof(int) * 27);
			}
			if (newsprites!=NULL && newcolors != NULL)
			{
				*sprites = newsprites;
				*colors = newcolors;
				int a = 27;
				while (a)
				{
					a--;
					(*colors)[*nombresprite * 27 + a] = 0;
				}
				a = size*size;
				while (a)
				{
					a--;
					(*sprites)[*nombresprite * size * size + a] = 0;
				}
				SpriteModifier(renderer, *sprites + *nombresprite * size * size, *colors + *nombresprite * 27,size, letters, lettersprites);
				(*nombresprite)++;
			}
		}
	}
	return (t==1);
}

int EditorMenu(SDL_Renderer* renderer, char* letters, char* spriteletters, char* name, char* title, char newlevel)
{
	//Chargement du nom de fichier
	char* endtitle = concatenate("[",name,0,0);
	if (endtitle)
		endtitle = concatenate(endtitle, "].edlz",1, 0);
	if (endtitle)
		endtitle = concatenate(title, endtitle,0, 1);
	if (endtitle)
		endtitle = concatenate("edit/", endtitle, 0, 1);
	if (!endtitle || !name || !title)
	{
		free(endtitle);
		return(FileError(renderer, letters, spriteletters));
	}
	int numbersprites[] = { 0, 0,0 };
	char* sprites8 = NULL;
	int* colors8 = NULL;
	char* sprites16 = NULL;
	int* colors16 = NULL;
	char* sprites32 = NULL;
	int* colors32 = NULL;
	if (newlevel)
	{
		//Création des données
	}
	else
	{
		FILE* save = fopen(endtitle, "r");
		if (!save)
		{
			free(endtitle);
			return(FileError(renderer, letters, spriteletters));
		}
		char valid = !(IntLecture(numbersprites, save, 0, 3) < 0);
		if (!valid)
		{
			free(endtitle);
			return(FileError(renderer, letters, spriteletters));
		}
		sprites8 = malloc(sizeof(char) * 64 * numbersprites[0]);
		colors8 = malloc(sizeof(int) * 27 * numbersprites[0]);
		sprites16 = malloc(sizeof(char) * 256 * numbersprites[1]);
		colors16 = malloc(sizeof(int) * 27 * numbersprites[1]);
		sprites32 = malloc(sizeof(char) * 32 * 32 * numbersprites[2]);
		colors32 = malloc(sizeof(int) * 27 * numbersprites[2]);
		if ((!(sprites32 && colors32) && numbersprites[2]) || (!(sprites16 && colors16) && numbersprites[1]) ||
			(!(sprites8 && colors8) && numbersprites[0]))
			valid = 0;
		if (valid)
			valid = !(CharLecture(sprites8, save, 0, 1, 64 * numbersprites[0]) < 0);
		if (valid)
			valid = !(CharLecture(sprites16, save, 0, 1, 256 * numbersprites[1]) < 0);
		if (valid)
			valid = !(CharLecture(sprites32, save, 0, 1, 32*32 * numbersprites[2]) < 0);
		if (valid)
			valid = !(IntLecture(colors8, save, 0, 27 * numbersprites[0]) < 0);
		if (valid)
			valid = !(IntLecture(colors16, save, 0, 27 * numbersprites[1]) < 0);
		if (valid)
			valid = !(IntLecture(colors32, save, 0, 27 * numbersprites[2]) < 0);
		fclose(save);
		if (!valid)
		{
			free(endtitle);
			free(colors8);
			free(sprites8);
			free(sprites16);
			free(colors16);
			free(sprites32);
			free(colors32);
			return(FileError(renderer, letters, spriteletters));
		}
	}
	int action = 1;
	int t = 0;
	while (action != 9 && t != 1)
	{
		//Menu de l'espace editeur
		action = 1;
		rect(renderer, 0, 0, 1024, 704, 0, 0, 0);
		rect(renderer, 510, 100, 4, 500, 200, 200, 200);
		cadre(renderer, 300, 0, 420, 70, 255, 0, 0);
		text(renderer, 320, 20, "Zone Editeur", letters, spriteletters, 255, 255, 255);
		text(renderer, 50, 110, "Sprites", letters, spriteletters, 255, 255, 255);
		text(renderer, 50, 162, "Cartes", letters, spriteletters, 255, 255, 255);
		text(renderer, 50, 214, "Scripts", letters, spriteletters, 255, 255, 255);
		text(renderer, 50, 266, "Variables", letters, spriteletters, 255, 255, 255);
		text(renderer, 50, 318, "Combats", letters, spriteletters, 255, 255, 255);
		text(renderer, 50, 370, "Menus", letters, spriteletters, 255, 255, 255);
		text(renderer, 50, 422, "Joueur", letters, spriteletters, 255, 255, 255);
		text(renderer, 50, 474, "Sauvegarder", letters, spriteletters, 255, 255, 255);
		text(renderer, 50, 526, "Quitter", letters, spriteletters, 255, 255, 255);
		t = 0;
		while (t != 9 && t != 6 && t != 1)
		{
			cadre(renderer, 38, 46 + action * 52, 400, 52, 0, 0, 255);
			SDL_RenderPresent(renderer);
			cadre(renderer, 38, 46 + action * 52, 400, 52, 0, 0, 0);
			t = Touche();
			if (t == 2 && action != 1)
			{
				action--;
			}
			if (t == 3 && action != 9)
			{
				action++;
			}
		}
		if (t == 9)
			t = 6;
		if (t == 6 && action == 1)
		{
			t = 0;
			int format = 0;
			while (t != 6 && t != 1)
			{
				rect(renderer, 514, 100, 510, 500, 0, 0, 0);
				text(renderer, 546, 110, "Format :", letters, spriteletters, 255, 255, 255);
				text(renderer, 546, 174, "8x8", letters, spriteletters, 255, 255 * (format != 0), 255 * (format != 0));
				text(renderer, 546, 238, "16x16", letters, spriteletters, 255, 255 * (format != 1), 255 * (format != 1));
				text(renderer, 546, 302, "32x32", letters, spriteletters, 255, 255 * (format != 2), 255 * (format != 2));
				text(renderer, 546, 368, "Retour", letters, spriteletters, 255, 255 * (format != 3), 255 * (format != 3));
				SDL_RenderPresent(renderer);
				t = Touche();
				if (t == 2 && format)
					format--;
				if (t == 3 && format != 3)
					format++;
				if (t == 9)
					t = 6;
				if (t == 6 && format == 0)
				{
					if (SpriteEditor(renderer, &sprites8, &colors8, numbersprites, 8, letters, spriteletters)==1)
						t=1;
				}
				if (t == 6 && format == 1)
				{
					if(SpriteEditor(renderer, &sprites16, &colors16, numbersprites+1, 16, letters, spriteletters) == 1)
						t = 1;
				}
				if (t == 6 && format == 2)
				{
					if(SpriteEditor(renderer, &sprites32, &colors32, numbersprites+2, 32, letters, spriteletters) == 1)
						t = 1;
				}
			}
		}
		if (t == 6 && action == 8)
		{
			//Sauvegarde
			FILE* save = fopen(endtitle, "w");
			if (!save)
			{
				t = FileError(renderer, letters, spriteletters);
			}
			else
			{
				IntWriting(numbersprites, save, 3);
				CharWriting(sprites8, save, numbersprites[0] * 64);
				CharWriting(sprites16, save, numbersprites[1] * 256);
				CharWriting(sprites32, save, numbersprites[2] * 32 * 32);
				IntWriting(colors8, save, numbersprites[0] * 27);
				IntWriting(colors16, save, numbersprites[1] * 27);
				IntWriting(colors32, save, numbersprites[2] * 27);
				fclose(save);
				cadre(renderer, 144, 200, 736, 270, 0, 255, 0);
				rect(renderer, 152, 208, 720, 254, 0, 0, 0);
				text(renderer, 176, 316, "Sauvegarde effectuee.", letters, spriteletters, 255, 255, 255);
				t = 0;
				SDL_RenderPresent(renderer);
				while (t == 0)
				{
					t = Touche();
				}
				t = (t == 1);
			}
		}
	}
	free(endtitle);
	free(colors8);
	free(sprites8);
	free(sprites16);
	free(colors16);
	free(sprites32);
	free(colors32);
	return (t == 1);
}