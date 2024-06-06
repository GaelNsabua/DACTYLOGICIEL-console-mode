#include "ansi_settings.h"
#include "controller.h"

//FONCTION QUI AFFICHE DES ELEMENTS A L'ECRAN AU LANCEMENT
void lancement(){
    center_height();
    center_text(BOLD BLUE CLIGNOTANT"\t\tUDBL-"RED"DACTYLOGICIEL"RESET"\n\n\n");
    sleep(3); //LE PROGRAMME ATTENT 3 SECONDES AVANT D'EXECUTER LE RESTE D'INSTRUCTONs
    center_text(CYAN UNDERLINE"\tMEMBRES DE L'EQUIPE\n\n"RESET);
    //center_text("==================");
    center_text("1. MUKALA NSABUA GAEL\t3. MUJINGA NDAYA MIRADIE\n");
    center_text("2. MUKAS KASONG CHRISTELLA\t4. MUJINGA WA NGOIE ANITA\n");
    sleep(5);
    system("cls");
    menu();
}

//FONCTION QUI PERMET DE CENTRER LE TEXTE EN HAUTEUR
void center_height(){
    for (int i = 0; i < 10; i++) {
        printf("\n");
      }
}

//FONCTION QUI PERMET DE CENTRER LE TEXTE EN LARGEUR
void center_text(const char* text) {
  int text_length = strlen(text);
  int console_width = 120; // Largeur de la console
  int spaces_before = (console_width - text_length) / 2;
  //Centrage par rapport à la largeur
  for (int i = 0; i < spaces_before; i++) {
    printf(" ");
  }
  printf("%s", text);
}

//FONCTION QUI PERMET DE DEMANDER A L'UTILISATEUR DE CONFIRMER SON CHOIX AVANT DE QUITTER LE JEU
void exit_confirm(){
    center_height();
    center_text(BOLD BLUE CLIGNOTANT"\t\tUDBL-"RED"DACTYLOGICIEL"RESET"\n\n");
    center_text("Etes vous sur de vouloir quitter\n\n");
    center_text("1. OUI    2. NON\n\n");
    center_text("Choisissez une option :: ");

    int choix;
    scanf("%d", &choix);

    if (choix == 1)
    {
        return;
    } else{
        system("cls");
        menu();
    }

}

void menu(){

    int option;

    do{
        system("cls");
        center_height();
        center_text(CYAN BOLD"\t\t\tTESTER " GRAY BOLD " VOTRE RAPIDITE A TAPER AU " RED BOLD " CLAVIER\n\n\n"RESET);
        center_text("MENU\n\n");
        center_text("=====\n");
        center_text("1. DEMARRER\n\n");
        center_text("2. CONFIGURER\n\n");
        center_text("3. AIDE\t\n\n");
        center_text("0. QUITTER\n\n");

        center_text("Choisissez une option :: ");
        scanf("%d", &option);

    } while (option > 3 || option < 0);

    switch (option)
    {
    case 0 :
        system("cls");
        exit_confirm();
        break;
    case 1 :
        system("cls");
        ask_for_players_name();
    break;
    case 2 :
        system("cls");
        add_word_in_file();
    break;

    default:
        center_height();
        center_text(RED "ERREUR !!!!" RESET);
        break;
    }

}


void show_player_name(char nom_joueur[]){

    center_height();
    center_text(GREEN "JOUEUR ::: " RESET);
    printf("%s\n\n\n\n", nom_joueur);
}


void correct_message(){

    center_text("\n\n");
    center_text(GREEN"\tCorrect !\n"RESET);
    sleep(1);
}


int nb_word_choice(){

    int nb_mot;

    do
    {
        system("cls");
        center_height();
        center_text(GREEN "\tEVALUER VOTRE RAPIDITE" CYAN " SELON VOS CHOIX\n\n"RESET);
        center_text("Avec combien de mot voulez-vous jouer :: ");
        scanf("%d", &nb_mot);

    } while (nb_mot < 0 || nb_mot > 40);

    return nb_mot;

}

void aide(){

    center_height();
    center_text(UNDERLINE "\tA PROPOS\n\n" RESET);
    center_text(CYAN "\tUDBL-DACTYLOGICIEL " RESET "est un jeu concu pour aider les utilisateur a ameliorer\n");
    center_text("leur vitesse de frappe au clavier.\n\n");
    center_text("Le jeu consiste en fait a evaluer la vitesse de frappe de deux joueurs\n");
    center_text("et determiner lequel des deux est le plus rapide.\n\n");
    
    center_text(UNDERLINE "\tVERSION\n\n" RESET);
    center_text("Ceci est la version 1.0.1 de UDBL-DACTYLOGICIEL.\n\n");
    center_text("Concu le 06.06.2024\n\n");

    center_text(UNDERLINE "\tCONCEPTEURS\n\n" RESET);
    center_text("MUKALA NSABUA GAEL\n");
    center_text("MUJINGA NDAYA MIRADIE \n");
    center_text("MUKAS KASONG CHRISTELLA\n");
    center_text("MIJINGA WA NGOIE ANITA\n");

    scroll_animation(3);

}

void scroll_animation(int n){

    int i = 0;
    while (i != n)
    {
        sleep(1);
        printf("\n");
        i++;
    }

}


