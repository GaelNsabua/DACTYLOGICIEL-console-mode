#include <stdio.h>
#include <stdlib.h>
#include "global_variables.h"
#include "ansi_settings.h"

//FONCTION QUI PERMET DE RECUPERER LES MOT A PARTIR D'UN FICHIER ET DE LES REMPLIR DE LE TABLEAU PREVU A CETTE EFFET
void get_mots_from_file(){

    FILE* fichier = fopen("mots.txt", "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    int nombreDeMots = 0;

    // Lire les mots depuis le fichier
    while (nombreDeMots < MAX_MOTS && fgets(mots[nombreDeMots], sizeof(mots[nombreDeMots]), fichier) != NULL) {
        // Supprimer le saut de ligne à la fin du mot (si présent)
        mots[nombreDeMots][strcspn(mots[nombreDeMots], "\n")] = '\0';
        nombreDeMots++;
    }

    fclose(fichier);
}


void write_in_file(JOUEUR joueur_data[]){

    FILE* fichier = fopen("joueurs.csv", "a+");

        if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    int i;

    for (size_t i = 0; i < 2; i++)
    {
        fprintf(fichier, "%s,%.0f,%d\n", joueur_data[i].nom_joueur, joueur_data[i].temps_mis , joueur_data[i].vitesse);
    }

    fclose(fichier);
}


void add_word_in_file(){

    char new_word[100];
    int nb_new_word;

    FILE* fichier = fopen("mots.txt", "a+");

        if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    center_height();
    center_text(CYAN "\t\tAJOUT DE NOUVEAUX" GREEN " MOTS\n\n\n" RESET);
    center_text("Combien de mots voulez-vous ajouter :: ");
    scanf("%d", &nb_new_word);

    int i = 1;

    while (i <= nb_new_word )
    {
        system("cls");
        center_height();
        center_text(CYAN "\t\tAJOUT DE NOUVEAUX" GREEN " MOTS\n\n\n" RESET);
        center_text("SAISISSEZ LE NOUVEAU MOT :: ");
        scanf("%s", new_word);

        fprintf(fichier, "%s\n", new_word);

        center_text("\n\n");
        center_text(GREEN "\tMot ajoute avec succes" RESET);
        sleep(2);
        i++;

    }

    fclose(fichier);
    menu();

}


