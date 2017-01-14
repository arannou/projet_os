#ifndef _DIVERS_H_
#define _DIVERS_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define COMMENCE_PAR(a,b)	(strncmp((a), (b), strlen((b)))==0)
#define EST_EGAL(a,b)    	(strlen((a))==strlen((b)) && COMMENCE_PAR((a),(b)))

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
	
#define ARG_MAX 128
#define CHAINE_MAX 512
#define MAX_PATH 512

typedef enum {faux=0, vrai} t_bool ; 

void AfficheInvite();
t_bool ecrire_variable (char* nomVar, char* valeur);
t_bool lire_variable (char* nomVar, char* valeur, int taille);

//MODIF ANAIS - 13/01/2017
int definir_variable(char * nomVarEnv, char * valeurVar);
int changer_variable (char * nomVarEnv, char * valeurVar);
//FIN

#endif
