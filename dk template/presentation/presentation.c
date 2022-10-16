#include "presentation.h"

SDL_Surface *chargerImage(const char *nomImage);
void afficherImage(int ligne, int colonne, SDL_Surface *image);

SDL_Surface	*ecran,
		*imgFondEcran,
		*imgCle1,
		*imgCle2,
		*imgCle3,
		*imgCle4,
		*imgCorbeau1,
		*imgCorbeau2,
		*imgCroco1,
		*imgCroco2,
		*imgCroco3,
		*imgCroco4,
		*imgCroco5,
		*imgDKJr1,
		*imgDKJr2,
		*imgDKJr3,
		*imgDKJr4,
		*imgDKJr5,
		*imgDKJr6,
		*imgDKJr7,
		*imgDKJr8,
		*imgDKJr9,
		*imgDKJr10,
		*imgDKJr11,
		*imgDKJr12,
		*imgDKJr13,
		*imgDKJrEchec,
		*imgCage1,
		*imgCage2,
		*imgCage3,
		*imgCage4,
		*imgRireDK,
		*imgChiffre0,
		*imgChiffre1,
		*imgChiffre2,
		*imgChiffre3,
		*imgChiffre4,
		*imgChiffre5,
		*imgChiffre6,
		*imgChiffre7,
		*imgChiffre8,
		*imgChiffre9;
pthread_mutex_t mutexSDL;

// ------------------------------------------------------------------------
// charger les images et ouvrir la fenêtre graphique

