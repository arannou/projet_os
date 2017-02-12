/*
* Anais Pignet
* Alicia Rannou
* IMR1
* commandes_internes.c : Code des fonctions appelées lors d'une appel à une fonction interne du shell
*/
#include "divers.h"
#include "commandes_internes.h"

t_bool	ActionECHO (parse_info *info, int debut, int nbArg) {
  /*Variables */
  int i;
  FILE *sortie;
  /* si l'appel est correctement ecrit, on a :
   * arguments[0] == "echo"
   * arguments[1..nbArg-1] = "..."
   *
   * Par de lecture, mais une ecriture redirigee possible
   */
   // Si la redirection est demandée
  if (!EST_EGAL(info->sortie, ""))
  {
    //On ouvre le fichier
    sortie = fopen(info->sortie, "w");
    if (sortie == NULL) //S'il y a eu une erreur lors de la lecture
    {
      /* Traitement du cas où le fichier n'est pas accessible en écriture */
      printf("Erreur, le fichier demandé n'est pas accessible en écriture. Vous allez etre redirigé sur la sortie standard\n");
     sortie=stdout; //On redirige l'utilisateur sur la sortie standard
    }
  }
  //Si la redirection n'est pas demandée
  else {
    sortie=stdout; //On dirige l'utilisateur sur la sortie standard
  }

  i = 1;
  while(i<nbArg)  {
    fprintf(sortie, "%s ", info->ligne_cmd[debut+i]);
    i++;
  }
  printf("\n");
  // Si la redirection est demandée
  if (!EST_EGAL(info->sortie, ""))
  {
    //On peut fermer notre fichier de sortie
    fclose(sortie);
  }

  return vrai;
}

t_bool	ActionSET (parse_info *info, int debut, int nbArg) {

  /* si l'appel est correctement ecrit, on a :
   * arguments[0] == "set"
   * arguments[1] == "nom_variable"
   * arguments[2] == "="
   * arguments[3] == "valeur"
   * nbArg == 4
   *
   * ou
   * arguments[0] == "set"
   * arguments[1] == "nom_variable"
   * arguments[2] == "="
   * nbArg == 3
   *
   */

  if (!EST_EGAL(info->ligne_cmd[debut], "set") && !EST_EGAL(info->ligne_cmd[debut+2], "=")) {
    printf("Impossible de mettre a jour la variable, appel incorrect\n");
    return faux;
  }

  if (nbArg == 4)	{
    return ecrire_variable (info->ligne_cmd[debut+1], info->ligne_cmd[debut+3]);
  } else if (nbArg == 3) {
    return ecrire_variable (info->ligne_cmd[debut+1], NULL);
  } else {
    return faux;
  }
}

t_bool ActionCD (parse_info *info, int debut, int nbArg) {

  char def[MAX_PATH];
  char dirName[MAX_PATH];
  int i;

  /* le cas nbArg==1 a un comportement par defaut qui mene au
   * repertoire HOME utilisateur
   *
   * Si nbArg>=1 il faut aggreger tous les arguments en un seul chemin
   * (le repertoire de destination contient des espaces)
   */
  if (nbArg == 1) {

    lire_variable ("USERPROFILE", def, sizeof (def));
    if (chdir (def) == -1) {
      printf ("Impossible de changer vers le repertoire '%s' \n", def );
      return faux;
    }
  } else {

    strcpy(dirName,"");
    for(i=1; i<nbArg; i++) {
      if(strlen(dirName)!=0) strcat(dirName," ");
      strcat(dirName, info->ligne_cmd[debut+i]);
    }

    if (chdir (dirName) == -1) {
      printf ("Impossible de changer vers le repertoire '%s'\n", dirName);
      return faux;
    }
  }
  return vrai;

}


t_bool	ActionLS (parse_info *info, int debut, int nbArg) {

  /* Utilisation des parametres */
  (void) info;
  (void) debut;
  (void) nbArg;


    char var[CHAINE_MAX];
    char * dwRet = getcwd (var, sizeof (var));
    struct dirent* fichier = NULL; /* Déclaration d'un pointeur vers la structure dirent. */
    DIR* rep = NULL;
    rep = opendir(dwRet);
    if (rep == NULL) {
        printf("Erreur, impossible d'ouvrir le répertoire courant\n");
        return faux;
    } else {
        // ca serait bien de mettre des couleurs
        // et de placer '.' et '..' au début
        fichier = readdir(rep); /* On lit le premier répertoire du dossier. */
        while ((fichier = readdir(rep)) != NULL)
            printf("%s\n", fichier->d_name);
        return vrai;
    }
}
