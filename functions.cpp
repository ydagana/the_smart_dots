#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "functions.h"
#include "cpu.h"

bool start(SDL_Surface* ecran, char cas)
{
    if(cas == 3)
        return instructions(ecran);
    else
    {
       srand(time(NULL));
       SDL_Surface *dot1 = NULL, *dot2 = NULL, *img1 = NULL, *img2 = NULL, *txt1 = NULL;
       SDL_Surface *txt2 = NULL, *Wset = NULL, *Lset = NULL, *txtWin1 = NULL, *txtWin2 = NULL;
       SDL_Surface *p1 = NULL, *p2 = NULL;
       TTF_Font *police = NULL, *police1 = NULL;
       SDL_Color color = {0, 0, 0}, bleu = {0, 0, 255}, red = {255, 0, 0};
       police = TTF_OpenFont("fonts/police3.ttf", 12);
       police1 = TTF_OpenFont("fonts/angelina.ttf", 60);
       dot1 = IMG_Load("images/dotV.jpg");
       dot2 = IMG_Load("images/dotR.jpg");
       img1 = IMG_Load("images/grille.jpg");
       img2 = IMG_Load("images/toplay.jpg");
       Wset = IMG_Load("images/Wset.png");
       Lset = IMG_Load("images/Lset.png");
       txtWin1 = TTF_RenderText_Blended(police1, "Set :", color);
       txtWin2 = TTF_RenderText_Blended(police1, "Game :", color);
       police1 = TTF_OpenFont("fonts/police3.ttf", 30);
       txt1 = TTF_RenderText_Blended(police, "player 1", color);
       p1 = TTF_RenderText_Blended(police1, "player 1", bleu);
       if(cas == 1)
       {
           p2 = TTF_RenderText_Blended(police1, "player 2", red);
           txt2 = TTF_RenderText_Blended(police, "player 2", color);
       }
       if(cas == 2)
       {
           p2 = TTF_RenderText_Blended(police1, "CPU", red);
           txt2 = TTF_RenderText_Blended(police, "CPU", color);
       }
       short X, Y, nbr;
       nbr = 1;
       char player = 1, p1set = 0, p2set = 0, set[5] = {0}, nset = 1;
       while((p1set < 3)&&(p2set < 3))
       {
            char card[NL][NH] = {0}, proba[NL][NH] = {0};
            bool cont = true, win = false;
            SDL_Event event;
            while(cont)
            {
                if((cas == 2)&&(player == 2))
                {
                    CPU(card, proba, &nbr);
                    win = testWin(card, player);
                    if(win)
                    {
                        nset++;
                        p2set++;
                        set[nset - 1] = 2;
                    }
                    player = 1;
                }
                char x = -1, y = -1;
                SDL_WaitEvent(&event);
                //while((event.type != SDL_QUIT)&&(event.type != SDL_KEYDOWN)&&(event.type != SDL_MOUSEBUTTONDOWN));
                switch(event.type)
                {
                    case SDL_QUIT:
                         cont = false;
                         return false;
                         break;
                    case SDL_KEYDOWN:
                         switch(event.key.keysym.sym)
                         {
                            case SDLK_ESCAPE:
                                 cont = false;
                                 return true;
                                 break;
                         }
                         break;
                    case SDL_MOUSEBUTTONDOWN:
                         if((event.button.button == SDL_BUTTON_LEFT)||
                            (event.button.button == SDL_BUTTON_RIGHT))
                         {
                            if((cas == 1)||((cas == 2)&&(player == 1)))
                            {
                                X = event.button.x;
                                Y = event.button.y;
                                if(Y < 555)
                                {
                                    if((X - 10)%D <= 5)
                                        x = (X - 10)/D;
                                    else if((X - 10)%D > 10)
                                        x = (X - 10)/D + 1;
                                    if((Y - 10)%D <= 5)
                                        y = (Y - 10)/D;
                                    else if((Y - 10)%D > 10)
                                        y = (Y - 10)/D + 1;
                                    if((card[x][y] == 0)&&(x >= 0)&&(y >= 0))
                                    {
                                        card[x][y] = player;
                                        win = testWin(card, player);
                                        if(player == 1)
                                        {
                                            if(win)
                                            {
                                                nset++;
                                                p1set++;
                                                set[nset - 1] = 1;
                                            }
                                            player = 2;
                                        }
                                        else
                                        {
                                            if(win)
                                            {
                                                nset++;
                                                p2set++;
                                                set[nset - 1] = 2;
                                            }
                                            player = 1;
                                        }
                                    }
                                }
                            }
                         }
                         break;
                }

                if(win)
                {
                    blit(ecran, card, dot1, dot2, img1, img2, txt1, txt2, Wset, Lset, player, set);
                    if(player == 1)
                        won(p2, ecran, txtWin1);
                    else
                        won(p1, ecran, txtWin1);
                    cont = false;
                }
                blit(ecran, card, dot1, dot2, img1, img2, txt1, txt2, Wset, Lset, player, set);
                SDL_Flip(ecran);
            }
        }
        if(player == 1)
            won(p2, ecran, txtWin2);
        else
            won(p1, ecran, txtWin2);
        TTF_CloseFont(police);
        TTF_CloseFont(police1);
        SDL_FreeSurface(img1);
        SDL_FreeSurface(img2);
        SDL_FreeSurface(txt1);
        SDL_FreeSurface(txt2);
        SDL_FreeSurface(txtWin1);
        SDL_FreeSurface(txtWin2);
        SDL_FreeSurface(dot1);
        SDL_FreeSurface(dot2);
        SDL_FreeSurface(Wset);
        SDL_FreeSurface(Lset);
    }
}