void ouvrirFenetreGraphique()
{
	SDL_Rect rect;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	ecran = SDL_SetVideoMode(1240, 640, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	imgFondEcran = SDL_DisplayFormat(SDL_LoadBMP("./images/autres/fondEcran.bmp"));
	
	imgCle1 = chargerImage("./images/autres/cle1.bmp");
	imgCle2 = chargerImage("./images/autres/cle2.bmp");
	imgCle3 = chargerImage("./images/autres/cle3.bmp");
	imgCle4 = chargerImage("./images/autres/cle4.bmp");
	imgCorbeau1 = chargerImage("./images/autres/corbeau1.bmp");
	imgCorbeau2 = chargerImage("./images/autres/corbeau2.bmp");
	imgCroco1 = chargerImage("./images/autres/croco1.bmp");
	imgCroco2 = chargerImage("./images/autres/croco2.bmp");
	imgCroco3 = chargerImage("./images/autres/croco3.bmp");
	imgCroco4 = chargerImage("./images/autres/croco4.bmp");
	imgCroco5 = chargerImage("./images/autres/croco5.bmp");
	imgDKJr1 = chargerImage("./images/dkjr/dkjr1.bmp");
	imgDKJr2 = chargerImage("./images/dkjr/dkjr2.bmp");
	imgDKJr3 = chargerImage("./images/dkjr/dkjr3.bmp");
	imgDKJr4 = chargerImage("./images/dkjr/dkjr4.bmp");
	imgDKJr5 = chargerImage("./images/dkjr/dkjr5.bmp");
	imgDKJr6 = chargerImage("./images/dkjr/dkjr6.bmp");
	imgDKJr7 = chargerImage("./images/dkjr/dkjr7.bmp");
	imgDKJr8 = chargerImage("./images/dkjr/dkjr8.bmp");
	imgDKJr9 = chargerImage("./images/dkjr/dkjr9.bmp");
	imgDKJr10 = chargerImage("./images/dkjr/dkjr10.bmp");
	imgDKJr11 = chargerImage("./images/dkjr/dkjr11.bmp");
	imgDKJr12 = chargerImage("./images/dkjr/dkjr12.bmp");
	imgDKJr13 = chargerImage("./images/dkjr/dkjr13.bmp");
	imgDKJrEchec = chargerImage("./images/dkjr/dkjrechec.bmp");
	imgCage1 = chargerImage("./images/autres/cage1.bmp");
	imgCage2 = chargerImage("./images/autres/cage2.bmp");
	imgCage3 = chargerImage("./images/autres/cage3.bmp");
	imgCage4 = chargerImage("./images/autres/cage4.bmp");
	imgRireDK = chargerImage("./images/autres/rireDK.bmp");
	imgChiffre0 = chargerImage("./images/chiffres/Zero.bmp");
	imgChiffre1 = chargerImage("./images/chiffres/Un.bmp");
	imgChiffre2 = chargerImage("./images/chiffres/Deux.bmp");
	imgChiffre3 = chargerImage("./images/chiffres/Trois.bmp");
	imgChiffre4 = chargerImage("./images/chiffres/Quatre.bmp");
	imgChiffre5 = chargerImage("./images/chiffres/Cinq.bmp");
	imgChiffre6 = chargerImage("./images/chiffres/Six.bmp");
	imgChiffre7 = chargerImage("./images/chiffres/Sept.bmp");
	imgChiffre8 = chargerImage("./images/chiffres/Huit.bmp");
	imgChiffre9 = chargerImage("./images/chiffres/Neuf.bmp"); 
        
	SDL_WM_SetCaption("Donkey Kong JR", NULL);
	rect.x = 0;
	rect.y = 0;
	SDL_BlitSurface(imgFondEcran, NULL, ecran, &rect);
	SDL_Flip(ecran);
	
	pthread_mutex_init(&mutexSDL, NULL);
}

// ------------------------------------------------------------------------
// afficher les différentes images de la clé (num est le numéro de l'image)

void afficherCle(int num)
{
	switch(num)
	{
            case 1:
                afficherImage(3, 12, imgCle1); break;
            case 2:
                afficherImage(3, 13, imgCle2); break;
            case 3:
                afficherImage(3, 13, imgCle3); break;
            case 4:
                afficherImage(3, 13, imgCle4); 
	}
}

// ------------------------------------------------------------------------
// afficher les différentes images d'un corbeau

void afficherCorbeau(int colonne, int num)
{
	switch(num)
	{
            case 1:
                afficherImage(10, colonne, imgCorbeau1); break;
            case 2:
                afficherImage(9, colonne, imgCorbeau2);
	}
}

// ------------------------------------------------------------------------
// afficher les différentes images d'un croco

void afficherCroco(int colonne, int num)
{
	switch(num)
	{
            case 1:
                afficherImage(8, colonne, imgCroco1); break;
            case 2:
                afficherImage(8, colonne, imgCroco2); break;
            case 3:
                afficherImage(9, 23, imgCroco3); break;
            case 4:
                afficherImage(12, colonne, imgCroco4); break;
            case 5:
                afficherImage(12, colonne, imgCroco5);
	}
}

// ------------------------------------------------------------------------
// afficher les différentes images de Donkey Kong Jr

void afficherDKJr(int ligne, int colonne, int num)
{
	switch(num)
	{
            case 1:
                afficherImage(ligne, colonne, imgDKJr1); break;
            case 2:
                afficherImage(ligne, colonne, imgDKJr2); break;
            case 3:
                afficherImage(ligne, colonne, imgDKJr3); break;
            case 4:
                afficherImage(ligne, colonne, imgDKJr4); break;
            case 5:
                afficherImage(10, 21, imgDKJr5); break;
            case 6:
                afficherImage(7, 21, imgDKJr6); break;
            case 7:
                afficherImage(ligne, colonne, imgDKJr7); break;
            case 8:
                afficherImage(ligne, colonne, imgDKJr8); break;
            case 9:
                afficherImage(5, 12, imgDKJr9); break;
            case 10:
                afficherImage(3, 11, imgDKJr10); break;
            case 11:
                afficherImage(6, 10, imgDKJr11); break;
            case 12:
                afficherImage(6, 11, imgDKJr12); break;
            case 13:
                afficherImage(11, 7, imgDKJr13);
	}
}

// ------------------------------------------------------------------------
// afficher les différentes parties de la cage

void afficherCage(int num)
{
	switch(num)
	{
            case 1:
                afficherImage(2, 7, imgCage1); break;
            case 2:
                afficherImage(2, 9, imgCage2); break;
            case 3:
                afficherImage(4, 7, imgCage3); break;
            case 4:
                afficherImage(4, 9, imgCage4);
	}
}

// ------------------------------------------------------------------------
// afficher le rire de Donkey Kong

void afficherRireDK()
{
	afficherImage(3, 8, imgRireDK);
}

// ------------------------------------------------------------------------
// afficher la tête de Donkey Kong Jr en cas d'échec 

void afficherEchec(int nbEchecs)
{
	afficherImage(7, 26 + nbEchecs, imgDKJrEchec);
}

// ------------------------------------------------------------------------
// afficher le score

void afficherScore(int score)
{
	afficherChiffre(3, 26, score / 1000);
	afficherChiffre(3, 27, (score /100) % 10);
	afficherChiffre(3, 28, (score / 10) % 10);
	afficherChiffre(3, 29, score % 10);
}

// ------------------------------------------------------------------------
// afficher les différents chiffres

void afficherChiffre(int ligne, int colonne, int chiffre)
{
	switch(chiffre)
	{
            case 0:
                afficherImage(ligne, colonne, imgChiffre0); break;
            case 1:
                afficherImage(ligne, colonne, imgChiffre1); break;
            case 2:
                afficherImage(ligne, colonne, imgChiffre2); break;
            case 3:
                afficherImage(ligne, colonne, imgChiffre3); break;
            case 4:
                afficherImage(ligne, colonne, imgChiffre4); break;
            case 5:
                afficherImage(ligne, colonne, imgChiffre5); break;
            case 6:
                afficherImage(ligne, colonne, imgChiffre6); break;
            case 7:
                afficherImage(ligne, colonne, imgChiffre7); break;
            case 8:
                afficherImage(ligne, colonne, imgChiffre8); break;
            case 9:
                afficherImage(ligne, colonne, imgChiffre9);
	}
}

// ------------------------------------------------------------------------
// charger une image avec fond transparent

SDL_Surface *chargerImage(const char *nomImage)
{
	SDL_Surface *image;
	
	image = SDL_DisplayFormat(SDL_LoadBMP(nomImage));
	SDL_SetColorKey(image, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 255, 255));
	
	return image;
}

