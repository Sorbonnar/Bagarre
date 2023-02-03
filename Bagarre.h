#ifndef __BAGARRE__
#define __BAGARRE__

#include <stdio.h>

//Structure de tuile qui composent le labyrinthe
typedef struct 
{
    //Murs
	int N, E, S, W;
    //L'objet
    int Item;
    //Le chemin de l'expansion
    int Cheminot;

} t_tile;


/* Fonction Mohamed Ali pour jouer manuellement
Elle prend en entrée t qui indique si c'est le joueur ou l'adversaire qui doit commencer*/
void MohamedAli(int *t);

/* Fonction Recuperation qui permet de récuperer le labyrinthe dans une forme plus facilement exploitable pour l'expansion
Elle prend en entrée l'ancien labyrinthe, le nouveau et la taille du labyrinthe*/
void Recuperation(int *Laby, t_tile *Labo, int x, int y);

/* Fonction Exotuile pour récuperer la tuile exterieur
Elle prend en entrée un pointeur vers une tuile ainsi qu'un t_move pour récuperer les informations de la tuile*/
void ExoTuile(t_tile *ExoTuile, t_move move);

/* Fonction Party qui se connecte au serveur
Elle prend en entrée une chaîne de caractères qui servira a stocker le nom ainsi que deux pointeurs qui serviront à récuperer la taille du labyrinthe*/
void Party(char nom[50], int *x, int *y);

/* Fonction Expansion qui servira à parcourir le labyrinthe.
Elle prend en entrée le labyrinthe, un t_move pour accéder au prochain objet, la taille du labyrinthe et la position du joueur*/
int RyoikiTenkai(t_tile *Labo, t_move move, int x, int y, int *O, int *M);

/* Fonction Mike Tyson qui servira à jouer automatiquement.
Elle prend en entrée l'ancien labyrinthe, le nouveau, la tuile externe, la taille du labyrinthe et t qui indique si c'est le bot ou l'adversaire qui doit commencer*/
void MikeTyson(int *Laby, t_tile *Labo, t_tile *ExoTuile, int x, int y, int *t);



#endif