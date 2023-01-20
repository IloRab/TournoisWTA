 /* main.c
  * Auteurs : Bryan Bohec, Ilo Rabiarivelo, Mathis Luce
  * Date de création : 05/11/2021
  * Projet IAP : Tournoi WTA
  */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable : 4996)


// CONSTANTES

#define maxTournois 10 //Nombre maximum de tournoi que l'ont peut enregistrer
#define nbMatchsTournoi 127 //Nombre de Matchs par Tournoi 
#define nbJoueusesTournois 128 //Nombre de Joueuse par Tournoi
#define lgMot 30 //Longueur des Mots

// FIN CONSTANTES


// CREATION DES STRUCTURES

typedef struct{ //Définition de la structure Joueuses
  char nom[lgMot+1]; //Nom de la Joueuse
  unsigned int points; //Nombre de points total
}Joueuse; //Les Joueuses possèdent un Nom et un Nombre de Point. 


typedef struct { //Définition de la structure Match 
unsigned int idxGagnante; //index de la gagnante
unsigned int idxPerdante; //index de la perdante
} Match; //Chaque match se lit sur une ligne avec 1 Gagnante et 1 Perdante

typedef struct { //Définition de la structure Tournoi
  char nom[lgMot+1]; //Nom du Tournoi
  int date; //Date du Tournoi
  Match dataMatch[nbMatchsTournoi]; //Les matchs qui ont été joué pendant le Tournoi
} Tournoi; //Chaque tournoi possède un nom, une date et un tableau de Matchs

typedef struct { //Définition de la structure TournoiWTA
  Tournoi dataTournois[maxTournois]; //Les Tournois qui sont stocké dans le logiciel
  Joueuse dataJoueuses[maxTournois*nbJoueusesTournois]; //Les Joueuses stocké dans le logiciel
  Match dataMatch[nbMatchsTournoi]; //Les Matchs qui sont stockés dans le logiciel
  int nbTournois; //Le nombre de Tournoi qui va être stocké au total
  int idxT; //Index Tournoi qui permettra la selection des Tournois enregistrés
  int idxJ; //Index Joueuse qui permettra la selection des Joueuses enregistrés
} TournoiWTA; //Cette structure va permettre le stockage de tout les Tournois, de toutes les joueuses et de tout les matchs qui ont été introduit dans le logiciel

// STRUCTURE(++)

typedef struct { //Définition de la structure Montableau
  Joueuse tabjoueuse [nbJoueusesTournois]; //Les Joueuses qui seront dans le tableau
} Montableau; //Cette structure sera utile pour classer les joueuses par ordre pour la commande 7

//FIN DE STRUCTURE CREATION


// DEFINITION DES FONCTIONS



//Sprint 1

/* Cette fonction va définir le nombre de tournoi que l'utilisateur va enregistrer.
 * tournoiwta[in-out] l'argument
 */

void definir_nb_tournoi(TournoiWTA *tournoiwta){
  char mot[lgMot+1];
  scanf("%s", mot);
  tournoiwta->nbTournois = atoi(mot);
}


/* Retourne l'index d'une joueuse dans tournoiwta, ou crée la joueuse et retourne son index
 * tournoiwta[in-out] Premier argument
 * nomjoueuse[in] deuxieme argument
 * [retour] l'index de la joueuse
 */
int rechercheindexjoueuse(TournoiWTA *tournoiwta, char* nomjoueuse) {
  for (int i = 0; i <= tournoiwta->idxJ ; i++) {
    if (strcmp (tournoiwta->dataJoueuses[i].nom, nomjoueuse) == 0) { //si on trouve la joueuse, on renvoit son index
      return i;
    }
  }
  strcpy(tournoiwta->dataJoueuses[tournoiwta->idxJ].nom, nomjoueuse); // sinon on l'ajoute et idxJ+1
  tournoiwta->dataJoueuses[tournoiwta->idxJ].points = 0;
  tournoiwta->idxJ++;
  return tournoiwta->idxJ-1;

}


/* Enregistre tous les matchs d'un tournoi dans tournoiwta
 * tournoiwta[in-out]
 */
