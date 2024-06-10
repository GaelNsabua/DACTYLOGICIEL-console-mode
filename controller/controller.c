#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../view/view.h"
#include "../model/model.h"
#include "../setup/ansi_settings.h"
#include "../setup/global_variables.h"


//FONCTION QUI PERMET DE RECUPERER LES NOMS DES JOUEURS ET D'APPELER LE RESTE DES FONCTION
void ask_for_players_name(){

    center_height();

    center_text(CYAN "\t\tPRET A TESTER VOTRE RAPIDITE\n\n\n" RESET);
    center_text("Entrez le nom du premier joueur : ");
    scanf("%s", joueur_data[0].nom_joueur);
    joueur_data[0].temps_mis = 0;
    joueur_data[0].vitesse = 0;

    center_text("Entrez le nom du second joueur : ");
    scanf("%s", joueur_data[1].nom_joueur);
    joueur_data[1].temps_mis = 0;
    joueur_data[1].vitesse = 0;
    
    main_control();

}

//FONCTION DE CONTROL PRINCIPAL
void main_control(){

    int status = 0;
    int taille_tableau = nb_word_choice();

    for(status = 0; status < 2; status++){
        main_game(status, taille_tableau);
        sleep(5);
    }

}


void main_game(int status, int taille_tableau){

    int index_joueur = status;

    ask_ready_to_start(joueur_data[index_joueur]); //AVANT DE LANCER LE CHRONO, ON S'ASSURE QUE LE JOUEUR EST PRET

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

            show_player_name(joueur_data[index_joueur].nom_joueur);

            suggest_get_user_word(mots[index]);

            if (strcmp(mot_joueur,mots[index]) != 0){

                center_text("\n\n");
                center_text(RED "\tMot incorrect !\n"RESET);
                sleep(1);
            }

        } while (strcmp(mot_joueur,mots[index]) != 0);

            correct_message();
            continue;

    }

    fin = time(NULL); //FIN DU CHRONOMETRE

    int vitesse = speed_calculation(difftime(fin, debut), taille_tableau);

    //ON REMPLIT LE TABLEAU AVEC LES INFORMATIONS DU JOUEUR A L'INDICE INDIQUE PAR LE STATUT
    joueur_data[index_joueur].vitesse = vitesse;
    joueur_data[index_joueur].temps_mis = difftime(fin, debut);

    //LE STATUT NOUS PERMET D'EXECUTER LE CODE CI APRES UNIQUEMENT APRES LE DEUXIEME APPEL DE LA FONCTION MAIN_GAME
    if(status == 1){
        sleep(5);
        write_in_file(joueur_data); //ON SAUVEGARDE LES INFORMATIONS DU JOUEUR DANS UN FICHIER
        compare_joueur(joueur_data[0].vitesse, joueur_data[1].vitesse);
    }

}



int choose_word_aleatory(){

    int nb_max =  MAX_MOTS;
    int nb_min = 0;
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

    center_text(CYAN "Temps ecoule : " RESET);
    printf("%.0f min et %d sec\n", minutes, secondes);

    int vitesse = (nb_mot * 60.0) / tempsEcoule; //MOT PAR MINUTE

    center_text(CYAN "Vitesse de frappe : " RESET);
    printf(" %d MPM\n", vitesse);

    return vitesse;
}


//FONCTION QUI PERMET DE DETERMINER LEQUEL DES JOUEURS EST LE PLUS RAPIDE SUR BASE DE LA VITESSE
void compare_joueur(int vitesse1, int vitesse2){

    system("cls");
    center_height();
    center_text(UNDERLINE "\tRAPPORT FINAL\n\n" RESET);

    if(vitesse1 > vitesse2){
        center_text("le joueur ");
        printf("%s\n", joueur_data[0].nom_joueur);
        center_text("est plus rapide que le joueur ");
        printf("%s\n", joueur_data[1].nom_joueur);

    } else if (vitesse2 > vitesse1)
    {
        center_text("le joueur ");
        printf("%s\n", joueur_data[1].nom_joueur);
        center_text("est plus rapide que le joueur ");
        printf("%s\n", joueur_data[0].nom_joueur);

    } else {
        center_text("le joueur et");
        printf("%s\n", joueur_data[0].nom_joueur);
        center_text("le joueur ");
        printf("%s\n", joueur_data[1].nom_joueur);
        center_text("ecrivent a la meme vitesse\n");
    }

    sleep(5);
    restart_game();

}



