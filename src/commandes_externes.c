/*
* Anais Pignet
* Alicia Rannou
* IMR1
* commandes_externes.c : Codes des fonctions permettant d'exécuter une commande non reconnue comme une commande interne.
*/

#include "divers.h"
#include "commandes_externes.h"
/* Variables */
t_bool	ActionEXEC (parse_info *info, int debut, int nbArg) {
  char ligne[CHAINE_MAX];
  t_bool premierPlan = vrai;
  FILE *sortie; // Notre fichier de sortie
  int i, status;
  int taillechaine = sizeof(info->modificateur) / sizeof (info->modificateur[0]); //On récupère la taille de la chaine du modificateur
  char arguments[CHAINE_MAX];

  //Création d'un fork
  pid_t pid_fils = fork();

  strcpy(ligne, "");
  strcpy(arguments, "");
  //Pour i allant de 1 au nombre d'arguments, on construit notre ligne de commande
  for(i=1; i<nbArg; i++) {

    if(strlen(ligne)!=0) {
      strcat(ligne," ");
    }
    strcat(ligne, info->ligne_cmd[debut+i]);
  }
  //Pour i allant de 0 à la taille de la chaine du modificateur ..
  for (int i = 0; i < taillechaine; ++i)
  {
    //On regarde si on a un attribut "ARRIERE_PLAN". Si oui, on passe le booleen premierPlan à l'état faux.
    if (info->modificateur[i] == ARRIERE_PLAN)
    {
      premierPlan = faux;
    }
  }

  //On vérifie que notre fils a correctement été créé
  if (pid_fils == -1)  {
    printf("Erreur dans le fils\n");
  }
  //Notre fils est créé
  else if (pid_fils == 0) {
    //Si on cherche à lancer la commande
    if (!EST_EGAL(info->sortie, ""))
    {
      //On ouvre le fichier
      sortie = fopen(info->sortie, "w");
      if (sortie == NULL) { //S'il y a eu une erreur lors de la lecture
        printf("Erreur, le fichier demandé n'est pas accessible en écriture. Vous allez etre redirigé sur la sortie standard\n");
        sortie=stdout; //On redirige l'utilisateur sur la sortie standard
      }
      //S'il n'y a pas d'erreur, on cherche à modifier le flux standard avec dup2
      if(dup2(fileno(sortie), fileno(stdout)) == -1){
        fprintf(stderr, "Une erreur a été rencontrée : %d\n", errno);
        sortie=stdout; //Si on a un message d'erreur, on redirige l'utilisateur sur la sortie standard
      }
      else { //Sinon, on ferme le fichier
        fclose(sortie);
      }
    }
    //Si notre commande a eu une erreur lors du lancement, on affiche un message
    if (execlp(info->ligne_cmd[0], info->ligne_cmd[0], ligne, NULL) == -1)  {
      perror("execlp");
      exit(EXIT_FAILURE);
    }
  }

  //Si on choisi d'exécuter la commande au premier plan
  if (premierPlan == vrai)
  {
    //On attend que le fils se termine (il doit renvoyer le PID du fils terminé) - Ici, la commande est équivalante à wait(&status) vu en cours
    waitpid(pid_fils, &status, 0);
  }
  //Si on choisi d'exécuter la commande en arrière plan
  else {
    waitpid(pid_fils,&status, WNOHANG); //On n'attend pas que le fils se termine (attribut WNOHANG qui nous permet de revenir dans le shell, même si notre fils n'est pas mort.)
  }

  (void) premierPlan;
  return faux;
}
