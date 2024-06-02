#include "view.h"
#include "ansi_settings.h"
#include <time.h>

typedef struct {
    char *nom_joueur[24];
    int vitesse;  //WORD PER MINUTE
    int temps_mis;
} JOUEUR;


void ask_for_players_name(){
    JOUEUR joueur1;
    JOUEUR joueur2;

    center_height();

    center_text(CYAN "PRET A TESTER VOTRE RAPIDITE\n\n\n" RESET);
    center_text("Entrez le nom du premier joueur : ");
    scanf("%s", joueur1.nom_joueur);
    joueur1.temps_mis = 0;
    joueur1.vitesse = 0;

    center_text("Entrez le nom du second joueur : ");
    scanf("%s", joueur2.nom_joueur);
    joueur2.temps_mis = 0;
    joueur2.vitesse = 0;

}

void game(){

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

    for (size_t i = 0; i < taille_tableau; i++)
    {
        nb_aleatoire = rand() % (nb_max-1) + nb_min;

        do
        {
            system("cls");
            center_height();
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

      double vitesse = (taille_tableau * 60.0) / tempsEcoule;

    center_text("Vitesse de frappe : ");
    printf(" %.2f MPM\n", vitesse);


}



