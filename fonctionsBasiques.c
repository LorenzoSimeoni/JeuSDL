#include "fonctionsBasiques.h"

int setWindowColor(SDL_Renderer *renderer, SDL_Color color)
{
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
        return -1;
    if(SDL_RenderClear(renderer) < 0)
        return -1;
    return 0;  
}

void icone(SDL_Window *window)
{
    SDL_Surface *surface;
    surface = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0);

    /* On crée quatre carré pour notre icône. */
    struct carre carre[4] = {
        { {  4,  4, 10, 10 }, SDL_MapRGB(surface->format, 0, 0, 0) }, /* Noir */
        { {  4, 18, 10, 10 }, SDL_MapRGB(surface->format, 0, 0, 255) }, /* Bleu */
        { { 18,  4, 10, 10 }, SDL_MapRGB(surface->format, 0, 255, 0) }, /* Vert */
        { { 18, 18, 10, 10 }, SDL_MapRGB(surface->format, 255, 255, 255) } /* Blanc */
    };

    /* On remplit notre surface grâce à nos carrés. */
    for(int i = 0; i < 4; i++)
        SDL_FillRect(surface, &carre[i].rect, carre[i].couleur);

    SDL_SetWindowIcon(window, surface);
    SDL_FreeSurface(surface);
}

int init(SDL_Window **window, SDL_Renderer **renderer, 
    int w, int h)
{
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return -1;
    }

    *window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              w, h, SDL_WINDOW_SHOWN);
    if(*window == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return -1;
    }

    icone(*window);

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if(*renderer == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}

SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL; 
    SDL_Texture *texture = NULL;
    tmp = SDL_LoadBMP(path);
    if(NULL == tmp)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }
    return texture;
}

void Destroyer(SDL_Texture *texture,
    SDL_Renderer *renderer, SDL_Window *window)
{
    if(texture != NULL)
        SDL_DestroyTexture(texture);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

int LoadImageAndQuery(SDL_Texture **texture, SDL_Renderer **renderer, SDL_Rect dst, const char path[])
{
    /*
      On load l'image du personnage dans une texture
    */
    *texture = loadImage(path, *renderer);

    if(*texture == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
        return -1;
    }
    /* On récupère les dimensions de la texture, on la copie sur le renderer
       et on met à jour l’écran. */
    SDL_QueryTexture(*texture, NULL, NULL, &dst.w, &dst.h);
    return 0;
}