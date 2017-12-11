#ifndef __BASE__

#define __BASE__

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define W 800
#define H 400
#define CASE 10

struct carre {
   SDL_Rect rect;
   Uint32 couleur;
};

int setWindowColor(SDL_Renderer *renderer, SDL_Color color);
int init(SDL_Window **window, SDL_Renderer **renderer, 
    int w, int h);
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
void Destroyer(SDL_Texture *texture,
	SDL_Renderer *renderer, SDL_Window *window);

void icone(SDL_Window *window);
int LoadImageAndQuery(SDL_Texture **texture, SDL_Renderer **renderer, SDL_Rect dst, const char path[]);

#endif
