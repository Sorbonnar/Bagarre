#include <stdlib.h>
#include <stdio.h>
#include "LabyrinthAPI.h"
#include "Bagarre.h"



void MohamedAliBot(int *Laby, t_tile *Labo, t_tile *ExoTuile, int x, int y, int *t) {

    t_move move;
    int O = 0, M = 0, r = 0, m, w;

    srand(time(NULL));

    int randomNumber = rand() % (x/2 + 1) * 2;

    m = NORMAL_MOVE;

    while (m == NORMAL_MOVE) {

        Recuperation(Laby, Labo, ExoTuile, x, y);

        r = RyoikiTenkai(Labo, move, x, y, &O, &M);

        if (*t == 0) {

            w = rand() % 4;
            move.insert = w;

            move.rotation = rand() % 4;

            if (w <= 1) {
                move.number = rand() % (y/2 + 1) * 2;
            }
            else {
                move.number = rand() % (x/2 + 1) * 2;
            }

            

            move.x = *M;
            move.y = *O;

            m = sendMove(&move);

            *t = 1;

        }

        else {

            m = getMove(&move);

            *t = 0;

        }

        //sendComment("const char* comment");

        printLabyrinth();

    }

}


int main() {

    int x, y, t;
    
    int *Laby = NULL;

    t_tile *Labo = NULL;

    t_tile *ExoTuile;

    int N, E, S, W, Item;

    char Nom[50];

    Party(Nom, &x, &y);

    Laby = malloc((x * y * 5 * sizeof(int)));

    Labo = malloc((x * y * sizeof(t_tile)));

    t = getLabyrinth(Laby, &N, &E, &S, &W, &Item);

    ExoTuile->N = N;
    ExoTuile->E = E;
    ExoTuile->S = S;
    ExoTuile->W = W;
    
    printLabyrinth();
    
    MohamedAliBot(Laby, Labo, ExoTuile, x, y, &t);

    closeConnection();

    return 555;

}