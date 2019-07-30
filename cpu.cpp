#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constantes.h"
#include "cpu.h"

void CPU(char card[NL][NH], char proba[NL][NH], short *nbr)
{
    for(char i = 0; i < NL; i++)
    {
        for(char j = 0; j < NH; j++)
        {
            if(card[i][j] == 1)
                proba[i][j] = -1;
            if(card[i][j] == 2)
                proba[i][j] = -2;
            if(card[i][j] == 0)
            {
                if((i > 3)&&(j > 3)&&(i + 4 < NL)&&(j + 4 < NH))
                    proba[i][j] = 1;
                else
                    proba[i][j] = 0;
            }
        }
    }
    for(char i = 0; i < NL; i++)//horizentalement
    {
        for(char j = 0; j < NH; j++)//verticalement
        {
        //défense

            //tester s'il y a 4 points d'un extrimité vide -> 90
            DefTest1(card, proba, i, j);

            //tester s'il y a 1 points peut construie 5 points -> 90
            DefTest2(card, proba, i, j);

            //tester s'il y a 3 points de deux extrimités vide -> 70
            DefTest3(card, proba, i, j);

            //tester s'il y a 1 points peut construire 4 points de deux extrimité vide -> 70
            DefTest4(card, proba, i, j);

            //tester s'il ya 3 points d'un extrimité vide -> 20
            DefTest5(card, proba, i, j);

            //tester s'il y a 2 points de deux extrimités vide -> 40
            DefTest6(card,proba, i, j);

            //attack

            //tester s'il y a 4 points d'un extrimité vide -> 100
            AttTest1(card, proba, i, j);

            //tester s'il y a 1 points peut construie 5 points -> 100
            AttTest2(card, proba, i, j);

            //tester s'il y a 3 points de deux extrimités vide -> 80
            AttTest3(card, proba, i, j);

            //tester s'il y a 1 points peut construire 4 points de deux extrimité vide -> 80
            AttTest4(card, proba, i, j);

            //tester s'il ya 3 points d'un extrimité vide -> 50
            AttTest5(card, proba, i, j);

            //mettre un point à cote de deux autres -> 30
            AttTest6(card, proba, i, j);

            //mettre un point à cote d'un autre -> 10
            AttTest7(card, proba, i, j);
        }
    }

    //mettre le points qui a "proba" la plus grande
    put(card, proba, nbr);
}

//tester s'il y a 4 points d'un extrimité vide -> 90
void DefTest1(char card[NL][NH], char proba[NL][NH], char i, char j)
{
    char prob = 90;
    bool cas1 = true, cas2 = true, cas3 = true, cas4 = true;
    if(card[i][j] == 1)
    {
        for(char k = 1; k < 4; k++)
        {
            if(j + 3 < NH)
            {
                if(card[i][j + k] != 1)
                    cas1 = false;
            }
            if(i + 3 < NL)
            {
                if(card[i + k][j] != 1)
                    cas2 = false;
            }
            if((j + 3 < NH)&&(i + 3 < NL))
            {
                if(card[i + k][j + k] != 1)
                    cas3 = false;
            }
            if((j + 3 < NH)&&(i > 2))
            {
                if(card[i - k][j + k] != 1)
                    cas4 = false;
            }
        }
        if((cas1)&&(j + 3 < NH))
        {
            if((j > 0)&&(card[i][j - 1] == 0))
                proba[i][j - 1] = prob;
            if((j < NH - 4)&&(card[i][j + 4] == 0))
                proba[i][j + 4] = prob;
        }
        if((cas2)&&(i + 3 < NL))
        {
            if((i > 0)&&(card[i - 1][j] == 0))
                proba[i - 1][j] = prob;
            if((i < NL - 4)&&(card[i + 4][j] == 0))
                proba[i + 4][j] = prob;
        }
        if((cas3)&&(j + 3 < NH)&&(i + 3 < NL))
        {
            if((i > 0)&&(j > 0)&&(card[i - 1][j - 1] == 0))
                proba[i - 1][j - 1] = prob;
            if((i < NL - 4)&&(j < NH - 4)&&(card[i + 4][j + 4] == 0))
                proba[i + 4][j + 4] = prob;
        }
        if((cas4)&&(j + 3 < NH)&&(i > 2))
        {
            if((i < NL - 1)&&(j > 0)&&(card[i + 1][j - 1] == 0))
                proba[i + 1][j - 1] = prob;
            if((j < NH - 4)&&(i > 3)&&(card[i - 4][j + 4] == 0))
                proba[i - 4][j + 4] = prob;
        }
    }
}

