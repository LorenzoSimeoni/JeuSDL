#include "fonctionsBasiques.h"

#define WPERSO 30
#define HPERSO 30

#define STAT_SOL 0
#define STAT_AIR 1


typedef struct
{
    int status;
    float x,y;
    float vx,vy;
} Sprite;


int RefreshScreen(Sprite* Sp, SDL_Renderer **renderer, SDL_Texture **texture, SDL_Texture *textureSol[],
 SDL_Rect *dst, SDL_Rect dstTextureSol[], SDL_Color Turquoise);

void InitSprite(Sprite* Sp);
void Render(Sprite* Sp,SDL_Surface* screen);
void Saute(Sprite* Sp,float impulsion);
void ControleSol(Sprite* Sp);
void Gravite(Sprite* Sp,float factgravite,float 
	factsautmaintenu,Uint8* keys);
void Evolue(Sprite* Sp,Uint8* keys);

void UpdateEvents(Uint8* keys);







