#include <stdlib.h>
#include <stdio.h>
#include "LabyrinthAPI.h"
#include "Bagarre.h"




void Recuperation(int *Laby, t_tile *Labo, t_tile *Exotuile, int x, int y) {

    int i, j, k = 0;
    
    t_tile pol;

    for (i = 0; i < x; i++) {

        for (j = 0; j < y; j++) {

            pol.N = Laby[5 * k];
            pol.E = Laby[5 * k + 1];
            pol.S = Laby[5 * k + 2];
            pol.W = Laby[5 * k + 3];
            pol.Item = Laby[5 * k + 4];

            Labo[k] = pol;

            k++;

        }

    }

}


void ExoTuile(t_tile *ExoTuile, t_move move) {

    ExoTuile->N = move.tileN;

    ExoTuile->E = move.tileE;

    ExoTuile->S = move.tileS;

    ExoTuile->W = move.tileW;

    ExoTuile->Item = move.tileItem;

}


/*void Insertion(t_tile *Labo, t_move move) {
    
    t_tile pol;

    for (i = 0; i < x; i++) {

        for (j = 0; j < y; j++) {

            pol.N = Laby[5 * k];
            pol.E = Laby[5 * k + 1];
            pol.S = Laby[5 * k + 2];
            pol.W = Laby[5 * k + 3];
            pol.Item = Laby[5 * k + 4];

            Labo[k] = pol;

            k++;

        }

    }

}*/


void Bagarre(int *t) {

    int x, m;
    t_move move;

    m = NORMAL_MOVE;

    while (m == NORMAL_MOVE) {

        if (*t == 0) {

            printf("Please insert the type of insertion (0 to 3), the column or line number and the rotation of the tile (0 to 3)\n");

            scanf(" %d %d %d", &x, &move.number, &move.rotation);

            move.insert = x; // Pour éviter l'affichage de l'erreur de type entre int et enum


            printf("Please insert the coordinates where you want to go\n");

            scanf(" %d %d", &move.x, &move.y);


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