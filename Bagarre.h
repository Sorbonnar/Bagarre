#ifndef __BAGARRE__
#define __BAGARRE__

#include <stdio.h>


#define TIME_TIME 1000  /* Temps pour jouer */


typedef struct 
{
	int N, E, S, W;
    int Item;
    int Cheminot;

} t_tile;


void MohamedAli(int *t);

void Recuperation(int *Laby, t_tile *Labo, int x, int y);

void ExoTuile(t_tile *ExoTuile, t_move move);

void Party(char nom[50], int *x, int *y);

int RyoikiTenkai(t_tile *Labo, t_move move, int x, int y, int *O, int *M);



#endif