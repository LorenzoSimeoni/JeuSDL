#include "fonctionsBasiques.h"
#include "fonctionsPersonnage.h"
#include "fonctionsMenu.h"
#include "map.h"

int main (int argc, char *argv[])
{
    /*
      Partie Déclaration Variables/Pointeurs
    */
    SDL_Window *window;
    Uint8 keys[SDL_NUM_SCANCODES] = {0}; //Tableau qui permet de gérer plusieurs évènements
    Sprite S; // Structure qui gère notre personnage
    SDL_Renderer *renderer; 
    Uint32 timer,elapsed; //Permet de gérer son temps de rafraichissement
    int status = EXIT_FAILURE; 
    int timetochange = 0; //Variable utile pour l'animation du personnage
    SDL_Color Turquoise = {26,188, 156,0};

    SDL_Texture *textureSol[30]; //Tableau avec toutes les textures
    SDL_Rect dstTextureSol[30]; //Tableau qui gère les emplacements des textures
    /*
      Ici on initialise toutes les positions des textures de sol
    */
    for(int i=0; i<20; i++) {
        dstTextureSol[i].x = i*40;
        dstTextureSol[i].y = 360;
        dstTextureSol[i].w = 40;
        dstTextureSol[i].h = 40;
    }
    mapage(dstTextureSol); // Permet pour le moment de placer des blocs sur lesquels sauter.

    SDL_Texture *texture = NULL; //texture du personnage
    SDL_Rect dst = {0, 337, WPERSO, HPERSO}; //Where is our character at the beginning
    SDL_Rect personnage = {2, 167, WPERSO, HPERSO}; //Droite = 35 Gauche = 99
 
    SDL_bool quit = SDL_FALSE;    

    //On initialise SDL, le renderer et la windows
    if(init(&window, &renderer, W, H) == -1)
        goto Quit;
    //On load les textures et on choisi les coordonnées
    if(CreateMenu(&renderer, Turquoise) == -1) 
        goto Quit;

    // Tant qu'on ne clique pas sur le bouton on attend
    while (quit != SDL_TRUE)
    {
        quit = Menu();
        if(quit == 2)
            goto Game;
        else if(quit == 1)
            goto Quit;
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
    for(int i=20; i<30; i++) {
        if(LoadImageAndQuery(&textureSol[i], &renderer, dstTextureSol[i], "/home/simeoni/Documents/ProjetJeuSDL/Images/terre.bmp") == -1) 
            goto Quit;
    }

    if(LoadImageAndQuery(&texture, &renderer, dst, "/home/simeoni/Documents/ProjetJeuSDL/Images/character/characters.bmp") == -1) 
        goto Quit;

    if(RefreshScreen(&S,&renderer, &texture, textureSol, 
        &dst, &personnage,dstTextureSol, Turquoise) == -1)
        goto Quit;
    //On initialise le personnage
    InitSprite(&S);
    do
    {
        timer = SDL_GetTicks(); 
        UpdateEvents(keys);//Si on appui sur un bouton, on le note dans un tableau
        Evolue(&S,keys, &timetochange, dstTextureSol); // Le personnage varie dans son environnement
        /*
          On attend un évènement ici
        */
        if(keys[SDL_SCANCODE_ESCAPE] == 1)  
            quit = SDL_TRUE;
        if(RefreshScreen(&S,&renderer, &texture, textureSol, 
            &dst, &personnage, dstTextureSol, Turquoise) == -1)
            goto Quit;
        elapsed = SDL_GetTicks() - timer;
        if (elapsed<20) //On gère le temps de rafraichissement
            SDL_Delay(20-elapsed);

    } while(!quit);

    status = EXIT_SUCCESS;

    /*
      On détruit ce qu'il y a à détruire
    */
Quit:
    Destroyer(textureSol,texture, renderer, window);
    return status;
}