#include "fonctionsBasiques.h"
#include "fonctionsPersonnage.h"

int RefreshScreen(Sprite* Sp, SDL_Renderer **renderer, SDL_Texture **texture, SDL_Texture *textureSol[],
 SDL_Rect *dst, SDL_Rect dstTextureSol[], SDL_Color Turquoise)
{
    dst->x = (Sint16)Sp->x;
    dst->y = (Sint16)Sp->y;
    /*
      L'écran est coloré
    */
    if(setWindowColor(*renderer, Turquoise) == -1){
        fprintf(stderr, " Erreur setWindowColor : %s\n", SDL_GetError());
        return -1;
    }
    for(int k = 0; k<20 ; k++) {
        SDL_RenderCopy(*renderer, textureSol[k], NULL, &dstTextureSol[k]);
    }
    SDL_RenderCopy(*renderer, *texture, NULL, dst);
    SDL_RenderPresent(*renderer);   
    return 0;
}

void InitSprite(Sprite* Sp)
{
    Sp->x = 0.0f;
    Sp->y = 330.0f;
    Sp->status = STAT_SOL;
    Sp->vx = Sp->vy = 0.0f;
}

void Saute(Sprite* Sp,float impulsion)
{
    Sp->vy = -impulsion;
    Sp->status = STAT_AIR;
}

void ControleSol(Sprite* Sp)
{
    if (Sp->y>330.0f)
    {
        Sp->y = 330.0f;
        if (Sp->vy>0)
            Sp->vy = 0.0f;
        Sp->status = STAT_SOL;
    }
}

void ControleMur(Sprite* Sp)
{
    if (Sp->x > W - WPERSO)
    {
        Sp->x = W - WPERSO;
        if (Sp->vx>0)
            Sp->vx = 0.0f;
    }
    else if(Sp->x < 0)
    {
        Sp->x = 0;
        if (Sp->vx < 0)
            Sp->vx = 0.0f;
    }
}

void Gravite(Sprite* Sp,float factgravite,float factsautmaintenu,Uint8* keys)
{
    if (Sp->status == STAT_AIR && keys[SDL_SCANCODE_SPACE])
        factgravite/=factsautmaintenu;
    Sp->vy += factgravite;
}

void Evolue(Sprite* Sp,Uint8* keys)
{
    float lateralspeed = 0.5f;
    float airlateralspeedfacteur = 0.5f;
    float maxhspeed = 3.0f;
    float adherance = 1.5f;
    float impulsion = 6.0f;
    float factgravite = 0.5f;
    float factsautmaintenu = 3.0f;
// controle lateral
    if (Sp->status == STAT_AIR) // (*2)
        lateralspeed*= airlateralspeedfacteur;
    if (keys[SDL_SCANCODE_LEFT]) // (*1)
        Sp->vx-=lateralspeed;
    if (keys[SDL_SCANCODE_RIGHT])
        Sp->vx+=lateralspeed;
    if (Sp->status == STAT_SOL && !keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT]) // (*3)
        Sp->vx/=adherance;
// limite vitesse
    if (Sp->vx>maxhspeed) // (*4)
        Sp->vx = maxhspeed;
    if (Sp->vx<-maxhspeed)
        Sp->vx = -maxhspeed;
// saut
    if (keys[SDL_SCANCODE_SPACE] && Sp->status == STAT_SOL)
        Saute(Sp,impulsion);
    Gravite(Sp,factgravite,factsautmaintenu,keys);
    ControleSol(Sp);
    ControleMur(Sp);
// application du vecteur à la position.
    Sp->x +=Sp->vx;
    Sp->y +=Sp->vy;
}

void UpdateEvents(Uint8* keys)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            keys[event.key.keysym.scancode]=1;
            break;
        case SDL_KEYUP:
            keys[event.key.keysym.scancode]=0;
            break;
        }
    }
}