void enregistrement_tournoi(TournoiWTA *tournoiwta){
  char nomdutournoi[lgMot+1];
  int datedutournoi;
  char nomdelajoueuse[lgMot+1]; //pour fonction creation joueuse
  scanf("%s", nomdutournoi);
  scanf("%d", &datedutournoi);
  strcpy(tournoiwta->dataTournois[tournoiwta->idxT].nom, nomdutournoi);//pour stocker le nom du tournoi 
  tournoiwta->dataTournois[tournoiwta->idxT].date = datedutournoi;


  for (int i = 0; i< nbMatchsTournoi; i++) {
    scanf("%s", nomdelajoueuse);
    tournoiwta->dataTournois[tournoiwta->idxT].dataMatch[i].idxGagnante = rechercheindexjoueuse(tournoiwta, nomdelajoueuse);

    scanf("%s", nomdelajoueuse);
    tournoiwta->dataTournois[tournoiwta->idxT].dataMatch[i].idxPerdante = rechercheindexjoueuse(tournoiwta, nomdelajoueuse);
  }

   for (int i = 0; i < nbMatchsTournoi; i++) {
  if (i < 64) {
     tournoiwta->dataJoueuses[tournoiwta->dataTournois[tournoiwta->idxT].dataMatch[i].idxPerdante].points += 10;
   }
  if (i >= 64 && i <96) {
     tournoiwta->dataJoueuses[tournoiwta->dataTournois[tournoiwta->idxT].dataMatch[i].idxPerdante].points += 45;
   }
  if (i >= 96 && i < 112) {
     tournoiwta->dataJoueuses[tournoiwta->dataTournois[tournoiwta->idxT].dataMatch[i].idxPerdante].points += 90;
   }
  if (i >= 112 && i < 120) {
     tournoiwta->dataJoueuses[tournoiwta->dataTournois[tournoiwta->idxT].dataMatch[i].idxPerdante].points += 180;
   }
  if (i >= 120 && i < 124) {
     tournoiwta->dataJoueuses[tournoiwta->dataTournois[tournoiwta->idxT].dataMatch[i].idxPerdante].points += 360;
   }
  if (i >= 124 && i < 126) {
    tournoiwta->dataJoueuses[tournoiwta->dataTournois[tournoiwta->idxT].dataMatch[i].idxPerdante].points += 720;
  }
  if (i == 126 ) {
    tournoiwta->dataJoueuses[tournoiwta->dataTournois[tournoiwta->idxT].dataMatch[i].idxPerdante].points += 1200;
    tournoiwta->dataJoueuses[tournoiwta->dataTournois[tournoiwta->idxT].dataMatch[i].idxGagnante].points += 2000;
  }
 }


  tournoiwta->idxT++;


}




/* Affiche tous les matchs d'un tournoi
 * tournoiwta[in] l'argument
 */
void affichage_matchs_tournoi(TournoiWTA* tournoiwta){
  char nom[lgMot+1];
  int date;
  scanf("%s", nom);
  scanf("%d", &date);

  int a = 0;
  while (a <= tournoiwta->idxT) {
    if ( (strcmp(tournoiwta->dataTournois[a].nom, nom) == 0) && tournoiwta->dataTournois[a].date == date ) {
      printf("%s ", tournoiwta->dataTournois[a].nom);
      printf("%d\n", tournoiwta->dataTournois[a].date);
          for (int i = 0; i < nbMatchsTournoi; i++) {
            if (i == 0) {
              printf("64emes de finale\n");
            }
            if (i == 64) {
              printf("32emes de finale\n");
            }
            if (i == 96) {
              printf("16emes de finale\n");
            }
            if (i == 112) {
              printf("8emes de finale\n");
            }
            if (i == 120) {
              printf("quarts de finale\n");
            }
            if (i == 124) {
              printf("demi-finales\n");
            }
            if (i == 126) {
              printf("finale\n");
            }                  
            printf("%s ", tournoiwta->dataJoueuses[tournoiwta->dataTournois[a].dataMatch[i].idxGagnante].nom);
            printf("%s\n", tournoiwta->dataJoueuses[tournoiwta->dataTournois[a].dataMatch[i].idxPerdante].nom);
          }
          printf("\n");
          return;
    }

    a++;
  }
  printf("tournoi inconnu");
}


//Sprint 2

/* Affiche tous les matchs d'une joueuse pour un tournoi
 * tournoiwta[in-out] l'argument
 */
