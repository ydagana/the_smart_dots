#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "functions.h"

int main(int argc, char** argv)
{
    SDL_Surface *ecran = NULL,*txt = NULL, *img = NULL;
    SDL_Rect pos, pos1;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    TTF_Font *police2;
    SDL_Color black = {0, 0, 0};
    SDL_WM_SetCaption("The Smart Dots", NULL);
    SDL_WM_SetIcon(IMG_Load("images/ico.png"), NULL);
    ecran = SDL_SetVideoMode(L, H, 32, SDL_SWSURFACE);
    police2 = TTF_OpenFont("fonts/police1.ttf", 20);
    img = IMG_Load("images/starting.jpg");
    pos.x = 0;
    pos.y = 0;
    SDL_BlitSurface(img, NULL, ecran, &pos);
    bool cont = true;
    SDL_Event event;
    char cas = 1;
    while(cont)
    {
        pos.x = 0;
        pos.y = 0;
        SDL_BlitSurface(img, NULL, ecran, &pos);
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                 cont = false;
                 break;
            case SDL_KEYDOWN:
				 switch(event.key.keysym.sym)
				 {
				 	case SDLK_ESCAPE:
						 cont = false;
						 break;
					case SDLK_RETURN:
						 cont = start(ecran, cas);
						 break;
					case SDLK_LEFT:
						 cas--;
						 break;
					case SDLK_DOWN:
						 cas--;
						 break;
					case SDLK_RIGHT:
						 cas++;
						 break;
					case SDLK_UP:
						 cas++;
						 break;
				 }
				 break;
        }
        if(cas > 3)
			cas = 1;
		if(cas < 1)
			cas = 3;
		if(cas == 1)
			txt = TTF_RenderText_Blended(police2, "jouer contre un ami", black);
		if(cas == 2)
			txt = TTF_RenderText_Blended(police2, "jouer contre CPU", black);
		if(cas == 3)
			txt = TTF_RenderText_Blended(police2, "instructions", black);
        pos.x = ecran->w/2 - txt->w/2;
		pos.y = 300;
		SDL_BlitSurface(txt, NULL, ecran, &pos);
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(img);
    SDL_FreeSurface(txt);
	TTF_CloseFont(police2);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
