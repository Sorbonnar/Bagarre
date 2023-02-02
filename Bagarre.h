#ifndef __BAGARRE__
#define __BAGARRE__

#include <stdio.h>


#define TIME_TIME 1000	    	/* Temps pour jouer */


typedef struct 
{
	int N, E, S, W;
    int Item;

} t_tile;



typedef struct {

	t_tile *taby;
    int toz;
    int x, y;

} t_laby;


void Bagarre(int *t);

void Recuperation(int *Laby, t_tile *Labo, t_tile *Exotuile, int x, int y);

void ExoTuile(t_tile *ExoTuile, t_move move);



#endif