void afficher_matchs_joueuse(TournoiWTA* tournoiwta) {
  char nom[lgMot+1];
  int date;
  char nomjoueuse[lgMot+1];
  scanf("%s", nom);
  scanf("%d", &date);
  scanf("%s", nomjoueuse);
  int a = 0, b = 0, c = 0, i = 0;
  

  while (a <= tournoiwta->idxT) {
    if ( (strcmp(tournoiwta->dataTournois[a].nom, nom) == 0) && tournoiwta->dataTournois[a].date == date ) { //Si le nom et la date correspond, on affiche les matchs
      for (; i < nbMatchsTournoi; i++) {
        if ( (strcmp(tournoiwta->dataJoueuses[tournoiwta->dataTournois[a].dataMatch[i].idxGagnante].nom, nomjoueuse) == 0 ) || (strcmp(tournoiwta->dataJoueuses[tournoiwta->dataTournois[a].dataMatch[i].idxPerdante].nom, nomjoueuse) == 0 ) ) {
          printf("%s ", tournoiwta->dataJoueuses[tournoiwta->dataTournois[a].dataMatch[i].idxGagnante].nom);
          printf("%s\n", tournoiwta->dataJoueuses[tournoiwta->dataTournois[a].dataMatch[i].idxPerdante].nom);
         }
         else{
           b++;
         }

       }
       if(b==i){
         printf("Joueuse Inconnu");
       }
   }
   else{
     c++;
   }
  a++;
  }
  if(c==a){
    printf("Tournoi Inconnu");
  }
}




//sprint 3



/* Affiche les joueuses d'un tournoi avec leurs points par ordre alphabétique
 * tournoiwta[in] premier arguement
 * montableau[in] deuxieme argument
 * Retourne un affichage de montableau
 */
void affichage_joueuses_tournoi (TournoiWTA* tournoiwta, Montableau montableau) {
  
  char nom[lgMot+1];
  int date;
  scanf("%s", nom);
  scanf("%d", &date);
  int indextournoi = 0;


  while (indextournoi <= tournoiwta->idxT) {
    if ( (strcmp(tournoiwta->dataTournois[indextournoi].nom, nom) == 0) && (tournoiwta->dataTournois[indextournoi].date == date) ) {
      printf("%s ", tournoiwta->dataTournois[indextournoi].nom);
      printf("%d\n", tournoiwta->dataTournois[indextournoi].date);

      for (int i = 0, j = 0; j < 64 ; i+=2, j++){
        strcpy (montableau.tabjoueuse[i].nom, tournoiwta->dataJoueuses[tournoiwta->dataTournois[indextournoi].dataMatch[j].idxGagnante].nom);
        strcpy (montableau.tabjoueuse[i+1].nom, tournoiwta->dataJoueuses[tournoiwta->dataTournois[indextournoi].dataMatch[j].idxPerdante].nom);
      }

//On donne a chaque joueuse un nombre de points en fonction d'où elle a perdu dans le tournoi
      for (int j = 0; j < 128; j++) {

          for (int i = 126; i >= 0; i--) {
            if ((strcmp(montableau.tabjoueuse[j].nom, tournoiwta->dataJoueuses[tournoiwta->dataTournois[indextournoi].dataMatch[i].idxGagnante].nom) == 0) && (i == 126)) {
              montableau.tabjoueuse[j].points = 2000;
            }
            if ((strcmp(montableau.tabjoueuse[j].nom, tournoiwta->dataJoueuses[tournoiwta->dataTournois[indextournoi].dataMatch[i].idxPerdante].nom) == 0) && (i == 126)) {
              montableau.tabjoueuse[j].points = 1200;
            }
            else if ((strcmp(montableau.tabjoueuse[j].nom, tournoiwta->dataJoueuses[tournoiwta->dataTournois[indextournoi].dataMatch[i].idxPerdante].nom) == 0) && ((i < 126) && (i >= 124))) {
              montableau.tabjoueuse[j].points = 720;
            }
            else if ((strcmp(montableau.tabjoueuse[j].nom, tournoiwta->dataJoueuses[tournoiwta->dataTournois[indextournoi].dataMatch[i].idxPerdante].nom) == 0) && ((i < 124) && (i >= 120))) {
              montableau.tabjoueuse[j].points = 360;
            }
            else if ((strcmp(montableau.tabjoueuse[j].nom, tournoiwta->dataJoueuses[tournoiwta->dataTournois[indextournoi].dataMatch[i].idxPerdante].nom) == 0) && ((i < 120) && (i >= 112))) {
              montableau.tabjoueuse[j].points = 180;
            }
            else if ((strcmp(montableau.tabjoueuse[j].nom, tournoiwta->dataJoueuses[tournoiwta->dataTournois[indextournoi].dataMatch[i].idxPerdante].nom) == 0) && ((i < 122) && (i >= 96))) {
              montableau.tabjoueuse[j].points = 90;
            }
            else if ((strcmp(montableau.tabjoueuse[j].nom, tournoiwta->dataJoueuses[tournoiwta->dataTournois[indextournoi].dataMatch[i].idxPerdante].nom) == 0) && ((i < 96) && (i >= 64))) {
              montableau.tabjoueuse[j].points = 45;
            }
            else if ((strcmp(montableau.tabjoueuse[j].nom, tournoiwta->dataJoueuses[tournoiwta->dataTournois[indextournoi].dataMatch[i].idxPerdante].nom) == 0) && ((i < 64) && (i >= 0))) {
              montableau.tabjoueuse[j].points = 10;
            }
            
          }
      }



      Joueuse temp;
// Tri des Joueuses par ordre alphabétique de leur nom
      for(int i=0; i<128; i++){
        for(int j=0; j<128-1-i; j++){
          if(strcmp(montableau.tabjoueuse[j].nom, montableau.tabjoueuse[j+1].nom) > 0){

            temp = montableau.tabjoueuse[j];
            montableau.tabjoueuse[j] = montableau.tabjoueuse[j+1];
            montableau.tabjoueuse[j+1] = temp;
          }
        }
      }
          

// Affichage du tableau
      for (int i = 0; i< nbJoueusesTournois; i++) {
        printf("%s ", montableau.tabjoueuse[i].nom);
        printf("%d\n", montableau.tabjoueuse[i].points);
      }

      return;

    }
    indextournoi++;
  }
  
  printf("tournoi inconnu");
}


