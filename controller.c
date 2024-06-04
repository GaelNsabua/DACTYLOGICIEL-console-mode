#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "view.h"
#include "ansi_settings.h"


typedef struct {
    char *nom_joueur[24];
    double temps_mis;
    int vitesse;  //WORD PER MINUTE
} JOUEUR;

JOUEUR joueur1;
JOUEUR joueur2;


void ask_for_players_name(){

    center_height();

    center_text(CYAN "\t\tPRET A TESTER VOTRE RAPIDITE\n\n\n" RESET);
    center_text("Entrez le nom du premier joueur : ");
    scanf("%s", joueur1.nom_joueur);
    joueur1.temps_mis = 0;
    joueur1.vitesse = 0;

    center_text("Entrez le nom du second joueur : ");
    scanf("%s", joueur2.nom_joueur);
    joueur2.temps_mis = 0;
    joueur2.vitesse = 0;

    int status = 0;
    game(joueur1, status);
    sleep(3);
    status = 1;
    game(joueur2, status);
}

void game(JOUEUR* joueur, int status){

    srand(time(NULL)); //INITIALISATION DE LA FONCTION QUI NOUS PERMET DE GENERER DES MOTS ALEATOIREMENT

    char* words[] = {"Bonjour", "Gratuit", "courant", "joueur", "MONSIEUR", "UDBL", "Finale", "seulement", "Sciences", "Whatsapp", "trouver", "ciel", "powershell", "chat",};

    int nb_max =  sizeof(words)/sizeof(words[0]);
    int nb_min = 1;
    int nb_aleatoire;
    int taille_tableau = nb_max;
    char mot_joueur[100];

    // Chronomètre
    time_t debut = time(NULL);
    time_t fin;

    for (size_t i = 0; i < taille_tableau-12; i++)
    {
        nb_aleatoire = rand() % (nb_max-1) + nb_min;

        do
        {
            system("cls");

            center_height();
            center_text(GREEN "JOUEUR ::: " RESET);
            printf("%s\n\n\n", joueur->nom_joueur);

            //center_height();
            center_text(CYAN "Taper le mot :: " RESET);
            printf(GREEN BOLD "%s\n\n" RESET, words[nb_aleatoire]);
            center_text(RED">>> "RESET);

            scanf("%s", mot_joueur);

        } while (strcmp(mot_joueur,words[nb_aleatoire]) != 0);

            center_text("\n\n");
            center_text(GREEN"\tCorrect !\n"RESET);
            sleep(1);
            continue;

    }

    fin = time(NULL);
    double tempsEcoule = difftime(fin, debut);
    double minutes = tempsEcoule / 60; // Conversion en minutes
    int secondes = (int)tempsEcoule % 60; // Récupération des secondes

    center_text(BLUE "Temps ecoule : " RESET);
    printf("%.0f minutes et %d secondes\n", minutes, secondes);

      int vitesse = ((taille_tableau-12) * 60.0) / tempsEcoule;

    center_text("Vitesse de frappe : ");
    printf(" %d MPM\n", vitesse);

    JOUEUR joueur_data[2];

    strcpy(joueur_data[status].nom_joueur, joueur->nom_joueur);
    joueur_data[status].vitesse = vitesse;
    joueur_data[status].temps_mis = tempsEcoule;

    if(status == 1){
        sleep(3);
        compare_joueur(joueur_data[0].vitesse, joueur_data[1].vitesse);
    }


    FILE* fichier = fopen("joueurs.csv", "a+");

        if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    fprintf(fichier, "%s,%.0f,%d\n", joueur_data[status].nom_joueur, joueur_data[status].temps_mis , joueur_data[status].vitesse = vitesse);

    fclose(fichier);


}


void compare_joueur(int vitesse1, int vitesse2){

    system("cls");
    center_height();
    center_text(UNDERLINE "\tRAPPORT FINAL\n\n" RESET);

    if(vitesse1 > vitesse2){
        center_text("le joueur ");
        printf("%s\n", joueur1.nom_joueur);
        center_text("est plus rapide que le joueur ");
        printf("%s\n", joueur2.nom_joueur);
    } else if (vitesse2 > vitesse1)
    {
        center_text("le joueur ");
        printf("%s\n", joueur2.nom_joueur);
        center_text("est plus rapide que le joueur ");
        printf("%s\n", joueur1.nom_joueur);
    } else {
        center_text("le joueur ");
        printf("%s\n", joueur1.nom_joueur);
        center_text("et le joueur ");
        printf("%s\n", joueur2.nom_joueur);
        center_text("ecrivent a la meme vitesse\n");
    }

}



