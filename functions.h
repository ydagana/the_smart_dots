#ifndef DEF_FUNCTIONS
#define DEF_FUNCTIONS

    bool start(SDL_Surface* , char);
    bool instructions(SDL_Surface*);
    void blit(SDL_Surface *ecran, char card [][NH], SDL_Surface *dot1, SDL_Surface *dot2,
         SDL_Surface *img, SDL_Surface *img2, SDL_Surface *txt1, SDL_Surface *txt,
         SDL_Surface *Wset, SDL_Surface *Lset, char player, char *set);
    bool testWin(char(*)[NH], char);
    void won(SDL_Surface* player, SDL_Surface* ecran, SDL_Surface* cas);

#endif
