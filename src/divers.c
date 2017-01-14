/*
* Anais Pignet
* Alicia Rannou
* IMR1
* divers.c : code des fonctions utilitaires
*/
#include "divers.h"

void AfficheInvite() {

	char invite[CHAINE_MAX];
	char chaine[CHAINE_MAX];
	char var[CHAINE_MAX];
	size_t i;
	char * dwRet;

	if (lire_variable ("INV", invite, sizeof (invite))) {

    /* Format reconnu :
     * \u : remplace par l'utilisateur
     * \h : remplace par le nom de machine
     * \p : remplace par le chemin courant
     */

		strcpy(chaine, "");
		for(i=0; i<strlen(invite); i++) {
			if (invite[i]=='\\' && i<strlen(invite)-1) {
				i = i+1;
				switch(invite[i]) {
					case 'u' :
					lire_variable ("USERNAME", var, sizeof (var));
					break;
					case 'h' :
					lire_variable ("COMPUTERNAME", var, sizeof (var));
					break;
					case 's' :
					strcpy(var," ");
					break;
					case 'p' :
					dwRet = getcwd (var, sizeof (var));

					if (dwRet == NULL) {
						fprintf (stderr, "Echec lors de l'appel a getcwd !\n");
						fflush (stderr);
					}
					break;
					default :
	  /* cas impossible a priori */
					break;
				}
			}
			else {
				sprintf(var, "%c", invite[i]);
			}
			strncat(chaine, var, CHAINE_MAX - strlen(chaine));
		}

	}
	//ANAIS - 13/01/2017
	else if (lire_variable("set VAR", invite, sizeof (invite)))
	{
		/* code */
		definir_variable("set VAR", invite);

	}
	//FIN ANAIS
	else {
		strcpy(chaine, "$ ");
	}

	printf ("%s", chaine);
	fflush (stdout);
}

t_bool ecrire_variable (char* nomVar, char* valeur) {

	printf("Appel a ecrire_variable (%s %d) a ecrire avec \"%s\" et \"%s\". \n",
		__FILE__,
		__LINE__,
		nomVar,
		valeur);
	return faux;
}

t_bool lire_variable (char* nomVar, char* valeur, int taille) {
	strcpy(valeur, "");

	printf("Appel a lire_variable (%s %d) a ecrire avec \"%s\", \"%s\" et %d. \n",
		__FILE__,
		__LINE__,
		nomVar,
		valeur,
		taille);
	return faux;
}

//MODIF ANAIS - 13/01/2017

void definir_variable (char * nomVarEnv, char * valeurVar){
	int result = setenv(nomVarEnv, valeurVar, 1);
	if (result == 0){
		printf("Succès");
	}
	else {
		printf("Echec");
	}
}

void changer_variable (char * nomVarEnv, char * valeurVar){
	int result = 0;
	char * lieuVar = getenv(nomVarEnv);
	if(lieuVar != NULL){
		result = setenv(nomVarEnv, valeurVar, 1);
		if (result == 0){
			printf("Succès");
		}
		else {
			printf("Echec");
		}
	}
}
