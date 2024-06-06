#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "view.h"
#include "ansi_settings.h"
#define MAX_MOTS 40


typedef struct {
    char *nom_joueur[24];
    double temps_mis;
    int vitesse;  //WORD PER MINUTE
} JOUEUR; //LA STRUCTURE QUI REPRESENTE UN JOUEUR

JOUEUR joueur1;
JOUEUR joueur2;

char mots[MAX_MOTS][50]; // TABLEAU QUI VA STOCKER LES MOTS A SAISIR. CHAQUE PEUT AVOIR AU MAXIMUM 50 CARACTERES
char mot_joueur[100]; //VARIABLE QUI VA CONTENIR LE MOT SAISI PAR L'UTILISATEUR

//FONCTION QUI PERMET DE RECUPERER LES NOMS DES JOUEURS ET D'APPELER LE RESTE DES FONCTION
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
    int taille_tableau = nb_word_choice();
    main_game(joueur1, status, taille_tableau);
    sleep(3);
    status = 1;
    main_game(joueur2, status, taille_tableau);
}

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


void main_game(JOUEUR* joueur, int status, int taille_tableau){

    srand(time(NULL)); //INITIALISATION DE LA FONCTION QUI NOUS PERMET DE GENERER DES MOTS ALEATOIREMENT

    get_mots_from_file();

    sleep(1);

    int index;

    // INITIALISATION DU CHRONOMETRE
    time_t debut = time(NULL);
    time_t fin;

    for (size_t i = 0; i < taille_tableau; i++)
    {
         index = choose_word_aleatory();
         
        do
        {
            system("cls");

            show_player_name(joueur->nom_joueur);

            suggest_get_user_word(mots[index]);

        } while (strcmp(mot_joueur,mots[index]) != 0);

            correct_message();
            continue;

    }

    fin = time(NULL); //FIN DU CHRONOMETRE

    int vitesse = speed_calculation(difftime(fin, debut), taille_tableau);

    JOUEUR joueur_data[2]; //TABLEAU CONTENANT LES JOUEURS

    strcpy(joueur_data[status].nom_joueur, joueur->nom_joueur);
    joueur_data[status].vitesse = vitesse;
    joueur_data[status].temps_mis = difftime(fin, debut);
    //LE STATUT NOUS PERMET D'EXECUTER LE CODE CI APRES UNIQUEMENT APRES LE DEUXIEME APPEL DE LA FONCTION MAIN_GAME
    if(status == 1){
        sleep(3);
        compare_joueur(joueur_data[0].vitesse, joueur_data[1].vitesse);
        write_in_file(joueur_data);
    }

}



int choose_word_aleatory(){

    int nb_max =  MAX_MOTS;
    int nb_min = 1;
    int nb_aleatoire;
    static int last_nb; //VARIABLE QUI NOUS PERMET DE NE PAS REPETER LE MEME MOT SUCCESSIVEMENT

    do
    {
        nb_aleatoire = rand() % (nb_max-1) + nb_min;

    } while (nb_aleatoire == last_nb); //CONDITION QUI NOUS PERMET DE VERIFIER QUE LE MOT ACTUEL N'EST PAS LE MEME QUE LE PRECEDENT

    last_nb =  nb_aleatoire;
    
    return nb_aleatoire;

}


//FONCTION QUI PERMET D'AFFICHER LE MOT A SAISIR ET QUI RECUPERE LA SAISIE DE L'UTILISATEUR
void suggest_get_user_word(char mot[]){

    center_text(CYAN "Taper le mot :: " RESET);
    printf(GREEN BOLD "%s\n\n" RESET, mot);
    center_text(RED">>> "RESET);

    scanf("%s", mot_joueur);
}

//FONCTION QUI NOUS PERMET DE CALCULER LA VITESSE (EN MOT PAR MINUTE) DE SAISIE DES JOUEURS ET LE TEMPS MIS (EN MINUTES ET SECONDES)
int speed_calculation(double tempsEcoule, int nb_mot){

    double minutes = tempsEcoule / 60; // Conversion en minutes
    int secondes = (int)tempsEcoule % 60; // Récupération des secondes

    center_text(BLUE "Temps ecoule : " RESET);
    printf("%.0f minutes et %d secondes\n", minutes, secondes);

    int vitesse = (nb_mot * 60.0) / tempsEcoule;

    center_text("Vitesse de frappe : ");
    printf(" %d MPM\n", vitesse);

    return vitesse;
}



void write_in_file(JOUEUR joueur_data[]){

    FILE* fichier = fopen("joueurs.csv", "a+");

        if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

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

}


//FONCTION QUI PERMET DE DETERMINER LEQUEL DES JOUEURS EST LE PLUS RAPIDE SUR BASE DE LA VITESSE
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



