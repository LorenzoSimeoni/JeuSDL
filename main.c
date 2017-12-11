#include "fonctionsBasiques.h"
#include "fonctionsPersonnage.h"
#include "fonctionsMenu.h"

int main (int argc, char *argv[])
{
    /*
      Partie Déclaration Variables/Pointeurs
    */
    SDL_Window *window;
    Uint8 keys[SDL_NUM_SCANCODES] = {0};
    Sprite S;
    SDL_Renderer *renderer;
    Uint32 timer,elapsed;
    int status = EXIT_FAILURE;
    //SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color Turquoise = {26,188, 156,0};

    SDL_Texture *textureSol[20];
    SDL_Rect dstTextureSol[20];
    for(int i=0; i<20; i++) {
        dstTextureSol[i].x = i*40;
        dstTextureSol[i].y = 360;
        dstTextureSol[i].w = 40;
        dstTextureSol[i].h = 40;
    }

    SDL_Texture *texture = NULL;
    SDL_Rect dst = {0, 330, WPERSO, WPERSO};

    SDL_bool quit = SDL_FALSE;    

    if(init(&window, &renderer, W, H) == -1)
        goto Quit;

    if(CreateMenu(&renderer, Turquoise) == -1) 
        goto Quit;

    while (quit != SDL_TRUE)
    {
        quit = Menu();
        if(quit == 2)
            goto Game;
    }

Game:
    quit = SDL_FALSE;
    /*
      A partir d'ici on lance le jeu
    */
    for(int i=0; i<20; i++) {
        if(LoadImageAndQuery(&textureSol[i], &renderer, dstTextureSol[i], "/home/simeoni/Documents/ProjetJeuSDL/Images/block.bmp") == -1) 
            goto Quit;
    }

    if(LoadImageAndQuery(&texture, &renderer, dst, "/home/simeoni/Documents/ProjetJeuSDL/Images/petitMickey.bmp") == -1) 
        goto Quit;

    if(RefreshScreen(&S,&renderer, &texture, textureSol, 
        &dst, dstTextureSol, Turquoise) == -1)
        goto Quit;

    InitSprite(&S);
    do
    {
        timer = SDL_GetTicks();
        UpdateEvents(keys);
        Evolue(&S,keys);
        /*
          On attend un évènement ici
        */
        if(keys[SDL_SCANCODE_ESCAPE] == 1) 
            quit = SDL_TRUE;
        if(RefreshScreen(&S,&renderer, &texture, textureSol, 
            &dst, dstTextureSol, Turquoise) == -1)
            goto Quit;
        elapsed = SDL_GetTicks() - timer;
        if (elapsed<20)
            SDL_Delay(20-elapsed);

    } while(!quit);

    status = EXIT_SUCCESS;

    /*
      On détruit ce qu'il y a à détruire
    */
Quit:
    Destroyer(texture, renderer, window);
    return status;
}