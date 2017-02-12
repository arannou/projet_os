/*
* Anais Pignet
* Alicia Rannou
* IMR1
* echo.c : Code de la fonction 'echo' du shell
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