//tester s'il y a 1 points peut construie 5 points -> 90
void DefTest2(char card[NL][NH], char proba[NL][NH], char i, char j)
{
    char prob = 90;
    char cas1 = 0, cas2 = 0, cas3 = 0, cas4 = 0, i1 = 0, i2 = 0, i3 = 0, i4 = 0;
    if((card[i][j] == 1)&&(j + 4 < NH)&&(card[i][j + 4] == 1))
    {
        for(char k = 1; k < 4; k++)
        {
            if(card[i][j + k] != 1)
            {
                cas1 = k;
                i1 ++;
            }
        }
        if((i1 == 1)&&(card[i][j + cas1] == 0))
            proba[i][j + cas1] = prob;
    }
    if((card[i][j] == 1)&&(i + 4 < NL)&&(card[i + 4][j] == 1))
    {
        for(char k = 1; k < 4; k++)
        {
            if(card[i + k][j] != 1)
            {
                cas2 = k;
                i2 ++;
            }
        }
        if((i2 == 1)&&(card[i + cas2][j] == 0))
            proba[i + cas2][j] = prob;
    }
    if((card[i][j] == 1)&&((i + 4 < NL)&&(j + 4 < NH)&&(card[i + 4][j + 4] == 1)))
    {
        for(char k = 1; k < 4; k++)
        {
            if(card[i + k][j + k] != 1)
            {
                cas3 = k;
                i3 ++;
            }
        }
        if((i3 == 1)&&(card[i + cas3][j + cas3] == 0))
            proba[i + cas3][j + cas3] = prob;
    }
    if((card[i][j] == 1)&&(i > 3)&&(j + 4 < NH)&&(card[i - 4][j + 4] == 1))
    {
        for(char k = 1; k < 4; k++)
        {
            if(card[i - k][j + k] != 1)
            {
                cas4 = k;
                i4 ++;
            }
        }
        if((i4 == 1)&&(card[i - cas4][j + cas4] == 0))
            proba[i - cas4][j + cas4] = prob;
    }
}

//tester s'il y a 3 points de deux extrimités vide -> 70
void DefTest3(char card[NL][NH], char proba[NL][NH], char i, char j)
{
    char prob = 70;
    bool cas1 = true, cas2 = true, cas3 = true, cas4 = true;
    if(card[i][j] == 1)
    {
        for(char k = 1; k < 3; k++)
        {
            if(j + 2 < NH)
            {
                if(card[i][j + k] != 1)
                    cas1 = false;
            }
            if(i + 2 < NL)
            {
                if(card[i + k][j] != 1)
                    cas2 = false;
            }
            if((j + 2 < NH)&&(i + 2 < NL))
            {
                if(card[i + k][j + k] != 1)
                    cas3 = false;
            }
            if((j + 2 < NH)&&(i > 1))
            {
                if(card[i - k][j + k] != 1)
                    cas4 = false;
            }
        }
        if((cas1)&&(j + 2 < NH))
        {
            if(((j > 0)&&(card[i][j - 1] == 0))&&((j + 3 < NH)&&(card[i][j + 3] == 0)))
            {
                if(proba[i][j - 1] < prob)
                    proba[i][j - 1] = prob + proba[i][j - 1]/10;
                else
                {
                    if(proba[i][j - 1]%10 + prob/10 >9)
                        proba[i][j - 1]+=9;
                    else
                        proba[i][j - 1] += prob/10;
                }
                if(proba[i][j + 3] < prob)
                    proba[i][j + 3] = prob + proba[i][j + 3]/10;
                else
                {
                    if(proba[i][j + 3]%10 + prob/10 >9)
                        proba[i][j + 3]+=9;
                    else
                        proba[i][j + 3] += prob/10;
                }
            }
        }
        if((cas2)&&(i + 2 < NL))
        {
            if(((i > 0)&&(card[i - 1][j] == 0))&&((i + 3 < NL)&&(card[i + 3][j] == 0)))
            {
                if(proba[i - 1][j] < prob)
                    proba[i - 1][j] = prob + proba[i - 1][j]/10;
                else
                {
                    if(proba[i - 1][j]%10 + prob/10 >9)
                        proba[i - 1][j]+=9;
                    else
                         proba[i - 1][j]+=prob/10;
                }
                if(proba[i + 3][j] < prob)
                    proba[i + 3][j] = prob + proba[i + 3][j]/10;
                else
                {
                    if(proba[i + 3][j]%10 + prob/10 >9)
                        proba[i + 3][j] +=9;
                    else
                        proba[i + 3][j] += prob/10;
                }
            }
        }
        if((cas3)&&(j + 2 < NH)&&(i + 2 < NL))
        {
            if(((i > 0)&&(j > 0)&&(card[i - 1][j - 1] == 0))&&((i + 3 < NL)&&(j + 3< NH)&&(card[i + 3][j + 3] == 0)))
            {
                if(proba[i - 1][j - 1] < prob)
                    proba[i - 1][j - 1] = prob + proba[i - 1][j - 1]/10;
                else
                {
                    if(proba[i - 1][j - 1]%10 + prob/10 >9)
                        proba[i - 1][j - 1]+=9;
                    else
                        proba[i - 1][j - 1] += prob/10;
                }
                if(proba[i + 3][j + 3] < prob)
                    proba[i + 3][j + 3] = prob + proba[i + 3][j + 3]/10;
                else
                {
                    if(proba[i + 3][j + 3]%10 + prob/10 >9)
                        proba[i + 3][j + 3]+=9;
                    else
                        proba[i + 3][j + 3] += prob/10;
                }
            }
        }
        if((cas4)&&(j + 2 < NH)&&(i > 1))
        {
            if(((i + 1 < NL)&&(j > 0)&&(card[i + 1][j - 1] == 0))&&((j + 3 < NH)&&(i > 2)&&(card[i - 3][j + 3] == 0)))
            {
                if(proba[i + 1][j - 1] < prob)
                    proba[i + 1][j - 1] = prob + proba[i + 1][j - 1]/10;
                else
                {
                    if(proba[i + 1][j - 1]%10 + prob/10 >9)
                        proba[i + 1][j - 1]+=9;
                    else
                        proba[i + 1][j - 1] += prob/10;
                }
                if(proba[i - 3][j + 3] < prob)
                    proba[i - 3][j + 3] = prob + proba[i - 3][j + 3]/10;
                else
                {
                    if(proba[i - 3][j + 3]%10 + prob/10 >9)
                        proba[i - 3][j + 3]+=9;
                    else
                        proba[i - 3][j + 3] += prob/10;
                }
            }
        }
    }
}

