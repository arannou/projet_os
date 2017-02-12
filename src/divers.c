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

	// on défini des variables d'environnement initiales
	setenv("INV","Bonjour$", 0);
	setenv("USERNAME","user", 0);
	if (lire_variable ("INV", invite, sizeof (invite))) {

	    /* Format reconnu :
	     * \u : remplace par l'utilisateur
	     * \h : remplace par le nom de machine
		 * \p : remplace par le chemin courant
	     * \s : ajoute un espace
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
	else {
		strcpy(chaine, "$ ");
	}
	// affichage de l'invite en couleur
	printf ("%s%s%s", VERT, chaine, RESET);

	fflush (stdout);
}
/* permet d'ecrire une valeur pour une variable d'environnement
 @param nomChar : le nom de la variable
 @param valeur : la valeur à lui attribuer
 @return : succes ou échec de l'opération
 */
t_bool ecrire_variable (char* nomVar, char* valeur) {
	setenv(nomVar, valeur,1);
	// le 1 écrase la valeur précedente
	t_bool result = setenv(nomVar, valeur,1);
	return result;
}

/* permet de lire la valeur d'une variable d'environnement
 @param nomChar : le nom de la variable
 @param valeur : la valeur qui lui correspond
 @param taille : taille de la valeur
 @return : succes ou échec de l'opération
 */
t_bool lire_variable (char* nomVar, char* valeur, int taille) {
	strcpy(valeur, getenv(nomVar));
	(void) taille;
	if (valeur!= NULL) return vrai;
	else return faux;
}