// ------------------------------------------------------------------------
// afficher une image sur l'image de fond d'écran initiale

void afficherImage(int ligne, int colonne, SDL_Surface *image)
{
	SDL_Rect rect;
	
	pthread_mutex_lock(&mutexSDL);  
	      
	rect.x = colonne * 40;
	rect.y = ligne * 40;
	SDL_BlitSurface(image, NULL, ecran, &rect);
	SDL_Flip(ecran);
	
	pthread_mutex_unlock(&mutexSDL);  
}

// ------------------------------------------------------------------------
// restaurer l'image de fond d'écran initiale pour 1 ou plusieurs carrés

void effacerCarres(int ligne, int colonne, int nbLignes, int nbColonnes)
{
	SDL_Rect rect, rectCible;	
	
	pthread_mutex_lock(&mutexSDL); 
	
	rect.x = colonne * 40;
	rect.y = ligne * 40;
	rect.w = nbColonnes * 40;
	rect.h = nbLignes * 40;
	rectCible.x = colonne * 40;
	rectCible.y = ligne * 40;
	SDL_BlitSurface(imgFondEcran, &rect, ecran, &rectCible);
	SDL_Flip(ecran);
        
	pthread_mutex_unlock(&mutexSDL);  
}

// ------------------------------------------------------------------------
// restaurer l'image de fond d'écran initiale pour 1 ou plusieurs points

void effacerPoints(int x, int y, int nbX, int nbY)
{
	SDL_Rect rect, rectCible;	
	
	pthread_mutex_lock(&mutexSDL); 
	
	rect.x = x;
	rect.y = y;
	rect.w = nbX;
	rect.h = nbY;
	rectCible.x = x;
	rectCible.y = y;
	SDL_BlitSurface(imgFondEcran, &rect, ecran, &rectCible);
	SDL_Flip(ecran);
        
	pthread_mutex_unlock(&mutexSDL);  
}

// ------------------------------------------------------------------------
// retourner la touche sur laquelle a appuyé le joueur ou SDL_QUIT
// si clic sur la croix

int lireEvenement()
{
	SDL_Event event;
	int evt = 0;
	struct timespec temps = { 0, 20000000 };

        while(evt == 0)
        {
            pthread_mutex_lock(&mutexSDL); 
    
            while(SDL_PollEvent(&event))
            {   
                if(event.type == SDL_QUIT)  
                    evt = SDL_QUIT;
                else if(event.type == SDL_KEYDOWN)
                    evt = event.key.keysym.sym;
            }

            pthread_mutex_unlock(&mutexSDL);  

            nanosleep(&temps, NULL);  
        } 
  
        return evt;
}