//tester s'il y a 1 points peut construire 4 points de deux extrimité vide -> 70
void DefTest4(char card[NL][NH], char proba[NL][NH], char i, char j)
{
    char prob = 70;
    char cas1 = 0, cas2 = 0, cas3 = 0, cas4 = 0, i1 = 0, i2 = 0, i3 = 0, i4 = 0;
    if((j > 0)&&(card[i][j] == 1)&&(j + 4 < NH)&&(card[i][j + 3] == 1)&&(card[i][j - 1] == 0)&&(card[i][j + 4] == 0))
    {
        for(char k = 1; k < 3; k++)
        {
            if(card[i][j + k] == 0)
            {
                cas1 = k;
                i1 ++;
            }
        }
        if((i1 == 1)&&(card[i][j + cas1] == 0))
        {
            if(proba[i][j + cas1] < prob)
                proba[i][j + cas1] = prob ;
           // else
             //   proba[i][j + cas1] = prob/10 + proba[i][j + cas1];
        }
    }
    if((i > 0)&&(card[i][j] == 1)&&(i + 4 < NL)&&(card[i + 4][j] == 0)&&(card[i - 1][j] == 0)&&(card[i + 3][j] == 1))
    {
        for(char k = 1; k < 3; k++)
        {
            if(card[i + k][j] == 0)
            {
                cas2 = k;
                i2 ++;
            }
        }
        if((i2 == 1)&&(card[i + cas2][j] == 0))
        {
            if(proba[i + cas2][j] < prob)
                proba[i + cas2][j] = prob ;//+ proba[i + cas2][j]/10;
            //else
              //  proba[i + cas2][j] = prob/10 + proba[i + cas2][j];
        }
    }
    if((i > 0)&&(j > 0)&&(card[i][j] == 1)&&(i + 4 < NL)&&(j + 4 < NH)&&(card[i + 4][j + 4] == 0)&&(card[i + 3][j + 3] == 1))
    {
        for(char k = 1; k < 3; k++)
        {
            if(card[i + k][j + k] == 0)
            {
                cas3 = k;
                i3 ++;
            }
        }
        if((i3 == 1)&&(card[i + cas3][j + cas3] == 0))
        {
            if(proba[i + cas3][j + cas3] < prob)
                proba[i + cas3][j + cas3] = prob;// + proba[i + cas3][j + cas3]/10;
            //else
              //  proba[i + cas3][j + cas3] = prob/10 + proba[i + cas3][j + cas3];
        }
    }
    if((i + 1 < NH)&&(j > 0)&&(card[i][j] == 1)&&(i > 3)&&(j + 4 < NH)&&(card[i - 4][j + 4] == 0)&&(card[i - 3][j + 3] == 1))
    {
        for(char k = 1; k < 3; k++)
        {
            if(card[i - k][j + k] == 0)
            {
                cas4 = k;
                i4 ++;
            }
        }
        if((i4 == 1)&&(card[i - cas4][j + cas4] == 0))
        {
            if(proba[i - cas4][j + cas4] < prob)
                proba[i - cas4][j + cas4] = prob ;//+ proba[i - cas4][j + cas4]/10;
            //else
              //  proba[i - cas4][j + cas4] = prob/10 + proba[i - cas4][j + cas4];
        }
    }
}