//sprint 5



/* Envoie le nombre de points que gagne une joueuse en fonction de sa position dans le tournoi
 * joueuse[in] le premier argument
 * indextournoi[in] le deuxieme argument
 * tournoiwta[in] le troisième argument
 */
int points_joueuses_tournoi(Joueuse joueuse, int indextournoi, TournoiWTA tournoiwta) {
    if (indextournoi < 0) {
        return 0;
    }

    for (int i = 126; i >= 0; i--) {
        if ((strcmp(joueuse.nom, tournoiwta.dataJoueuses[tournoiwta.dataTournois[indextournoi].dataMatch[i].idxGagnante].nom) == 0) && (i == 126)) {
            return 2000;
        }
        else if ((strcmp(joueuse.nom, tournoiwta.dataJoueuses[tournoiwta.dataTournois[indextournoi].dataMatch[i].idxPerdante].nom) == 0) && (i == 126)) {
            return 1200;
        }
        else if ((strcmp(joueuse.nom, tournoiwta.dataJoueuses[tournoiwta.dataTournois[indextournoi].dataMatch[i].idxPerdante].nom) == 0) && ((i < 126) && (i >= 124))) {
            return 720;
        }
        else if ((strcmp(joueuse.nom, tournoiwta.dataJoueuses[tournoiwta.dataTournois[indextournoi].dataMatch[i].idxPerdante].nom) == 0) && ((i < 124) && (i >= 120))) {
            return 360;
        }
        else if ((strcmp(joueuse.nom, tournoiwta.dataJoueuses[tournoiwta.dataTournois[indextournoi].dataMatch[i].idxPerdante].nom) == 0) && ((i < 120) && (i >= 112))) {
            return 180;
        }
        else if ((strcmp(joueuse.nom, tournoiwta.dataJoueuses[tournoiwta.dataTournois[indextournoi].dataMatch[i].idxPerdante].nom) == 0) && ((i < 122) && (i >= 96))) {
            return 90;
        }
        else if ((strcmp(joueuse.nom, tournoiwta.dataJoueuses[tournoiwta.dataTournois[indextournoi].dataMatch[i].idxPerdante].nom) == 0) && ((i < 96) && (i >= 64))) {
            return 45;
        }
        else if ((strcmp(joueuse.nom, tournoiwta.dataJoueuses[tournoiwta.dataTournois[indextournoi].dataMatch[i].idxPerdante].nom) == 0) && ((i < 64) && (i >= 0))) {
            return 10;
        }

    }
    return 0;

}

/* Affiche le classement de toutes les joueuses sur les 4 derniers tournois
 * tournoiwta[in] premier arguement
 */
