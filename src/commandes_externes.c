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
  t_bool premierPlan, retour;
  int i, status;
  char chemin[CHAINE_MAX] = "/bin/";
  
  //char commande[CHAINE_MAX];

  //Création d'un fork
  pid_t pid_fils = fork();

  strcpy(ligne, "");
  for(i=0; i<nbArg; i++) {

    if(strlen(ligne)!=0) {
      strcat(ligne," ");
    }
    strcat(ligne, info->ligne_cmd[debut+i]);
  }
  premierPlan = (info->modificateur[debut]!=ARRIERE_PLAN);

  printf("execution d'une commande externe  (%s %d) a ecrire :\n%s\n", __FILE__, __LINE__, ligne);
  (void) premierPlan;
  strcat(chemin, info->ligne_cmd[debut]);
  
  if (pid_fils == -1)
  {
   printf("Erreur dans le fils\n");
   retour = faux;
 }
  //Mon fils est créé
 else if (pid_fils == 0) 
 {
   printf("Execution de la commande, params : %s", info->ligne_cmd[1]);

   if (execl(chemin, ligne, NULL) == -1)
   {
    perror("execl");
    exit(EXIT_FAILURE);
  }

}
else {
  printf("Execution de la commande externe  (%s) situé %s \n", ligne, chemin);

  if (premierPlan == vrai)
  {
    //j'attends la fin de mon fils
    wait(&status); 
  }
  retour = vrai;
}

return retour;
}