//tester s'il ya 3 points d'un extrimité vide -> 20
void DefTest5(char card[NL][NH], char proba[NL][NH], char i, char j)
{
    char prob = 20;
    bool cas1 = true, cas2 = true, cas3 = true, cas4 = true;
    if(card[i][j] == 1)
    {
        for(char k = 1; k < 3; k++)
        {
            if(j + 2 < NH)
            {
                if(card[i][j + k] != 1)
                    cas1 = false;
            }
            if(i + 2 < NL)
            {
                if(card[i + k][j] != 1)
                    cas2 = false;
            }
            if((j + 2 < NH)&&(i + 2 < NL))
            {
                if(card[i + k][j + k] != 1)
                    cas3 = false;
            }
            if((j + 2 < NH)&&(i > 1))
            {
                if(card[i - k][j + k] != 1)
                    cas4 = false;
            }
        }
        if((cas1)&&(j + 2 < NH))
        {
            if((j > 0)&&(card[i][j - 1] == 0))
            {
                if(proba[i][j - 1] < prob)
                    proba[i][j - 1] = prob + proba[i][j - 1]/10;
                else
                {
                    if(proba[i][j - 1]%10 + prob/10 > 9)
                        proba[i][j - 1]+=9;
                    else
                        proba[i][j - 1] += prob/10;
                }
            }
            if((j + 3 < NH)&&(card[i][j + 3] == 0))
            {
                if(proba[i][j + 3] < prob)
                    proba[i][j + 3] = prob + proba[i][j + 3]/10;
                else
                {
                    if(proba[i][j + 3]%10 + prob/10 > 9)
                        proba[i][j + 3] += 9;
                    else
                        proba[i][j + 3] += prob/10;
                }
            }
        }
        if((cas2)&&(i + 2 < NL))
        {
            if((i > 0)&&(card[i - 1][j] == 0))
            {
                if(proba[i - 1][j] < prob)
                    proba[i - 1][j] = prob + proba[i - 1][j]/10;
                else
                {
                    if(proba[i - 1][j] %10 + prob/10 > 9)
                        proba[i - 1][j] +=9;
                    else
                        proba[i - 1][j] += prob/10;
                }
            }
            if((i + 3 < NL)&&(card[i + 3][j] == 0))
            {
                if(proba[i + 3][j] < prob)
                    proba[i + 3][j] = prob + proba[i + 3][j]/10;
                else
                {
                    if(proba[i + 3][j]%10 + prob/10 > 9)
                        proba[i + 3][j]+=9;
                    else
                        proba[i + 3][j] += prob/10;
                }
            }
        }
        if((cas3)&&(j + 2 < NH)&&(i + 2 < NL))
        {
            if((i > 0)&&(j > 0)&&(card[i - 1][j - 1] == 0))
            {
                if(proba[i - 1][j - 1] < prob)
                    proba[i - 1][j - 1] = prob + proba[i - 1][j - 1]/10;
                else
                {
                    if(proba[i - 1][j - 1]%10 + prob/10 > 9)
                        proba[i - 1][j - 1] += 9;
                    else
                        proba[i - 1][j - 1] += prob/10;
                }
            }
            if((i + 3 < NL)&&(j + 3< NH)&&(card[i + 3][j + 3] == 0))
            {
                if(proba[i + 3][j + 3] < prob)
                    proba[i + 3][j + 3] = prob + proba[i + 3][j + 3]/10;
                else
                {
                    if(proba[i + 3][j + 3]%10 + prob/10 > 9)
                        proba[i + 3][j + 3] += 9;
                    else
                        proba[i + 3][j + 3] += prob/10;
                }
            }
        }
        if((cas4)&&(j + 2 < NH)&&(i > 1))
        {
            if((i + 1 < NL)&&(j > 0)&&(card[i + 1][j - 1] == 0))
            {
                if(proba[i + 1][j - 1] < prob)
                    proba[i + 1][j - 1] = prob + proba[i + 1][j - 1]/10;
                else
                {
                    if(proba[i + 1][j - 1]%10 + prob/10 > 9)
                        proba[i + 1][j - 1] += 9;
                    else
                        proba[i + 1][j - 1] += prob/10;
                }
            }
            if((j + 3 < NH)&&(i > 2)&&(card[i - 3][j + 3] == 0))
            {
                if(proba[i - 3][j + 3] < prob)
                    proba[i - 3][j + 3] = prob + proba[i - 3][j + 3]/10;
                else
                {
                    if(%10 + prob/10 > 9)
                        proba[i - 3][j + 3] += 9;
                    else
                        proba[i - 3][j + 3] += prob/10;
                }
            }
        }
    }
}

//tester s'il ya 2 points de deux extrimité vide -> 40
void DefTest6(char card[NL][NH], char proba[NL][NH], char i, char j)
{
    char prob = 40;
    if(card[i][j] == 1)
    {
        if((card[i][j + 1] == 1)&&(j + 2 < NH)&&(j > 0))
        {
            if((card[i][j + 2] == 0)&&(card[i][j - 1] == 0)&&(j + 3 < NH))
            {
                if(proba[i][j + 2] < prob)
                    proba[i][j + 2] = prob + proba[i][j + 2]/10;
                else
                {
                    if(proba[i][j + 2]%10 + prob/10 > 9)
                        proba[i][j + 2]+=9;
                    else
                        proba[i][j + 2]+=prob/10;
                }
            }
        }
        if((card[i + 1][j] == 1)&&(i + 2 < NL)&&(i > 0))
        {
            if((card[i + 2][j] == 0)&&(card[i - 1][j] == 0)&&(i + 3 < NL))
            {
                if(proba[i + 2][j] < prob)
                    proba[i + 2][j] = prob + proba[i + 2][j]/10;
                else
                {
                    if(proba[i + 2][j]%10 + prob/10 > 9)
                        proba[i + 2][j]+=9;
                    else
                        proba[i + 2][j]+= prob/10;
                }
            }
        }
        if((card[i + 1][j + 1] == 1)&&(j + 2 < NH)&&(j > 0)&&(i + 2 < NL)&&(i > 0))
        {
            if((card[i + 2][j + 2] == 0)&&(card[i - 1][j - 1] == 0)&&(j + 3 < NH)&&(i + 3 < NL))
            {
                if(proba[i + 2][j + 2] < prob)
                    proba[i + 2][j + 2] = prob + proba[i + 2][j + 2]/10;
                else
                {
                    if(proba[i + 2][j + 2]%10 + prob/10 > 9)
                        proba[i + 2][j + 2]+=9;
                    else
                        proba[i + 2][j + 2]+=prob/10;
                }
            }
        }
        if((card[i - 1][j + 1] == 1)&&(j + 2 < NH)&&(j > 0)&&(i + 1 < NL)&&(i > 1))
        {
            if((card[i - 2][j + 2] == 0)&&(card[i + 1][j - 1] == 0)&&(j + 3 < NH)&&(i > 2))
            {
                if(proba[i - 2][j + 2] < prob)
                    proba[i - 2][j + 2] = prob + proba[i - 2][j + 2]/10;
                else
                {
                    if(proba[i - 2][j + 2]%10 + prob/10 > 9)
                        proba[i - 2][j + 2]+=9;
                    else
                        proba[i - 2][j + 2]+=prob/10;
                }
            }
        }
    }
}

