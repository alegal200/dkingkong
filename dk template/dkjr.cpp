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

struct sigaction sigAct;
sigset_t mask;


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
//	afficherDKJr(0, 0, 9);
	
/*	afficherCorbeau(10, 2);
	afficherCorbeau(16, 1);
	
	effacerCarres(9, 10, 2, 1);

	afficherEchec(1);
	afficherScore(1999);


*/
	// sigaunx

	sigemptyset(&sigAct.sa_mask);
	sigAct.sa_handler = HandlerSIGQUIT ;
	sigAct.sa_flags = 0; // 
	sigaction(SIGQUIT, &sigAct, NULL);
	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigprocmask(SIG_BLOCK, &mask, NULL);

	afficherScore(0);

	//int *p ; 	
	//p = (int*) malloc(sizeof((void*) p));
	pthread_create(&threadCle ,NULL ,FctThreadCle , NULL );//,(void *)p);
	pthread_create(&threadEvenements ,NULL ,FctThreadEvenements , NULL);
	pthread_create(&threadDKJr ,NULL ,FctThreadDKJr , NULL );

	while (1){}

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
		effacerCarres(3, 12, 2, 4);		
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

//------------------------------------------------

void* FctThreadEvenements(void * a ){
struct timespec tempsfrap = { 0, 10 }; // todo change time here
while(1){

 int evt = lireEvenement();
 pthread_mutex_lock(&mutexEvenement);

	switch(evt){
		case SDL_QUIT:
			exit(0);
		case SDLK_UP:
			evenement = SDLK_UP ;
			printf("KEY_UP\n");
			// sigkill
			//pthread_kill ();
		break;
		case SDLK_DOWN:
			printf("KEY_DOWN\n");
			evenement = SDLK_DOWN ;
		break;
		case SDLK_LEFT:
			printf("KEY_LEFT\n");
			evenement = SDLK_LEFT ;
		break;
		case SDLK_RIGHT:
			printf("KEY_RIGHT\n");
			evenement = SDLK_RIGHT ;
		//default :
			/*printf("RIEN") ; 
			evenement = AUCUN_EVENEMENT ;*/
			/*thread_mutex_unlock(&mutexEvenement) ;
			continue;*/
		}	
	 pthread_mutex_unlock(&mutexEvenement) ;
	 // sigquit 
	 pthread_kill(threadDKJr, SIGQUIT);

	 nanosleep(&tempsfrap, NULL) ; 

	 pthread_mutex_lock(&mutexEvenement) ;
	 evenement = AUCUN_EVENEMENT ;
	 pthread_mutex_unlock(&mutexEvenement) ;
}



}

//------------------------------------------------
void HandlerSIGQUIT(int a){
	//printf("Handler SIGQUIT appelé");
}


//------------------------------------------------

