/*
* Anais Pignet
* Alicia Rannou
* IMR1
* commandes_internes.c : Code des fonctions appelées lors d'une appel à une fonction interne du shell
*/
#include "divers.h"
#include "commandes_internes.h"
#include "execution.h"

t_bool	ActionECHO (parse_info *info, int debut, int nbArg) {

  int i;
  FILE *sortie;
  /* si l'appel est correctement ecrit, on a :
   * arguments[0] == "echo"
   * arguments[1..nbArg-1] = "..."
   *
   * Par de lecture, mais une ecriture redirigee possible
   */
  if (!EST_EGAL(info->sortie, ""))
  {
    sortie = fopen(info->sortie, "w");
    if (sortie == NULL)
    {
      /* Traitement du cas où le fichier n'est pas accessible en écriture */
      printf("Erreur, le fichier demandé n'est pas accessible en écriture. Vous allez etre redirigé sur la sortie standard\n");
     sortie=stdout;
    }
  }
  else {
    sortie=stdout;
  }

  i = 1;
  while(i<nbArg)  {
    fprintf(sortie, "%s ", info->ligne_cmd[debut+i]);
    i++;
  }
  printf("\n");

  if (!EST_EGAL(info->sortie, ""))
  {
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

t_bool ActionIMRSHELL (parse_info *info, int debut, int nbArg) {

    (void) info;
    (void) debut;

    for(int i=1; i<nbArg; i++) {

        // read lines
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;

        parse_info *infoLigne;

        fp = fopen(info->ligne_cmd[debut+i], "r");

        // fp = fopen("/home/alicia/Documents/Cours/test/projet_os/script1.imr", "r");
        if (fp == NULL)
            printf("ce fichier n'existe pas\n");
            // exit(EXIT_FAILURE);

        while ((read = getline(&line, &len, fp)) != -1) {

            printf("Execution de : %s", line);
            infoLigne = parse(line);
            execution_ligne_cmd(infoLigne);
        }

        fclose(fp);
        if (line)
            free(line);
        // exit(EXIT_SUCCESS);

    }
    return vrai;
}
