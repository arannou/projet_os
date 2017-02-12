/*
* Anais Pignet
* Alicia Rannou
* IMR1
* echo.c : Code de la fonction 'echo' du shell
*/
#include "divers.h"
#include "commandes_internes.h"

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