void* FctThreadDKJr(void *){
	
	bool on = true; 
	// setsignal
	sigemptyset(&mask);
	sigaddset(&mask, SIGQUIT);
	sigprocmask(SIG_UNBLOCK, &mask, NULL);
	
	// afficher le dkjr 
	pthread_mutex_lock(&mutexGrilleJeu);
	setGrilleJeu(3, 1, DKJR); 
	afficherDKJr(11, 9, 1); 
	etatDKJr = LIBRE_BAS; 
	positionDKJr = 1;
	// temps de jumps 
	struct timespec tempsJump = { 1, 5000 }; // todo change time here
	
	pthread_mutex_unlock(&mutexGrilleJeu);
	
	while (on)
	{
		
		pause();
		pthread_mutex_lock(&mutexEvenement);
		pthread_mutex_lock(&mutexGrilleJeu);
		printf("etat de dkjr %d \n" , etatDKJr);
		switch (etatDKJr){
			case LIBRE_BAS:
				switch (evenement){
					case SDLK_LEFT:
					if (positionDKJr > 1){
						setGrilleJeu(3, positionDKJr);
						effacerCarres(11, (positionDKJr * 2) + 7, 2, 2);
						positionDKJr--;
						setGrilleJeu(3, positionDKJr, DKJR);
						afficherDKJr(11, (positionDKJr * 2) + 7, 
						((positionDKJr - 1) % 4) + 1);
						}
					break;
					case SDLK_RIGHT:
					if (positionDKJr < 7){// empeche de sortir sur la droite
						setGrilleJeu(3, positionDKJr);
						effacerCarres(11, (positionDKJr * 2) + 7, 2, 2);
						positionDKJr++;
						setGrilleJeu(3, positionDKJr, DKJR);
						afficherDKJr(11, (positionDKJr * 2) + 7, ((positionDKJr - 1) % 4) + 1);
						}
					
					break;
					case SDLK_UP:
					if (positionDKJr== 2 ||positionDKJr== 3 ||positionDKJr== 4 ||positionDKJr== 6){//todo casser
						
						
						setGrilleJeu(3, positionDKJr);
						effacerCarres(11, (positionDKJr * 2) + 7, 2, 2);
						setGrilleJeu(2, positionDKJr, DKJR);
						afficherDKJr(10, (positionDKJr * 2) + 7, 8);
						pthread_mutex_unlock(&mutexGrilleJeu);
						nanosleep(&tempsJump , NULL);
						pthread_mutex_lock(&mutexGrilleJeu);
						setGrilleJeu(2, positionDKJr);
						effacerCarres(10, (positionDKJr * 2) + 7, 2, 2);
						setGrilleJeu(3, positionDKJr, DKJR);
						afficherDKJr(11, (positionDKJr * 2) + 7, ((positionDKJr - 1) % 4) + 1);
					}
					if (positionDKJr== 1 ||positionDKJr== 5 ){
						etatDKJr = LIANE_BAS ;
						setGrilleJeu(3, positionDKJr);
						effacerCarres(11, (positionDKJr * 2) + 7, 2, 2);
						setGrilleJeu(2, positionDKJr, DKJR);
						afficherDKJr(9, (positionDKJr * 2) + 7, 7);
					}
					if (positionDKJr== 7 ){
						etatDKJr = DOUBLE_LIANE_BAS ;
						setGrilleJeu(3, positionDKJr);
						effacerCarres(11, (positionDKJr * 2) + 7, 2, 2);
						setGrilleJeu(2, positionDKJr, DKJR);
						afficherDKJr(9, (positionDKJr * 2) + 7, 5);
					}



					break;
				}
			case LIANE_BAS:
				if(evenement == SDLK_DOWN){
					etatDKJr = LIBRE_BAS ;
						setGrilleJeu(2, positionDKJr);
						effacerCarres(9, (positionDKJr * 2) + 7, 2, 2);
						setGrilleJeu(3, positionDKJr, DKJR);
						afficherDKJr(11, (positionDKJr * 2) + 7, ((positionDKJr - 1) % 4) + 1);
				}
			
			break;
			case DOUBLE_LIANE_BAS:
					if(evenement == SDLK_DOWN){
						etatDKJr = LIBRE_BAS ;
						setGrilleJeu(2, positionDKJr);
						effacerCarres(10, (positionDKJr * 2) + 7, 2, 2);
						setGrilleJeu(3, positionDKJr, DKJR);
						afficherDKJr(11, (positionDKJr * 2) + 7, ((positionDKJr - 1) % 4) + 1);
					}
					if(evenement == SDLK_UP){
						etatDKJr = LIBRE_HAUT ;
						setGrilleJeu(2, positionDKJr);
						effacerCarres(10, (positionDKJr * 2) + 7, 2, 2);
						setGrilleJeu(1, positionDKJr, DKJR);
						afficherDKJr(8, (positionDKJr * 2) + 7, 6);
					}
			
			break;
			case LIBRE_HAUT:
				switch (evenement){
					case SDLK_LEFT: 
					if (positionDKJr > 3){
						setGrilleJeu(1, positionDKJr);
						effacerCarres(7, (positionDKJr * 2) + 7, 2, 2);
						positionDKJr--;
						setGrilleJeu(1, positionDKJr, DKJR);
						afficherDKJr(7, (positionDKJr * 2) + 7, ((positionDKJr - 1) % 4)+1 );
						}
					break;
					case SDLK_RIGHT:
					if(positionDKJr == 6){
						setGrilleJeu(3, positionDKJr);
						effacerCarres(7, (positionDKJr * 2) + 7, 2, 2);
						positionDKJr++;
						setGrilleJeu(1, positionDKJr, DKJR);
						afficherDKJr(7, (positionDKJr * 2) + 7, 6);
					}
					if (positionDKJr < 6){
						setGrilleJeu(1, positionDKJr);
						effacerCarres(7, (positionDKJr * 2) + 7, 2, 2);
						positionDKJr++;
						setGrilleJeu(1, positionDKJr, DKJR);
						afficherDKJr(7, (positionDKJr * 2) + 7, ((positionDKJr - 1) % 4)+1);
						}
					
					break;

					case SDLK_UP:
					if(positionDKJr== 6){
						etatDKJr = LIANE_HAUT ;
						setGrilleJeu(3, positionDKJr);
						effacerCarres(7, (positionDKJr * 2) + 7, 2, 2);
						setGrilleJeu(0, positionDKJr, DKJR);
						afficherDKJr(5, (positionDKJr * 2) + 7, 7);
					}
					if( positionDKJr != 6){
						setGrilleJeu(1, positionDKJr);
						effacerCarres(7, (positionDKJr * 2) + 7, 2, 2);
						setGrilleJeu(0, positionDKJr, DKJR);
						afficherDKJr(5, (positionDKJr * 2) + 7, 8);
						pthread_mutex_unlock(&mutexGrilleJeu);
						nanosleep(&tempsJump , NULL);
						pthread_mutex_lock(&mutexGrilleJeu);
						setGrilleJeu(0, positionDKJr);
						effacerCarres(5, (positionDKJr * 2) + 7, 2, 2);
						setGrilleJeu(1, positionDKJr, DKJR);
						afficherDKJr(7, (positionDKJr * 2) + 7, ((positionDKJr - 1) % 4) + 1);
					}


					break;
					case SDLK_DOWN:
						if(positionDKJr== 7){
							etatDKJr = DOUBLE_LIANE_BAS ;
							setGrilleJeu(1, positionDKJr);
							effacerCarres(7, (positionDKJr * 2) + 7, 2, 2);
							setGrilleJeu(2, positionDKJr, DKJR);
							afficherDKJr(9, (positionDKJr * 2) + 7, 5);
						}
					break;
				}
			
			break;
			case LIANE_HAUT:
				if(evenement == SDLK_DOWN){
						etatDKJr = LIBRE_HAUT ;
						setGrilleJeu(0, positionDKJr);
						effacerCarres(5, (positionDKJr * 2) + 7, 2, 2);
						setGrilleJeu(1, positionDKJr, DKJR);
						afficherDKJr(7, (positionDKJr * 2) + 7, ((positionDKJr - 1) % 4) + 1);
				}
			
			break;	
		}
		pthread_mutex_unlock(&mutexGrilleJeu);
		pthread_mutex_unlock(&mutexEvenement);
	}
	pthread_exit(0);	
			
}
//--------------------------------------------------