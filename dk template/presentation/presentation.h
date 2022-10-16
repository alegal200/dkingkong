#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <SDL/SDL.h>

void ouvrirFenetreGraphique();

void afficherCle(int num);
void afficherCorbeau(int colonne, int num);
void afficherCroco(int colonne, int num);
void afficherDKJr(int ligne, int colonne, int num);
void afficherCage(int num);
void afficherRireDK();
void afficherEchec(int nbEchecs);
void afficherScore(int score);
void afficherChiffre(int ligne, int colonne, int chiffre);

void effacerCarres(int ligne, int colonne, int nbLignes = 1, int nbColonnes = 1);
void effacerPoints(int x, int y, int nbX = 1, int nbY = 1);

int lireEvenement();

#endif
