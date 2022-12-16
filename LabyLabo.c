#include <stdlib.h>
#include <stdio.h>
#include "LabyrinthAPI.h"




int main() {

    int x, y;
    int *Laby = NULL;
    int tileN, tileE, tileS, tileW, tileItem;
    char Nom[50];

    connectToServer("172.105.76.204", 1234, "Mohamed");

    waitForLabyrinth("TRAINING DONTMOVE display=debug", Nom, &x, &y);

    Laby = malloc((x*y*5*sizeof(int)));

    getLabyrinth(Laby, &tileN, &tileE, &tileS, &tileW, &tileItem);
    
    printLabyrinth();

    closeConnection();

    return 555;

}