void won(SDL_Surface* player, SDL_Surface* ecran, SDL_Surface* cas)
{
    SDL_Rect pos;
    pos.x = L/2 - cas->w/2;
    pos.y = H/2 - cas->h/2 - 100;
    SDL_BlitSurface(cas, NULL, ecran, &pos);
    pos.x = L/2 - player->w/2;
    pos.y = H/2 - 70;
    SDL_BlitSurface(player, NULL, ecran, &pos);
    SDL_Event event;
    bool cont = true;
    while(cont)
    {
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
                          cont = false;
                          break;
                 }
                 break;
        }
        SDL_Flip(ecran);
    }
}

bool testWin(char card[][NH], char player)
{
    bool win1 = true, win2 = true, win3 = true, win4 = true;
    for(char i = 0; i < NL; i++)
    {
        for(char j = 0; j < NH; j++)
        {
            if(card[i][j] == player)
            {
                for(char k = 1; k < 5; k++)
                {
                    if(card[i][j + k] != player)
                        win1 = false;
                    if(card[i + k][j] != player)
                        win2 = false;
                    if(card[i + k][j + k] != player)
                        win3 = false;
                    if((i >= 4)&&(card[i - k][j + k] != player))
                        win4 = false;
                }
                if((win1)||(win2)||(win3)||((win4)&&(i >= 4)))
                    return true;
                else
                {
                    win1 = true;
                    win2 = true;
                    win3 = true;
                    win4 = true;
                }
            }
        }
    }
    return false;
}

void blit(SDL_Surface *ecran, char card [][NH], SDL_Surface *dot1, SDL_Surface *dot2,
     SDL_Surface *img1, SDL_Surface *img2, SDL_Surface *txt1, SDL_Surface *txt2,
     SDL_Surface *Wset, SDL_Surface *Lset, char player, char* set)
{
    SDL_Rect pos;
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    pos.x = 0;
    pos.y = 0;
    SDL_BlitSurface(img1, NULL, ecran, &pos);
    pos.x = 92;
    pos.y = 565;
    SDL_BlitSurface(dot1, NULL, ecran, &pos);
    pos.x = 92;
    pos.y = 584;
    SDL_BlitSurface(dot2, NULL, ecran, &pos);
    for(char i = 0; i < NL; i++)
    {
        for(char j = 0; j < NH; j++)
        {
            pos.x = i*D + 10 - dot1->w/2;
            pos.y = j*D + 10 - dot1->h/2;
            if(card[i][j] == 1)
                SDL_BlitSurface(dot1, NULL, ecran, &pos);
            else if(card[i][j] == 2)
                SDL_BlitSurface(dot2, NULL, ecran, &pos);
        }
    }
    pos.x = 1;
    if(player == 1)
        pos.y = 565;
    else
        pos.y = 584;
    SDL_BlitSurface(img2, NULL, ecran, &pos);
    pos.x = 25;
    pos.y = 565;
    SDL_BlitSurface(txt1, NULL, ecran, &pos);
    pos.x = 25;
    pos.y = 584;
    SDL_BlitSurface(txt2, NULL, ecran, &pos);
    for(char i = 0; i < 5; i++)
    {
        if(set[i] == 1)
        {
            pos.x = 92 + 25*i;
            pos.y = 565;
            SDL_BlitSurface(Wset, NULL, ecran, &pos);
            pos.y = 584;
            SDL_BlitSurface(Lset, NULL, ecran, &pos);
        }
        if(set[i] == 2)
        {
            pos.x = 92 + 25*i;
            pos.y = 584;
            SDL_BlitSurface(Wset, NULL, ecran, &pos);
            pos.y = 565;
            SDL_BlitSurface(Lset, NULL, ecran, &pos);
        }
    }
}

bool instructions(SDL_Surface* ecran)
{
    SDL_Surface *inst = NULL, *pied = NULL;
    SDL_Rect pos;
    TTF_Font *police;
    SDL_Color black = {0, 0, 0};
    police = TTF_OpenFont("fonts/police3.ttf", 12);
    pied = TTF_RenderText_Blended(police, "jens++ production 2008", black);
    inst = IMG_Load("images/instructions.jpg");
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    pos.x = ecran->w/2 - inst ->w/2;
    pos.y = 100;
    SDL_BlitSurface(inst, NULL, ecran, &pos);
    pos.x = L - pied->w;
    pos.y = H - pied->h;
    SDL_BlitSurface(pied, NULL, ecran, &pos);
    SDL_Event event;
    bool cont = true;
    while(cont)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                 cont = false;
                 return false;
                 break;
            case SDL_KEYDOWN:
				 switch(event.key.keysym.sym)
				 {
				 	case SDLK_ESCAPE:
						 cont = false;
						 return false;
						 break;
					case SDLK_RETURN:
                         cont = false;
                         return true;
                         break;
				 }
				 break;
        }
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(inst);
    SDL_FreeSurface(pied);
    TTF_CloseFont(police);
}