//tester s'il y a 4 points d'un extrimité vide -> 100
void AttTest1(char card[NL][NH], char proba[NL][NH], char i, char j)
{
    char prob = 100;
    bool cas1 = true, cas2 = true, cas3 = true, cas4 = true;
    if(card[i][j] == 2)
    {
        for(char k = 1; k < 4; k++)
        {
            if(j + 3 < NH)
            {
                if(card[i][j + k] != 2)
                    cas1 = false;
            }
            if(i + 3 < NL)
            {
                if(card[i + k][j] != 2)
                    cas2 = false;
            }
            if((j + 3 < NH)&&(i + 3 < NL))
            {
                if(card[i + k][j + k] != 2)
                    cas3 = false;
            }
            if((j + 3 < NH)&&(i > 2))
            {
                if(card[i - k][j + k] != 2)
                    cas4 = false;
            }
        }
        if((cas1)&&(j + 3 < NH))
        {
            if((j > 0)&&(card[i][j - 1] == 0))
                proba[i][j - 1] = prob;
            if((j < NH - 4)&&(card[i][j + 4] == 0))
                proba[i][j + 4] = prob;
        }
        if((cas2)&&(i + 3 < NL))
        {
            if((i > 0)&&(card[i - 1][j] == 0))
                proba[i - 1][j] = prob;
            if((i < NL - 4)&&(card[i + 4][j] == 0))
                proba[i + 4][j] = prob;
        }
        if((cas3)&&(j + 3 < NH)&&(i + 3 < NL))
        {
            if((i > 0)&&(j > 0)&&(card[i - 1][j - 1] == 0))
                proba[i - 1][j - 1] = prob;
            if((i < NL - 4)&&(j < NH - 4)&&(card[i + 4][j + 4] == 0))
                proba[i + 4][j + 4] = prob;
        }
        if((cas4)&&(j + 3 < NH)&&(i > 2))
        {
            if((i < NL - 1)&&(j > 0)&&(card[i + 1][j - 1] == 0))
                proba[i + 1][j - 1] = prob;
            if((j < NH - 4)&&(i > 3)&&(card[i - 4][j + 4] == 0))
                proba[i - 4][j + 4] = prob;
        }
    }
}

//tester s'il y a 1 points peut construie 5 points -> 100
void AttTest2(char card[NL][NH], char proba[NL][NH], char i, char j)
{
    char prob = 10;
    for(char i = 0; i < NL; i++)
    {
        for(char j = 0; j < NH; j++)
        {
            char cas1 = 0, cas2 = 0, cas3 = 0, cas4 = 0, i1 = 0, i2 = 0, i3 = 0, i4 = 0;
            if((card[i][j] == 2)&&((j < NL - 4)&&(card[i][j + 4] == 2)))
            {
                for(char k = 1; k < 4; k++)
                {
                     if(card[i][j + k] != 2)
                     {
                         cas1 = k;
                         i1 ++;
                     }
                }
                if((i1 == 1)&&(card[i][j + cas1] == 0))
                    proba[i][j + cas1] = prob;
            }
            if((card[i][j] == 2)&&((i < NH - 4)&&(card[i + 4][j] == 2)))
            {
                for(char k = 1; k < 4; k++)
                {
                     if(card[i + k][j] != 2)
                     {
                         cas2 = k;
                         i2 ++;
                     }
                }
                if((i2 == 1)&&(card[i + cas2][j] == 0))
                    proba[i + cas2][j] = prob;
            }
            if((card[i][j] == 2)&&((i < NH - 4)&&(j < NL - 4)&&(card[i + 4][j + 4] == 2)))
            {
                for(char k = 1; k < 4; k++)
                {
                     if(card[i + k][j + k] != 2)
                     {
                         cas3 = k;
                         i3 ++;
                     }
                }
                if((i3 == 1)&&(card[i + cas3][j + cas3] == 0))
                    proba[i + cas3][j + cas3] = prob;
            }
            if((card[i][j] == 2)&&((i >= 4)&&(j < NL - 4)&&(card[i - 4][j + 4] == 2)))
            {
                for(char k = 1; k < 4; k++)
                {
                     if(card[i - k][j + k] != 2)
                     {
                         cas4 = k;
                         i4 ++;
                     }
                }
                if((i4 == 1)&&(card[i - cas4][j + cas4] == 0))
                    proba[i - cas4][j + cas4] = prob;
            }
        }
    }
}

