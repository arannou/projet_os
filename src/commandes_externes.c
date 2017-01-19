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
  t_bool premierPlan;
  int i;
  //On initialise ligne
  strcpy(ligne, "");
  //Tant que i < nbArg, on incrémente i
  for(i=0; i<nbArg; i++) {
    //
    if(strlen(ligne)!=0) {
      strcat(ligne," ");
    }
    strcat(ligne, info->ligne_cmd[debut+i]);

    //Debug - faire un exec avec nos params pour la commande
    printf("Ligne = %s\n", ligne);

  }

  premierPlan = (info->modificateur[debut]!=ARRIERE_PLAN);

  

  printf("execution d'une commande externe  (%s %d) a ecrire :\n%s\n", __FILE__, __LINE__, ligne);
  (void) premierPlan;

  return faux;
}
