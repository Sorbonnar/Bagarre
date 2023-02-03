#include <stdlib.h>
#include <stdio.h>
#include "LabyrinthAPI.h"
#include "Bagarre.h"



int main() {

    //La taille du layrinthe et le tour
    int x, y, t;
    
    //Le 1er labyrinthe
    int *Laby = NULL;

    //Le second labyrinthe
    t_tile *Labo = NULL;

    //La tuile externe
    t_tile *ExoTuile;

    //Les informations de la tuile externe au debut
    int N, E, S, W, Item;

    //Le nom de la partie
    char Nom[50];

    //On récupère la partie
    Party(Nom, &x, &y);

    //On alloue la taille nécessaire telle que donnée par le serveur
    Laby = malloc((x * y * 5 * sizeof(int)));

    Labo = malloc((x * y * sizeof(t_tile)));

    //On récupère le labyrinthe
    t = getLabyrinth(Laby, &N, &E, &S, &W, &Item);

    ExoTuile->N = N;
    ExoTuile->E = E;
    ExoTuile->S = S;
    ExoTuile->W = W;
    
    printLabyrinth();
    
    //Le bot qui va jouer automatiquement
    MikeTyson(Laby, Labo, ExoTuile, x, y, &t);

    closeConnection();

    return 555;

}