//tester s'il y a 3 points de deux extrimités vide -> 80
void AttTest3(char card[NL][NH], char proba[NL][NH], char i, char j)
{
    char prob = 80;
    bool cas1 = true, cas2 = true, cas3 = true, cas4 = true;
    if(card[i][j] == 2)
    {
        for(char k = 1; k < 3; k++)
        {
            if(card[i][j + k] != 2)
                cas1 = false;
            if(card[i + k][j] != 2)
                cas2 = false;
            if(card[i + k][j + k] != 2)
                cas3 = false;
            if((i >= 3)&&(card[i - k][j + k] != 2))
                cas4 = false;
        }
        if(cas1)
        {
            if(((j > 0)&&(card[i][j - 1] == 0))&&((j < NH - 3)&&(card[i][j + 3] == 0)))
            {
                if(proba[i][j - 1] < prob)
                    proba[i][j - 1] = prob ;//+ proba[i][j - 1]/10;
                //else
                  //  proba[i][j - 1] += prob/10;
                if(proba[i][j + 3] < prob)
                    proba[i][j + 3] = prob;// +  proba[i][j + 3]/10;
                //else
                  //   proba[i][j + 3] += prob/10;
            }
        }
        if(cas2)
        {
            if(((i > 0)&&(card[i - 1][j] == 0))&&((i < NL - 3)&&(card[i + 3][j] == 0)))
            {
                if(proba[i - 1][j] < prob)
                    proba[i - 1][j] = prob;// + proba[i - 1][j]/10;
                //else
                  //  proba[i - 1][j] += prob/10;
                if(proba[i + 3][j] < prob)
                    proba[i + 3][j] = prob;// + proba[i + 3][j]/10;
                //else
                   // proba[i + 3][j] += prob/10;
            }
        }
        if(cas3)
        {
            if(((i > 0)&&(j > 0)&&(card[i - 1][j - 1] == 0))&&((i < NL - 3)&&(j < NH - 3)&&(card[i + 3][j + 3] == 0)))
            {
                if(proba[i - 1][j - 1] < prob)
                    proba[i - 1][j - 1] = prob ;//+  proba[i - 1][j - 1]/10;
                //else
                  //    proba[i - 1][j - 1] += prob/10;
                if(proba[i + 3][j + 3] < prob)
                    proba[i + 3][j + 3] = prob ;//+ proba[i + 3][j + 3]/10;
                //else
                  //  proba[i + 3][j + 3] += prob/10;
            }
        }
        if((cas4)&&(i >= 3))
        {
            if(((i < NL - 3)&&(j > 0)&&(card[i + 1][j - 1] == 0))&&((j < NH - 3)&&(card[i - 3][j + 3] == 0)))
            {
                if(proba[i + 1][j - 1] < prob)
                    proba[i + 1][j - 1] = prob;// + proba[i + 1][j - 1]/10;
                //else
                  //  proba[i + 1][j - 1] += prob/10;
                if(proba[i - 3][j + 3] < prob)
                    proba[i - 3][j + 3] = prob;// + proba[i - 3][j + 3]/10;
              // else
                //    proba[i - 3][j + 3] += prob/10;
            }
        }
    }
}

//tester s'il y a 1 points peut construire 4 points de deux extrimité vide -> 80
void AttTest4(char card[NL][NH], char proba[NL][NH], char i, char j)
{
    char prob = 80;
    char cas1 = 0, cas2 = 0, cas3 = 0, cas4 = 0, i1 = 0, i2 = 0, i3 = 0, i4 = 0;
    if((j > 0)&&(card[i][j] == 2)&&(j + 4 < NH)&&(card[i][j + 3] == 2)&&(card[i][j - 1] == 0)&&(card[i][j + 4] == 0))
    {
        for(char k = 1; k < 3; k++)
        {
            if(card[i][j + k] == 0)
            {
                cas1 = k;
                i1 ++;
            }
        }
        if((i1 == 1)&&(card[i][j + cas1] == 0))
        {
            if(proba[i][j + cas1] < prob)
                proba[i][j + cas1] = prob ;//+ proba[i][j + cas1]/10;
           // else
             //   proba[i][j + cas1]+= prob/10;
        }
    }
    if((i > 0)&&(card[i][j] == 2)&&(i + 4 < NL)&&(card[i + 4][j] == 0)&&(card[i - 1][j] == 0)&&(card[i][j + 3] == 2))
    {
        for(char k = 1; k < 3; k++)
        {
            if(card[i + k][j] == 0)
            {
                cas2 = k;
                i2 ++;
            }
        }
        if((i2 == 1)&&(card[i + cas2][j] == 0))
        {
            if(proba[i + cas2][j] < prob)
                proba[i + cas2][j] = prob;// + proba[i + cas2][j]/10;
            //else
              //  proba[i + cas2][j]+= prob/10;
        }
    }
    if((i > 0)&&(j > 0)&&(card[i][j] == 2)&&(i + 4 < NL)&&(j + 4 < NH)&&(card[i + 4][j + 4] == 0)&&(card[i + 3][j + 3] == 2))
    {
        for(char k = 1; k < 3; k++)
        {
            if(card[i + k][j + k] == 0)
            {
                cas3 = k;
                i3 ++;
            }
        }
        if((i3 == 1)&&(card[i + cas3][j + cas3] == 0))
        {
            if(proba[i + cas3][j + cas3] < prob)
                proba[i + cas3][j + cas3] = prob;// + proba[i + cas3][j + cas3]/10;
            //else
              //  proba[i + cas3][j + cas3]+=prob/10;
        }
    }
    if((i + 1 < NH)&&(j > 0)&&(card[i][j] == 2)&&(i > 3)&&(j + 4 < NH)&&(card[i - 4][j + 4] == 0)&&(card[i - 3][j + 3] == 2))
    {
        for(char k = 1; k < 3; k++)
        {
            if(card[i - k][j + k] == 0)
            {
                cas4 = k;
                i4 ++;
            }
        }
        if((i4 == 1)&&(card[i - cas4][j + cas4] == 0))
        {
            if(proba[i - cas4][j + cas4] < prob)
                proba[i - cas4][j + cas4] = prob ;//+ proba[i - cas4][j + cas4]/10;
            //else
              //  proba[i - cas4][j + cas4]+=prob/10;
        }
    }
}

