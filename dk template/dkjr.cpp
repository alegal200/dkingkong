#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <SDL/SDL.h>
#include "./presentation/presentation.h"

#define DEBUG false 
#define VIDE        		0
#define DKJR       		1
#define CROCO       		2
#define CORBEAU     		3
#define CLE 			4

#define AUCUN_EVENEMENT    	0

#define LIBRE_BAS		1
#define LIANE_BAS		2
#define DOUBLE_LIANE_BAS	3
#define LIBRE_HAUT		4
#define LIANE_HAUT		5

#define DROITE  	 	1
#define GAUCHE   		2

void* FctThreadEvenements(void *);
void* FctThreadCle(void *);
void* FctThreadDK(void *);
void* FctThreadDKJr(void *);
void* FctThreadScore(void *);
void* FctThreadEnnemis(void *);
void* FctThreadCorbeau(void *);
void* FctThreadCroco(void *);

void initGrilleJeu();
void setGrilleJeu(int l, int c, int type = VIDE, pthread_t tid = 0);
void afficherGrilleJeu();

void HandlerSIGUSR1(int);
void HandlerSIGUSR2(int);
void HandlerSIGALRM(int);
void HandlerSIGINT(int);
void HandlerSIGQUIT(int);
void HandlerSIGCHLD(int);
void HandlerSIGHUP(int);

void DestructeurVS(void *p);

pthread_t threadCle;
pthread_t threadDK;
pthread_t threadDKJr;
pthread_t threadEvenements;
pthread_t threadScore;
pthread_t threadEnnemis;

pthread_cond_t condDK;
pthread_cond_t condScore;

pthread_mutex_t mutexGrilleJeu;
pthread_mutex_t mutexDK;
pthread_mutex_t mutexEvenement;
pthread_mutex_t mutexScore;

pthread_key_t keySpec;

bool MAJDK = false;
int  score = 0;
bool MAJScore = true;
int  delaiEnnemis = 4000;
int  positionDKJr = 1;
int  evenement = AUCUN_EVENEMENT;
int etatDKJr;

typedef struct
{
  int type;
  pthread_t tid;
} S_CASE;

S_CASE grilleJeu[4][8];

typedef struct
{
  bool haut;
  int position;
} S_CROCO;

// ------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	int evt;
	pthread_mutex_init(&mutexGrilleJeu, NULL);	



	ouvrirFenetreGraphique();
	////////////////////////////////////////////////////////////////////////////
	//////////////////	affichage initial ! ////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	afficherCage(1);
	afficherCage(2);
	afficherCage(3);
	afficherCage(4);
	// afficherRireDK();
		// creation d un thread ici
	//afficherCle(3);
	/* afficherCroco(11, 2);
	// afficherCroco(17, 1);
	afficherCroco(0, 3);
	afficherCroco(12, 5);
	afficherCroco(18, 4);

*/

//	afficherDKJr(11, 9, 1);
//	afficherDKJr(6, 19, 7);
	afficherDKJr(0, 0, 9);
	
/*	afficherCorbeau(10, 2);
	afficherCorbeau(16, 1);
	
	effacerCarres(9, 10, 2, 1);

	afficherEchec(1);
	afficherScore(1999);


*/
	afficherScore(0);

	int *p ; 
	
	p = (int*) malloc(sizeof((void*) p));
	pthread_create(&threadCle ,NULL ,FctThreadCle ,(void *)p);

	
	
	
	while (1)
	{
	    evt = lireEvenement();

	    switch (evt)
	    {
		case SDL_QUIT:
			exit(0);
		case SDLK_UP:
			printf("KEY_UP\n");
			break;
		case SDLK_DOWN:
			printf("KEY_DOWN\n");
			break;
		case SDLK_LEFT:
			printf("KEY_LEFT\n");
			break;
		case SDLK_RIGHT:
			printf("KEY_RIGHT\n");
	    }
	}
}

// -------------------------------------

void initGrilleJeu()
{
  int i, j;   
  
  pthread_mutex_lock(&mutexGrilleJeu);

  for(i = 0; i < 4; i++)
    for(j = 0; j < 7; j++)
      setGrilleJeu(i, j);

  pthread_mutex_unlock(&mutexGrilleJeu);
}

// -------------------------------------

void setGrilleJeu(int l, int c, int type, pthread_t tid)
{
  grilleJeu[l][c].type = type;
  grilleJeu[l][c].tid = tid;
}

// -------------------------------------

void afficherGrilleJeu()
{   
   for(int j = 0; j < 4; j++)
   {
       for(int k = 0; k < 8; k++)
          printf("%d  ", grilleJeu[j][k].type);
       printf("\n");
   }

   printf("\n");   
}



// -------------------------------------------------
// todo 
// check if the timing is correct 

void* FctThreadCle(void *){


	int time = 1 ;
	struct timespec temps = { 1, 700000000 };
	bool sence  = true;

	while(1){
		effacerCarres(3, 12, 4, 14);		
		pthread_mutex_lock(&mutexGrilleJeu);  
			
		if(sence)
			time ++ ;
		else
			time-- ;
		if(time >= 4 || time <= 1)	// pour faire balancer dans les 2 sences
			sence = !sence ;
		if(DEBUG)
			printf("sence = %d et time %d \n",sence,time);

		if(time == 1 ){
				grilleJeu[0][1].type = CLE ;
		}else{
				grilleJeu[0][1].type = VIDE ;
		}
		afficherCle(time) ; 
		pthread_mutex_unlock(&mutexGrilleJeu); 
		nanosleep(&temps, NULL) ; 

	}


}

//------------------------------------------------