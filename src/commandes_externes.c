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
  //char arguments[CHAINE_MAX] = "";

  //Création d'un fork
  pid_t pid_fils = fork();

  strcpy(ligne, "");
  for(i=0; i<nbArg; i++) {

    if(strlen(ligne)!=0) {
      strcat(ligne," ");
    }
    strcat(ligne, info->ligne_cmd[debut+i]);
    /*if (i < 0 && i < nbArg-1)
    {
      strcat(arguments, info->ligne_cmd[debut+i]);
    }*/
  }
  premierPlan = (info->modificateur[debut]!=ARRIERE_PLAN);

  printf("execution d'une commande externe  (%s %d) a ecrire :\n%s\n", __FILE__, __LINE__, ligne);
  (void) premierPlan;
  strcat(chemin, info->ligne_cmd[debut]);
  
  if (premierPlan == vrai){
    //Pas de &, on exécute au premier plan
    if (pid_fils == -1)
    {
      printf("Erreur dans le fils\n");
      retour = faux;
    }
    if ( pid_fils == 0){ //Mon fils est créé
      //execv (chemin : forme : "/usr/bin/commande", commande + arguments fini par NULL)
      if (execl(chemin, ligne, NULL) == -1)
      {
        perror("execv");
        exit(EXIT_FAILURE);
      }

    }
    else {

     printf("Execution de la commande externe  (%s) situé %s \n", ligne, chemin);

      wait(&status); //j'attends la fin de mon fils
      retour = vrai;
    }
  }
  else {
    //On a un & donc on exécute en arrière plan
   if (pid_fils == -1)
   {
    printf("Erreur dans le fils\n");
    retour = faux;
  }
    if ( pid_fils == 0){ //Mon fils est créé
      if (execl(chemin, ligne, NULL))
      {
        perror("execv");
        exit(EXIT_FAILURE);
      }

    }
    else {

     printf("Execution de la commande externe  (%s) \n", ligne);

      //On n'attend pas la fin du fils??
     retour = vrai;
   }
  } 

return retour;
}