void afficher_classement(TournoiWTA tournoiwta) {

    if (tournoiwta.idxJ == 0) {
        printf("pas de classement\n");
        return;
    }

    // Reinitialise les points de toutes les joueuses à 0
    for (int i = 0; i < tournoiwta.idxJ; i++) {
        tournoiwta.dataJoueuses[i].points = 0;
    }

    //On leur ajoute les points des 4 derniers tournois
    for (int i = 0; i < tournoiwta.idxJ; i++) {
        tournoiwta.dataJoueuses[i].points += points_joueuses_tournoi(tournoiwta.dataJoueuses[i], tournoiwta.idxT-1, tournoiwta);
        tournoiwta.dataJoueuses[i].points += points_joueuses_tournoi(tournoiwta.dataJoueuses[i], tournoiwta.idxT-2, tournoiwta);
         tournoiwta.dataJoueuses[i].points += points_joueuses_tournoi(tournoiwta.dataJoueuses[i], tournoiwta.idxT-3, tournoiwta);
        tournoiwta.dataJoueuses[i].points += points_joueuses_tournoi(tournoiwta.dataJoueuses[i], tournoiwta.idxT-4, tournoiwta);
    }



    Joueuse temp;
    // Tri par nombre de points
    for (int i = 0; i < tournoiwta.idxJ; i++) {
        for (int j = 0; j < tournoiwta.idxJ - 1 - i; j++) {
            if (tournoiwta.dataJoueuses[j].points < tournoiwta.dataJoueuses[j + 1].points) {
                temp = tournoiwta.dataJoueuses[j];
                tournoiwta.dataJoueuses[j] = tournoiwta.dataJoueuses[j + 1];
                tournoiwta.dataJoueuses[j + 1] = temp;
            }
        }
    }


    // Tri par ordre alphabetique si ils ont le meme nombre de points
    for (int i = 0; i < tournoiwta.idxJ; i++) {
        for (int j = 0; j < tournoiwta.idxJ - 1 - i; j++) {
            if ((tournoiwta.dataJoueuses[j].points == tournoiwta.dataJoueuses[j + 1].points) && (strcmp(tournoiwta.dataJoueuses[j].nom, tournoiwta.dataJoueuses[j + 1].nom) > 0)) {
                temp = tournoiwta.dataJoueuses[j];
                tournoiwta.dataJoueuses[j] = tournoiwta.dataJoueuses[j + 1];
                tournoiwta.dataJoueuses[j + 1] = temp;
            }
        }
    }


    // Affichage du tableau trié
    for (int i = 0; i < tournoiwta.idxJ; i++) {
        if (tournoiwta.dataJoueuses[i].points > 0) {
            printf("%s ", tournoiwta.dataJoueuses[i].nom);
            printf("%d\n", tournoiwta.dataJoueuses[i].points);
        }
    }
}



// FIN PROTOTYPES DES FONCTIONS


//PROGRAMME MAIN 

int main() {

    char mot[lgMot+1]; //Chaine de caractère qui va servir à l'utilisateur pour taper les commandes

    TournoiWTA tournoiwta; //Création du Tournoi WTA

    tournoiwta.idxJ = 0; //Création de l'Index Joueuse

    tournoiwta.idxT = 0; //Création de l'Index Tournoi

    Montableau montableau; //Création du tableau


    while (1) { 
    
    scanf("%s", mot);         

    //C1 exit
      if (strcmp(mot, "exit")==0) {
        exit(0);
      }

    //C2 definir_nombre_tournoi
      if (strcmp(mot,"definir_nombre_tournoi")==0) {
        definir_nb_tournoi(&tournoiwta);
      }
      
    //C3 enregistrement_tournoi
      if (strcmp(mot,"enregistrement_tournoi")==0) {
        enregistrement_tournoi(&tournoiwta);
      }

    //C4 affichage_matchs_tournois
      if(strcmp(mot,"affichage_matchs_tournoi")==0) {
        affichage_matchs_tournoi(&tournoiwta);
      }

    //C6 afficher_matchs_joueuse Paris 2021 Badosa
      if(strcmp(mot,"afficher_matchs_joueuse")==0) {
        afficher_matchs_joueuse(&tournoiwta);
      }

    //C5 affichage_joueuses_tournoi
      if(strcmp(mot,"affichage_joueuses_tournoi")==0) {
        affichage_joueuses_tournoi(&tournoiwta, montableau);
      }

    //C7 afficher_classement
      if(strcmp(mot,"afficher_classement")==0) {
        afficher_classement(tournoiwta);
      }
  }
  return 0;

}



