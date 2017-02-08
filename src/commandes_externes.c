/*
* Anais Pignet
* Alicia Rannou
* IMR1
* commandes_externes.c : Codes des fonctions permettant d'exécuter une commande non reconnue comme une commande interne.
*/

#include "divers.h"
#include "commandes_externes.h"

t_bool	ActionEXEC (parse_info *info, int debut, int nbArg) {
  char ligne[CHAINE_MAX];
  t_bool premierPlan = vrai;
  t_bool retour;
  int i, status;
  char arguments[CHAINE_MAX];

  //Création d'un fork
  pid_t pid_fils = fork();

  strcpy(ligne, "");
  strcpy(arguments, "");
  for(i=0; i<nbArg; i++) {

    if(strlen(ligne)!=0) {
      strcat(ligne," ");
    }
    strcat(ligne, info->ligne_cmd[debut+i]);
    if (i > 0)
    {
      strcat(arguments, info->ligne_cmd[debut+i]);
    }
    if (info->modificateur[i]!=ARRIERE_PLAN)
    {
      premierPlan = faux;
    }
  }
  //premierPlan = (info->modificateur[debut]!=ARRIERE_PLAN);
  

  printf("execution d'une commande externe  (%s %d) a ecrire :\n%s\n", __FILE__, __LINE__, ligne);
  

  if (pid_fils == -1)
  {
   printf("Erreur dans le fils\n");
   retour = faux;
 }
  //Mon fils est créé
 else if (pid_fils == 0) 
 {
   printf("Execution de la commande %s, params : %s", info->ligne_cmd[0], arguments);
   if (nbArg > 1)
   {
    if (execlp(info->ligne_cmd[0], info->ligne_cmd[0], arguments, NULL) == -1)
    {
      perror("execlp");
      exit(EXIT_FAILURE);
    }
  }
  else {
   if (execlp(info->ligne_cmd[0], info->ligne_cmd[0], NULL) == -1)
   {
    perror("execlp");
    exit(EXIT_FAILURE);
  }
}


}
else {
  if (premierPlan == vrai)
  {
    //j'attends la fin de mon fils
    wait(&status); 
  }
  retour = vrai;
}

(void) premierPlan;
return retour;
}
