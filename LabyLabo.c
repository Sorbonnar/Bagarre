#include <stdlib.h>
#include <stdio.h>
#include "LabyrinthAPI.h"
#include "Bagarre.h"



void MikeTysonBot(int *Laby, t_tile *Labo, t_tile *Exotuile, int x, int y) {

    Recuperation(Laby, Labo, Exotuile, x, y);

}


int main() {

    int x, y, t;
    
    int *Laby = NULL;

    t_tile *Labo = NULL;

    t_tile *ExoTuile;

    int N, E, S, W, Item;

    char Nom[50];

    connectToServer("172.105.76.204", 1234, "Mohamed");

    waitForLabyrinth("TRAINING DONTMOVE display=debug seed=000000", Nom, &x, &y);

    Laby = malloc((x * y * 5 * sizeof(int)));

    Labo = malloc((x * y * sizeof(t_tile)));

    t = getLabyrinth(Laby, &N, &E, &S, &W, &Item);

    ExoTuile->N = N;
    ExoTuile->E = E;
    ExoTuile->S = S;
    ExoTuile->W = W;
    
    printLabyrinth();


    Recuperation(Laby, Labo, x, y);

    
    //Bagarre(&t); //Bagarre manuelle


    closeConnection();

    return 555;

}