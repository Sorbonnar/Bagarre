#include <stdlib.h>
#include <stdio.h>
#include "LabyrinthAPI.h"
#include "Bagarre.h"




void Party(char nom[50], int *x, int *y) {

    connectToServer("172.105.76.204", 1234, "Mohamed");

    waitForLabyrinth("TRAINING DONTMOVE display=debug seed=000000", Nom, x, y);

}


void Recuperation(int *Laby, t_tile *Labo, t_tile *ExoTuile, int x, int y) {

    int i, j, k = 0;
    
    t_tile pol;

    for (i = 0; i < x; i++) {

        for (j = 0; j < y; j++) {

            pol.N = Laby[5 * k];
            pol.E = Laby[5 * k + 1];
            pol.S = Laby[5 * k + 2];
            pol.W = Laby[5 * k + 3];
            pol.Item = Laby[5 * k + 4];
            pol.Cheminot = 0;

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


void Insertion(t_tile *Labo, t_move move, t_tile *ExoTuile) {
    
    int t;

    if (move.rotation == 1) {

        t = ExoTuile->N;

        ExoTuile->N = ExoTuile->W;
        ExoTuile->W = ExoTuile->S;
        ExoTuile->S = ExoTuile->E;
        ExoTuile->E = t;

    }
    else if (move.rotation == 2) {

        t = ExoTuile->N;

        ExoTuile->N = ExoTuile->S;
        ExoTuile->S = t;

        t = ExoTuile->E;

        ExoTuile->E = ExoTuile->W;
        ExoTuile->W = t;

    }
    else if (move.rotation == 3) {

        t = ExoTuile->N;

        ExoTuile->N = ExoTuile->E;
        ExoTuile->E = ExoTuile->S;
        ExoTuile->S = ExoTuile->W;
        ExoTuile->W = t;

    }

    




}


void MikeTyson(int *t) {

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


int RyoikiTenkai(t_tile *Labo, t_move move, int x, int y, int *O, int *M) {

    //Initialisation des compteurs et de r qui vérifie et w qui compte pour éviter de tourner à l'infini comme avec le labyrinthe 3
    int i, j, direction, r = 0, w=0;
    int coord[2], coordt[2];

    while(r != 1){

        //On passe r à 1 et on le changera si les conditions ne sont pas remplis
        r++;

        //si w dépasse un certain nombre, on arrête la boucle
        if (w>1000)
            break;

        //On incrémente w à chaque tour de boucle
        w++;

        //Boucles qui parcourent le tableau
        for(i = *O; i < y; i++){

            for(j = *M; j < x; j++){

                //Si la case n'a pas été verifiée
                if(labo[i * y + j].Cheminot == 0){

                    //On vérifie chaque directions pour vérifier le chemin qui a été tracé
                    for(direction = 0; direction < 4; direction++){

                        coord[1] = i;

                        coord[0] = j;

                        //Nord
                        if ((direction == 0) && (labo[(coord[0] - 1) * y + coord[1]].S == 0) && (labo[coord[0] * y + coord[1]].N == 0)) {

                            coord[1]--;

                        }
                        //Est
                        else if ((direction == 1) && (labo[coord[0] * y + coord[1] + 1].W == 0) && (labo[coord[0] * y + coord[1]].W == 0)) {

                            coord[0]++;

                        }
                        //Sud
                        else if ((direction == 2) && (labo[(coord[0] + 1) * y + coord[1]].N == 0) && (labo[coord[0] * y + coord[1]].S == 0)) {

                            coord[1]++;

                        }
                        //Ouest
                        else if ((direction == 3) && (labo[coord[0] * y + coord[1] - 1].E == 0) && (labo[coord[0] * y + coord[1]].W == 0)) {

                            coord[0]--;

                        }

                        if(labo[coord[0] * y + coord[1]].Cheminot > 0){

                            //Si la case a été compté, on met la case actuelle à la valeur suivante
                            labo[i * y + j].Cheminot = labo[coord[0] * y + coord[1]].Cheminot + 1;

                            if (labo[i * y + j].Cheminot == move.nextItem) {

                                *O = j;
                                *M = i;

                                return 1

                            }

                            //On effectue un changement donc on passe r à 0 pour continuer la boucle à partir de la case changée
                            r = 0;

                        }

                    }

                }

            }

        }

        //On vérifie si tout le tableau à été parcourus
        for(i = 0; i < y; i++){

            for(j = 0; j < x; j++){

                if(labo[i * y + j].Cheminot == 0){

                    //Il reste des cases sans valeurs donc on passe r à 0 pour continuer la boucle
                    r = 0;

                }

            }

        }

    }

    return 0;

}