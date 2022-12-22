#include <stdlib.h>
#include <stdio.h>
#include "LabyrinthAPI.h"


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


int main() {

    int x, y, t;
    int *Laby = NULL;
    int tileN, tileE, tileS, tileW, tileItem;
    char Nom[50];

    connectToServer("172.105.76.204", 1234, "Mohamed");

    waitForLabyrinth("TRAINING DONTMOVE display=debug seed=000000", Nom, &x, &y);

    Laby = malloc((x*y*5*sizeof(int)));

    t = getLabyrinth(Laby, &tileN, &tileE, &tileS, &tileW, &tileItem);
    
    printLabyrinth();

    
    Bagarre(&t); //Bagarre manuelle


    closeConnection();

    return 555;

}