//tester s'il ya 3 points d'un extrimité vide -> 50
void AttTest5(char card[NL][NH], char proba[NL][NH], char i, char j)
{
    char prob = 50;
    bool cas1 = true, cas2 = true, cas3 = true, cas4 = true;
    if(card[i][j] == 2)
    {
        for(char k = 1; k < 3; k++)
        {
            if(j + 2 < NH)
            {
                if(card[i][j + k] != 2)
                    cas1 = false;
            }
            if(i + 2 < NL)
            {
                if(card[i + k][j] != 2)
                    cas2 = false;
            }
            if((j + 2 < NH)&&(i + 2 < NL))
            {
                if(card[i + k][j + k] != 2)
                    cas3 = false;
            }
            if((j + 2 < NH)&&(i > 1))
            {
                if(card[i - k][j + k] != 2)
                    cas4 = false;
            }
        }
        if((cas1)&&(j + 2 < NH))
        {
            if((j > 0)&&(card[i][j - 1] == 0))
            {
                if(proba[i][j - 1] < prob)
                    proba[i][j - 1] = prob;
            }
            if((j + 3 < NH)&&(card[i][j + 3] == 0))
            {
                if(proba[i][j + 3] < prob)
                    proba[i][j + 3] = prob;
            }
        }
        if((cas2)&&(i + 2 < NL))
        {
            if((i > 0)&&(card[i - 1][j] == 0))
            {
                if(proba[i - 1][j] < prob)
                    proba[i - 1][j] = prob;
            }
            if((i + 3 < NL)&&(card[i + 3][j] == 0))
            {
                if(proba[i + 3][j] < prob)
                    proba[i + 3][j] = prob;
            }
        }
        if((cas3)&&(j + 2 < NH)&&(i + 2 < NL))
        {
            if((i > 0)&&(j > 0)&&(card[i - 1][j - 1] == 0))
            {
                if(proba[i - 1][j - 1] < prob)
                    proba[i - 1][j - 1] = prob;
            }
            if((i + 3 < NL)&&(j + 3< NH)&&(card[i + 3][j + 3] == 0))
            {
                if(proba[i + 3][j + 3] < prob)
                    proba[i + 3][j + 3] = prob;
            }
        }
        if((cas4)&&(j + 2 < NH)&&(i > 1))
        {
            if((i + 1 < NL)&&(j > 0)&&(card[i + 1][j - 1] == 0))
            {
                if(proba[i + 1][j - 1] < prob)
                    proba[i + 1][j - 1] = prob;
            }
            if((j + 3 < NH)&&(i > 2)&&(card[i - 3][j + 3] == 0))
            {
                if(proba[i - 3][j + 3] < prob)
                    proba[i - 3][j + 3] = prob;
            }
        }
    }
}

