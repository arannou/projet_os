/*
* Anais Pignet
* Alicia Rannou
* IMR1
* ls.c : Code de la fonction 'ls' du shell
*/
#include "divers.h"
#include "commandes_internes.h"

t_bool	ActionLS (parse_info *info, int debut, int nbArg) {

  /* Utilisation des parametres */
  (void) info;
  (void) debut;
  (void) nbArg;


    char var[CHAINE_MAX];
    char * dwRet = getcwd (var, sizeof (var)); // récupere le repertoire courant
    struct dirent* fichier = NULL; /* Déclaration d'un pointeur vers la structure dirent. */
    DIR* rep = NULL;
    rep = opendir(dwRet); // ouvre le répertoire courant
    if (rep == NULL) { // en cas d'erreur
        printf("Erreur, impossible d'ouvrir le répertoire courant\n");
        return faux;
    } else {
        // ca serait bien de mettre des couleurs
        // et de placer '.' et '..' au début
        fichier = readdir(rep); /* On lit le premier répertoire du répertoire. */
        while ((fichier = readdir(rep)) != NULL) // boucle sur chaque fichier
            printf("%s\n", fichier->d_name); // on l'affiche
        return vrai;
    }
}
