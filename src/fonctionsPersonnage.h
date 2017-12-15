#include "fonctionsBasiques.h"

#define WPERSO 15
#define HPERSO 23

#define STAT_SOL 0
#define STAT_AIR 1


typedef struct
{
    int status;
    float x,y;
    float vx,vy;
    int anim;
} Sprite;

void checkSpAnim(Sprite *Sp, SDL_Rect *personnage);
int RefreshScreen(Sprite* Sp, SDL_Renderer **renderer, SDL_Texture **texture, SDL_Texture *textureSol[],
 SDL_Rect *dst, SDL_Rect *personnage, SDL_Rect dstTextureSol[], SDL_Color Turquoise);

void InitSprite(Sprite* Sp);
void Render(Sprite* Sp,SDL_Surface* screen);
void Saute(Sprite* Sp,float impulsion);
int ControleSol(Sprite* Sp);
void ControleMur(Sprite* Sp);
void ControlePlateforme(Sprite *Sp, SDL_Rect dstTextureSol);
void Gravite(Sprite* Sp,float factgravite,float 
	factsautmaintenu,Uint8* keys);
void Evolue(Sprite* Sp,Uint8* keys, int *timetochange, SDL_Rect dstTextureSol[]);

void UpdateEvents(Uint8* keys);







