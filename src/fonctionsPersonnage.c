#include "fonctionsBasiques.h"
#include "fonctionsPersonnage.h"

void checkSpAnim(Sprite *Sp, SDL_Rect *personnage){

    switch(Sp->anim){
        case 1:
            personnage->x = 2;
            personnage->y = 167;
            break;
        case 2:
            personnage->x = 26;
            personnage->y = 167;
            break;
        case 3:
            personnage->x = 50;
            personnage->y = 167;
            break;
        case -1:
            personnage->x = 6;
            personnage->y = 231;
            break;
        case -2:
            personnage->x = 30;
            personnage->y = 231;
            break;
        case -3:
            personnage->x = 54;
            personnage->y = 231;
            break;
    }
}

int RefreshScreen(Sprite* Sp, SDL_Renderer **renderer, SDL_Texture **texture, SDL_Texture *textureSol[],
 SDL_Rect *dst, SDL_Rect *personnage, SDL_Rect dstTextureSol[], SDL_Color Turquoise)
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
    for(int k = 0; k<30 ; k++) {
        SDL_RenderCopy(*renderer, textureSol[k], NULL, &dstTextureSol[k]);
    }
    checkSpAnim(Sp, personnage);
    SDL_RenderCopy(*renderer, *texture, personnage, dst);
    SDL_RenderPresent(*renderer);   
    return 0;
}

void InitSprite(Sprite* Sp)
{
    Sp->x = 0.0f;
    Sp->y = 337.0f;
    Sp->status = STAT_SOL;
    Sp->vx = Sp->vy = 0.0f;
    Sp->anim = 0;
}

void Saute(Sprite* Sp,float impulsion)
{
    Sp->vy = -impulsion;
    Sp->status = STAT_AIR;
}

int ControleSol(Sprite* Sp)
{
    if (Sp->y>337.0f)
    {
        Sp->y = 337.0f;
        if (Sp->vy>0)
            Sp->vy = 0.0f;
        Sp->status = STAT_SOL;
        return 1;
    }
    return 0;
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

void ControlePlateforme(Sprite *Sp, SDL_Rect dstTextureSol)
{
    if (Sp->x >= dstTextureSol.x - WPERSO  && Sp->x <= dstTextureSol.x + dstTextureSol.w) {
        if(Sp->y > dstTextureSol.y - HPERSO && Sp->y < dstTextureSol.y + dstTextureSol.h -HPERSO && Sp->vy>0) {
            Sp->y = dstTextureSol.y - HPERSO;
            Sp->vy = 0.0f;
            Sp->status = STAT_SOL; 
        }
        else if(Sp->y > dstTextureSol.y && Sp->y < dstTextureSol.y + dstTextureSol.h && Sp->vy<0)
            Sp->y = dstTextureSol.y + dstTextureSol.h;
        // else if(Sp-> y > dstTextureSol.h && Sp->y < dstTextureSol.y - HPERSO)
        //     Sp->x = dstTextureSol.x;
    }
    
}

void Gravite(Sprite* Sp,float factgravite,float factsautmaintenu,Uint8* keys)
{
    if (Sp->status == STAT_AIR && keys[SDL_SCANCODE_SPACE])
        factgravite/=factsautmaintenu;
    Sp->vy += factgravite;
}

void Evolue(Sprite* Sp,Uint8* keys, int *timetochange, SDL_Rect dstTextureSol[])
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
    if (keys[SDL_SCANCODE_LEFT]) {// (*1)
        Sp->vx-=lateralspeed;
        if(Sp->status == STAT_SOL){
            if(Sp->anim != -1 && Sp->anim != -2 && Sp->anim != -3) {
                Sp->anim = -1;
                *timetochange = 0;
            }
            if(*timetochange == 10)
            {
                Sp->anim = Sp->anim - 1 % 3;
                if(Sp->anim == 0) {
                    Sp->anim = -3;
                }
                *timetochange = 0;
            }
            else
                *timetochange = *timetochange + 1;
        }
        else 
            Sp->anim = -1;

    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        Sp->vx+=lateralspeed;
        if(Sp->status == STAT_SOL){
            if(Sp->anim != 1 && Sp->anim != 2 && Sp->anim != 3) {
                Sp->anim = 1;
                *timetochange = 0;
            }
            if(*timetochange == 10)
            {
                Sp->anim = Sp->anim + 1 % 3;
                if(Sp->anim == 0) {
                    Sp->anim = 3;
                }
                *timetochange = 0;
            }
            else
                *timetochange = *timetochange + 1;
        }
        else
            Sp->anim = 1;
    }
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
    int res = ControleSol(Sp);
    if(res == 1)
        goto finish;
    ControleMur(Sp);
    for(int k = 20; k<30; k++)
        ControlePlateforme(Sp, dstTextureSol[k]);
    if(Sp->vy != 0)
        Sp->status = STAT_AIR;
finish:
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