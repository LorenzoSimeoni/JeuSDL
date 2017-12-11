#include "fonctionsBasiques.h"
#include "fonctionsMenu.h"

int RefreshScreenMenu(SDL_Renderer **renderer, SDL_Texture **texture, 
    SDL_Texture **texture2, SDL_Texture **texture3, SDL_Texture **texture4,
 SDL_Rect *dst, SDL_Rect *dst2, SDL_Rect *dst3, SDL_Rect *dst4, SDL_Color Turquoise)
{
    /*
      L'écran est coloré
    */
    if(setWindowColor(*renderer, Turquoise) == -1){
        fprintf(stderr, " Erreur setWindowColor : %s\n", SDL_GetError());
        return -1;
    }
    SDL_RenderCopy(*renderer, *texture, NULL, dst);
    SDL_RenderCopy(*renderer, *texture2, NULL, dst2);
    SDL_RenderCopy(*renderer, *texture3, NULL, dst3);
    SDL_RenderCopy(*renderer, *texture4, NULL, dst4);
    SDL_RenderPresent(*renderer);   
    return 0;
}

int CreateMenu(SDL_Renderer **renderer, SDL_Color Turquoise)
{
    /*
      On fabrique le menu
    */
    SDL_Rect dstNewGame = {W/(2.0+2.0/3.0), 100, 0.25*W , 50};
    SDL_Texture *newGame = NULL;

    SDL_Rect dstContinue = {W/(2.0+2.0/3.0), 160, 0.25*W , 50};
    SDL_Texture *Continue = NULL;

    SDL_Rect dstOptions = {W/(2.0+2.0/3.0), 220, 0.25*W , 50};
    SDL_Texture *options = NULL;

    SDL_Rect dstQuit = {W/(2.0+2.0/3.0), 280, 0.25*W , 50};
    SDL_Texture *quitt = NULL;
      
    if(LoadImageAndQuery(&newGame, renderer, dstNewGame,
     "/home/simeoni/Documents/ProjetJeuSDL/Images/NewGame.bmp") == -1) 
        return -1;
    
    if(LoadImageAndQuery(&Continue, renderer, dstContinue,
     "/home/simeoni/Documents/ProjetJeuSDL/Images/Continue.bmp") == -1) 
        return -1;

    if(LoadImageAndQuery(&options, renderer, dstOptions,
     "/home/simeoni/Documents/ProjetJeuSDL/Images/Options.bmp") == -1) 
        return -1;

    if(LoadImageAndQuery(&quitt, renderer, dstQuit,
     "/home/simeoni/Documents/ProjetJeuSDL/Images/Quit.bmp") == -1) 
        return -1;

    if(RefreshScreenMenu(renderer, &newGame, &Continue, &options, &quitt, 
        &dstNewGame, &dstContinue, &dstOptions, &dstQuit, Turquoise) == -1)
        return -1;
    if(newGame != NULL)
        SDL_DestroyTexture(newGame);
    if(Continue != NULL)
        SDL_DestroyTexture(Continue);
    if(options != NULL)
        SDL_DestroyTexture(options);
    if(quitt != NULL)
        SDL_DestroyTexture(quitt);
    return 0;
}

int Menu() 
{
    SDL_Event event;
    /*
      On attend un évènement ici
    */
    SDL_WaitEvent(&event);
    if(event.type == SDL_QUIT)
        return SDL_TRUE;
    else if(event.type == SDL_MOUSEBUTTONUP) {
        if(event.button.button == SDL_BUTTON_LEFT && 
            (event.motion.x >=  W/(2.0+2.0/3.0) &&  event.motion.x <=  W/(2.0+2.0/3.0) + 0.25*W)
            && (event.motion.y >= 100 && event.motion.y <= 150))
            return 2;
        if(event.button.button == SDL_BUTTON_LEFT && 
            (event.motion.x >=  W/(2.0+2.0/3.0) &&  event.motion.x <=  W/(2.0+2.0/3.0) + 0.25*W)
            && (event.motion.y >= 160 && event.motion.y <= 210))
            printf("On est dans continue\n");
        if(event.button.button == SDL_BUTTON_LEFT && 
            (event.motion.x >=  W/(2.0+2.0/3.0) &&  event.motion.x <=  W/(2.0+2.0/3.0) + 0.25*W)
            && (event.motion.y >= 220 && event.motion.y <= 270))
            printf("On est dans options\n");
        if(event.button.button == SDL_BUTTON_LEFT && 
            (event.motion.x >=  W/(2.0+2.0/3.0) &&  event.motion.x <=  W/(2.0+2.0/3.0) + 0.25*W)
            && (event.motion.y >= 280 && event.motion.y <= 330))
            printf("On est dans exit\n");
    }
    return 0;
}
