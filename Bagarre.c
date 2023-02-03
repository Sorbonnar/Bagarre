#include <stdlib.h>
#include <stdio.h>
#include "LabyrinthAPI.h"
#include "Bagarre.h"



/* Fonction Party qui se connecte au serveur
Elle prend en entrée une chaîne de caractères qui servira a stocker le nom ainsi que deux pointeurs qui serviront à récuperer la taille du labyrinthe*/
void Party(char Nom[50], int *x, int *y) {

    connectToServer("172.105.76.204", 5678, "Mike_Tyson");

    waitForLabyrinth("TRAINING DONTMOVE", Nom, x, y);

}

/* Fonction Recuperation qui permet de récuperer le labyrinthe dans une forme plus facilement exploitable pour l'expansion
Elle prend en entrée l'ancien labyrinthe, le nouveau et la taille du labyrinthe*/
void Recuperation(int *Laby, t_tile *Labo, int x, int y) {

    int i, j, k = 0;
    
    t_tile pol;

    for (i = 0; i < x; i++) {

        for (j = 0; j < y; j++) {

            //On met toutes les valeurs dans une tuile intermediaire pour les stocker dans la bonne case du labyrinthe par la suite
            pol.N = Laby[5 * k];
            pol.E = Laby[5 * k + 1];
            pol.S = Laby[5 * k + 2];
            pol.W = Laby[5 * k + 3];
            pol.Item = Laby[5 * k + 4];
            //Cheminot sert à l'expansion
            pol.Cheminot = 0;

            Labo[k] = pol;

            k++;

        }

    }

}

/* Fonction Exotuile pour récuperer la tuile exterieur
Elle prend en entrée un pointeur vers une tuile ainsi qu'un t_move pour récuperer les informations de la tuile*/
void ExoTuile(t_tile *ExoTuile, t_move move) {

    ExoTuile->N = move.tileN;

    ExoTuile->E = move.tileE;

    ExoTuile->S = move.tileS;

    ExoTuile->W = move.tileW;

    ExoTuile->Item = move.tileItem;

}

/* Fonction Mohamed Ali pour jouer manuellement
Elle prend en entrée t qui indique si c'est le joueur ou l'adversaire qui doit commencer*/
void MohamedAli(int *t) {

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

        sendComment("const char* comment");

        printLabyrinth();

    }

}

/* Fonction Expansion qui servira à parcourir le labyrinthe.
Elle prend en entrée le labyrinthe, un t_move pour accéder au prochain objet, la taille du labyrinthe et la position du joueur*/
int RyoikiTenkai(t_tile *Labo, t_move move, int x, int y, int *O, int *M) {

    //Initialisation des compteurs et de r qui vérifie et w qui compte pour éviter de tourner à l'infini
    int i, j, direction, r = 0, w=0;
    int coord[2];

    while(r != 1){

        //On passe r à 1 et on le changera si les conditions ne sont pas remplis
        r++;

        //si w dépasse un certain nombre, on arrête la boucle
        if (w>100000)
            break;

        //On incrémente w à chaque tour de boucle
        w++;

        //Boucles qui parcourent le tableau
        for(i = *O; i < y; i++){

            for(j = *M; j < x; j++){

                //Si la case n'a pas été verifiée
                if(Labo[i * x + j].Cheminot == 0){

                    //On vérifie chaque directions pour vérifier le chemin qui a été tracé
                    for(direction = 0; direction < 4; direction++){

                        coord[1] = i;

                        coord[0] = j;

                        //Ouest
                        if ((direction == 0) && (Labo[coord[1] * x + coord[0] - 1].E == 0) && (Labo[coord[1] * x + coord[0]].W == 0)) {

                            coord[0]--;

                        }
                        //Sud
                        else if ((direction == 1) && (Labo[(coord[1] + 1) * x + coord[0]].N == 0) && (Labo[coord[1] * x + coord[0]].S == 0)) {

                            coord[1]++;

                        }
                        //Est
                        else if ((direction == 2) && (Labo[coord[1] * x + coord[0] + 1].W == 0) && (Labo[coord[1] * x + coord[0]].E == 0)) {

                            coord[0]++;

                        }
                        //Nord
                        else if ((direction == 3) && (Labo[(coord[1] - 1) * x + coord[0]].S == 0) && (Labo[coord[1] * x + coord[0]].N == 0)) {

                            coord[1]--;

                        }


                        if(Labo[coord[1] * x + coord[0]].Cheminot > 0){

                            //Si la case a été compté, on met la case actuelle à la valeur suivante
                            Labo[i * x + j].Cheminot = Labo[coord[1] * x + coord[0]].Cheminot + 1;

                            //On effectue un changement donc on passe r à 0 pour continuer la boucle à partir de la case changée
                            r = 0;

                        }

                        if ((Labo[coord[1] * x + coord[0]].Item == move.nextItem) && (Labo[i * x + j].Cheminot != 0)) {

                            *O = coord[1];
                            *M = coord[0];

                            return 1;

                        }

                    }

                }

            }

        }

        r = 1;

        //On vérifie si tout le tableau à été parcourus
        for(i = 0; i < y; i++){

            for(j = 0; j < x; j++){

                if(Labo[i * x + j].Cheminot == 0){

                    //Il reste des cases sans valeurs donc on passe r à 0 pour continuer la boucle
                    r = 0;

                }

            }

        }

    }

    return 0;

}

/* Fonction Mike Tyson qui servira à jouer automatiquement.
Elle prend en entrée l'ancien labyrinthe, le nouveau, la tuile externe, la taille du labyrinthe et t qui indique si c'est le bot ou l'adversaire qui doit commencer*/
void MikeTyson(int *Laby, t_tile *Labo, t_tile *ExoTuile, int x, int y, int *t) {

    t_move move;
    int O = 0, M = 0, r = 0, l, w;

    //Le bot joue aléatoirement parmis les coups autorisés
    srand(time(NULL));

    l = NORMAL_MOVE;

    while (l == NORMAL_MOVE) {

        Recuperation(Laby, Labo, x, y);

        r = RyoikiTenkai(Labo, move, x, y, &O, &M);

        if (*t == 0) {

            w = rand() % 4;
            move.insert = w;

            move.rotation = rand() % 4;

            if (w <= 1) {
                move.number = (rand() % (y/2)) * 2 + 1;
            }
            else {
                move.number = (rand() % (x/2)) * 2 + 1;
            }

            move.x = M;
            move.y = O;

            l = sendMove(&move);

            //Parfois le bot fait un move illégal car il remet une tuile au même endroit. Je ne sais pas comment faire pour l'éviter.
            //Lorsqu'il commence en étant joueur 2, il y a aussi un problème car il essaye d'aller en 0, 0 et je ne sais pas comment récuperer la position du jouer ou même savoir si on est le joueur 2.

            *t = 1;

        }

        else {

            l = getMove(&move);

            *t = 0;

        }

        sendComment("const char* comment");

        printLabyrinth();

    }

}