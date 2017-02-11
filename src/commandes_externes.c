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
 FILE *sortie;
 int i, status;
 int taillechaine = sizeof(info->modificateur) / sizeof (info->modificateur[0]);
 char arguments[CHAINE_MAX];

  //Création d'un fork
 pid_t pid_fils = fork();

 strcpy(ligne, "");
 strcpy(arguments, "");
 for(i=1; i<nbArg; i++) {

  if(strlen(ligne)!=0) {
   strcat(ligne," ");
}
strcat(ligne, info->ligne_cmd[debut+i]);
} 
for (int i = 0; i < taillechaine; ++i)
{
   if (info->modificateur[i] == ARRIERE_PLAN)
   {
      premierPlan = faux;
   }
}


  //printf("execution d'une commande externe  (%s %d) a ecrire :\n%s\n", __FILE__, __LINE__, ligne);


if (pid_fils == -1)  {
  printf("Erreur dans le fils\n");
}
  //Mon fils est créé
else if (pid_fils == 0) {
   if (!EST_EGAL(info->sortie, ""))
   {
      sortie = fopen(info->sortie, "w");
      if (sortie == NULL) {
       printf("Erreur, le fichier demandé n'est pas accessible en écriture. Vous allez etre redirigé sur la sortie standard\n");
       sortie=stdout;
    }
    
    if(dup2(fileno(sortie), fileno(stdout)) == -1){
      fprintf(stderr, "Une erreur a été rencontrée : %d\n", errno);
      sortie=stdout;
   } 
   else {
      fclose(sortie);
   } 
}
if (execlp(info->ligne_cmd[0], info->ligne_cmd[0], ligne, NULL) == -1)  {
 perror("execlp");
 exit(EXIT_FAILURE);
}
}



if (premierPlan == vrai)
{
       //j'attends la fin de mon fils
   waitpid(pid_fils, &status, 0);
}
else {
  waitpid(pid_fils,&status, WNOHANG);
}

(void) premierPlan;
return faux;
}
