/*
* Anais Pignet
* Alicia Rannou
* IMR1
* commandes_internes.c : Code des fonctions appelées lors d'une appel à une fonction interne du shell
*/
#include "divers.h"
#include "commandes_internes.h"



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


/*t_bool ActionIMRSHELL (parse_info *info, int debut, int nbArg) {
    for(int i=1; i<nbArg; i++) {
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        parse_info *infoLigne;

        fp = fopen(info->ligne_cmd[debut+i], "r");
        if (fp == NULL)
            printf("ce fichier n'existe pas\n");
        while ((read = getline(&line, &len, fp)) != -1) {
            printf("Execution de : %s", line);
            infoLigne = parse(line);
            execution_ligne_cmd(infoLigne);
        }
        fclose(fp);
        if (line)
            free(line);
    }
    return vrai;
}
*/