//mettre un point à cote de deux autres -> 30
void AttTest6(char card[NL][NH], char proba[NL][NH], char i, char j)
{
    char prob = 30;
    if(card[i][j] == 2)
    {
        if((card[i][j + 1] == 2)&&(j + 2 < NH)&&(j > 0))
        {
            if((card[i][j + 2] == 0)&&(card[i][j + 3] == 0)&&(card[i][j - 1] == 0)&&(j + 3 < NH))
            {
                if(proba[i][j + 2] < prob)
                    proba[i][j + 2] = prob;
            }
            if((card[i][j + 2] == 0)&&(card[i][j - 1] == 0)&&(j > 1)&&(card[i][j - 2] == 0))
            {
                if(proba[i][j - 1] < prob)
                    proba[i][j - 1] = prob;
            }
        }
        if((card[i + 1][j] == 2)&&(i + 2 < NL)&&(i > 0))
        {
            if((card[i + 2][j] == 0)&&(card[i + 3][j] == 0)&&(card[i - 1][j] == 0)&&(i + 3 < NL))
            {
                if(proba[i + 2][j] < prob)
                    proba[i + 2][j] = prob;
            }
            if((card[i + 2][j] == 0)&&(card[i - 1][j] == 0)&&(i > 1)&&(card[i - 2][j] == 0))
            {
                if(proba[i - 1][j] < prob)
                    proba[i - 1][j] = prob;
            }
        }
        if((card[i + 1][j + 1] == 2)&&(j + 2 < NH)&&(j > 0)&&(i + 2 < NL)&&(i > 0))
        {
            if((card[i + 2][j + 2] == 0)&&(card[i + 3][j + 3] == 0)&&(card[i - 1][j - 1] == 0)&&(j + 3 < NH)&&(i + 3 < NL))
            {
                if(proba[i + 2][j + 2] < prob)
                    proba[i + 2][j + 2] = prob;
            }
            if((card[i + 2][j + 2] == 0)&&(card[i - 1][j - 1] == 0)&&(i > 1)&&(j > 1)&&(card[i - 2][j - 2] == 0))
            {
                if(proba[i - 1][j - 1] < prob)
                    proba[i - 1][j - 1] = prob;
            }
        }
        if((card[i - 1][j + 1] == 2)&&(j + 2 < NH)&&(j > 0)&&(i + 1 < NL)&&(i > 1))
        {
            if((card[i - 2][j + 2] == 0)&&(card[i - 3][j + 3] == 0)&&(card[i + 1][j - 1] == 0)&&(j + 3 < NH)&&(i > 2))
            {
                if(proba[i - 2][j + 2] < prob)
                    proba[i - 2][j + 2] = prob;
            }
            if((card[i - 2][j + 2] == 0)&&(card[i + 1][j - 1] == 0)&&(j > 1)&&(card[i + 2][j - 2] == 0)&&(i + 2 < NL))
            {
                if(proba[i + 1][j - 1] < prob)
                    proba[i + 1][j - 1] = prob;
            }
        }
    }
}

//mettre un point à cote d'un autre -> 10
void AttTest7(char card[NL][NH], char proba[NL][NH], char i, char j)
{
    char prob = 10;
    for(char i = 0; i < NL; i++)
    {
        for(char j = 0; j < NH; j++)
        {
            if(card[i][j] == 2)
            {
                if((card[i][j - 1] == 0)&&(j > 0)&&(card[i][j + 1] == 0)&&(j < NH - 1))
                {
                        if(proba[i][j - 1] < prob)
                            proba[i][j - 1] = prob;
                        if(proba[i][j + 1] < prob)
                            proba[i][j + 1] = prob;
                }
                if((card[i - 1][j] == 0)&&(i > 0)&&(card[i + 1][j] == 0)&&(i < NL - 1))
                {
                        if(proba[i - 1][j] < prob)
                            proba[i - 1][j] = prob;
                        if(proba[i + 1][j] < prob)
                            proba[i + 1][j] = prob;
                }
                if((card[i - 1][j - 1] == 0)&&(i > 0)&&(j > 0)&&(card[i + 1][j + 1] == 0)&&(i < NL - 1)&&(j < NH - 1))
                {
                        if(proba[i - 1][j - 1] < prob)
                            proba[i - 1][j - 1] = prob;
                        if(proba[i + 1][j + 1] < prob)
                            proba[i + 1][j + 1] = prob;
                }
                if((card[i - 1][j + 1] == 0)&&(i > 0)&&(j < NH - 1)&&(card[i + 1][j - 1] == 0)&&(i < NL - 1)&&(j > 0))
                {
                        if(proba[i - 1][j + 1] < prob)
                            proba[i - 1][j + 1] = prob;
                        if(proba[i + 1][j - 1] < prob)
                            proba[i + 1][j - 1] = prob;
                }
            }
        }
    }
}

void put(char card[NL][NH], char proba[NL][NH], short *nbr)
{
    char cas = -1;
    short k = 0, x = 0, p = 0, t = 0;
    bool play = false;
    for(char i = 0; i < NL; i++)
    {
        for(char j = 0; j < NH; j++)
        {
            if(proba[i][j] > cas)
                cas = proba[i][j];
        }
    }
    for(char i = 0; i < NL; i++)
    {
        for(char j = 0; j < NH; j++)
        {
            if(proba[i][j] == cas)
                p++;
        }
    }
    x = (rand()%(p)) + 1;
    for(char i = 0; i < NL; i++)
    {
        for(char j = 0; j < NH; j++)
        {
            if(proba[i][j] == cas)
            {
                k++;
                t = card[i][j];
                if((k == x)&&(card[i][j] == 0))
                {
                    card[i][j] = 2;
                    proba[i][j] = -2;
                    fprintf(stdout, "%i):cas = %i, (x = %i)/(p = %i),  i= %i  j = %i, card = %i\n", *nbr, cas, x, p, i, j, t);
                    i = NL;
                    j = NH;
                    *nbr+=1;
                    play = true;
                }
            }
        }
    }
    if(!play)
        fprintf(stdout, "%i):erreur car cas = %i, (x = %i)/(p = %i), k = %i , card = %i\n", *nbr, cas, x, p, k, t);
}
