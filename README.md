# INTRODUCTION
Dans le cadre de notre cours de langage C il nous a été demandé de réaliser des projets réunissant toutes les connaissances acquises au cours de l’apprentissage de ce langage. Alors pour ce faire plusieurs projets nous ont été proposés par nos encadreurs et pour notre part nous avons eu à en choisir un qui est le suivant : « UDBL-DACTYLOGICIEL » que nous allons présenter dans les lignes qui suivent.

# DÉVELOPPEMENT 
## Présentation
Le projet UDBL-DACTYLOGICIEL consiste en la réalisation d’un jeu qui peut être soit en console ou en interface graphique. 

Le jeu se joue à deux pour tester lequel des joueurs écrit vite au clavier.

### Déroulement du jeu 
- L’ordinateur demande à l’utilisateur de saisir les noms des deux joueurs qui vont s’affronter 
- L’ordinateur demande à l’utilisateur le nombre de mots à saisir
- L’ordinateur pique des mots aléatoirement et les propose aux joueurs
- Le premier joueur saisit les mots proposés et valide l’un après l’autre selon l’ordre d’affichage 
- Le deuxième joueur saisit les mots proposés et valide l’un après l’autre selon l’ordre d’affichage 
- L’ordinateur demande au joueur de saisir le même mot autant de fois s’il n’est de correct
- À la fin du jeu l’ordinateur affiche le temps de saisie des deux joueurs et indique lequel des joueurs et plus rapide au clavier.

## Implémentation
Nous avons choisi d’implémenter notre jeu en mode console pour une meilleure efficacité. Et pour ce faire nous avons procédé de la manière suivante :

### Structure du projet
- **View** : Dans le fichier view nous retrouvons toutes les fonctions qui gère l’affichage
- **Controller** : Dans le fichier controller nous retrouvons toutes les fonctions qui gère la logique du jeu
- **Model** : Dans le fichier model nous retrouvons toutes les fonctions qui nous permettent de gérer les fichiers où nous stockons nos données.
- **Setup** : Dans le dossier setup nous retrouvons toutes les variables globales et les constantes prédéfinis.

Nous devons aussi un fichier `joueurs.csv` pour stocker les informations concernant les joueurs et un fichier `mots.txt` qui nous sert de base de données de mots à proposer aux joueurs.
```csv
nom   ,temps ,vitesse
PAUL  ,    0 ,     11
ANDRE ,    0 ,     12
```

### Variables globales
Dans le fichier `global_variable.h` nous avons déclaré :
- `MAX_MOTS` : une variable qui nous permet de déterminer le nombre maximal de mot que nous pouvons récupérer dans notre fichier `mots.txt`
- Un type de variable nommé `JOUEUR`. Ce type est une structure qui représente un joueur avec les informations dont nous avons besoin notamment le nom du joueur, le temps mis pour saisir les mots et la vitesse de frappe qui s’exprime en mot par minute.
- Un tableau de type `JOUEUR` nommé `joueur_data` de taille 2. Ce tableau va contenir les informations concernant les deux joueurs pendant une partie de jeu.
- Un tableau nommé `mots` de taille `MAX_MOTS` qui va contenir les mots à proposer aux joueurs et nous avons défini la taille maximale d’un mot à 50 caractères
- Une variable `mot_joueur` qui va contenir le mot saisi par l’utilisateur au cours du jeu.
 ```c
  #define MAX_MOTS 30

typedef struct {
    char* nom_joueur[24];
    int temps_mis;
    int vitesse;  //WORD PER MINUTE
} JOUEUR; //LA STRUCTURE QUI REPRESENTE UN JOUEUR

JOUEUR joueur_data[2]; //TABLEAU CONTENANT LES JOUEURS

char mots[MAX_MOTS][50]; // TABLEAU QUI VA STOCKER LES MOTS A SAISIR. CHAQUE PEUT AVOIR AU MAXIMUM 50 CARACTERES
char mot_joueur[100]; //VARIABLE QUI VA CONTENIR LE MOT SAISI PAR L'UTILISATEUR
```

Nous avons eu à définir dans le fichier `ansi_settings.h` des constantes correspondant à des caractères d’échappement ANSI afin de styliser le texte dans la console.
```c
//CARACTERE D'ECHAPPEMENT ANSI
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define GRAY "\033[37m"
#define CLIGNOTANT "\033[5m"
```

Nous avons eu aussi à utiliser des bibliothèques telles que `unistd.h` pour gérer le temps et `time.h` pour générer des nombres aléatoires.

### Fonctions
- `center_height()` : Cette fonction nous permet de centrer le texte sur l’axe vertical dans la console
```c
  //FONCTION QUI PERMET DE CENTRER LE TEXTE EN HAUTEUR
void center_height(){
    for (int i = 0; i < 10; i++) {
        printf("\n");
      }
}
```
- `center_text()` : Cette fonction permet de centrer le texte sur l’axe horizontal dans la console
 ```c
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
```
- `main()` : La fonction `main()` constitue le point d’entrée de notre programme et nous permet de lancer notre jeu en appelant la fonction `lancement()`.
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //BIBLIOTHEQUE QUI PERMET DE GERER LE TEMPS
#include "view.h"
#include "model.h"
#include "controller.h"
#include "global_variables.h"

int main()
{
    lancement();
    return 0;
}
```
- `lancement()` : Cette fonction nous permet d’afficher le texte d’accueil de notre jeu notamment le nom du jeu suivi des noms des membres du groupe. Cette fonction appelle une autre fonction qui est `menu()`.
```c
#include "ansi_settings.h"
#include "controller.h"

//FONCTION QUI AFFICHE DES ELEMENTS A L'ECRAN AU LANCEMENT
void lancement(){
    center_height();
    center_text(BOLD BLUE"\t\tUDBL-"RED"DACTYLOGICIEL"RESET"\n\n\n");
    sleep(3); //LE PROGRAMME ATTENT 3 SECONDES AVANT D'EXECUTER LE RESTE D'INSTRUCTONs
    center_text(CYAN UNDERLINE"\tMEMBRES DE L'EQUIPE\n\n"RESET);
    center_text("1. MUKALA NSABUA GAEL\t3. MUJINGA NDAYA MIRADIE\n");
    center_text("2. MUKAS KASONG CHRISTELLA\t4. MUJINGA WA NGOIE ANITA\n");
    sleep(5);
    system("cls");
    menu();
}
```
- `menu()` : La fonction `menu()` permet d’afficher le menu du jeu et d’appeler certaines autres fonctions en suivant le choix de l’utilisateur. Les différentes options que nous avons dans le menu sont :
  - Démarrer : Cette option permet de lancer le jeu
  - Configurer : Cette option permet aux joueurs de personnaliser le jeu en ajoutant des mots dans la base de données 
  - Aide : Cette option permet d’afficher les informations relatives au jeu.
  - Quitter : Cette option permet de quitter le jeu.

  Nous avons utilisé une variable nommée `choix` qui va contenir le nombre correspondant à l’option choisie par l’utilisateur et nous avons implémenté un contrôle de saisie pour plus d’efficacité.
```c
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
    case 0 : //QUITTER LE JEU
        sleep(1);
        system("cls");
        exit_confirm();
        break;
    case 1 : //DEMARER LE JEU
        sleep(1);
        system("cls");
        ask_for_players_name();
    break;
    case 2 : //CONFIGURATION ON PERMET AUX UTILISATEURS D'AJOUTER DES MOTS POUR PERSONNALISER LE JEU
        sleep(1);
        system("cls");
        add_word_in_file();
    break;
    case 3 : //AFFICHER LES INFORMATIONS RELATIVES AU JEU
        sleep(1);
        system("cls");
        aide();
    break;

    default:
        center_height();
        center_text(RED "ERREUR !!!!" RESET);
        break;
    }

}
```

- `exit_confirm()` : C’est la fonction appelée lorsque l’utilisateur choisit de quitter le jeu. Elle permet de demander à l’utilisateur de confirmer son choix avant de quitter le jeu.
```c
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
```
- `ask_for_players_name()` : C’est la fonction appelée lorsque l’utilisateur choisit l’option démarrer dans le menu. Cette fonction permet en fait de demander aux joueurs de saisir leur nom et de les stocker dans le tableau `joueur_data`. Et elle permet aussi d’initialiser les autres informations des joueurs à 0. Cette fonction appelle la fonction `main_control()`.
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "view.h"
#include "model.h"
#include "ansi_settings.h"
#include "global_variables.h"


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
```
- `main_control()` : Cette fonction est celle qui contrôle la logique du jeu. Elle permet d’appeler la fonction `nb_word_choice()` qui est la fonction qui demande aux joueurs avec combien de mots ils veulent jouer et qui retourne le nombre de mots choisi.
```c
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
```
Alors la fonction `main_control` appelle la fonction `main_game()` à deux reprises en lui envoyant le statut qui correspond à la position du joueur dans le tableau et `taille_tableau` qui contient le nombre de mots choisi par l’utilisateur. Cela avec un délai de 5 secondes entre les deux appels.
```c
//FONCTION DE CONTROL PRINCIPAL
void main_control(){

    int status;
    int taille_tableau = nb_word_choice();

    for(status = 0; status < 2; status++){
        main_game(status, taille_tableau);
        sleep(5);
    }

}
```
- `main_game()` : C’est la fonction où se déroule l’essentiel du jeu. Elle commence par appeler la fonction `ask_ready_to_start()` qui est une fonction permettant de demander au joueur s’il est prêt avant de lancer le chronomètre et de commencer à proposer les mots à taper. Si le joueur n’est pas prêt l’ordinateur lui demande combien de secondes doit-il attendre avant de lancer le jeu.
```c
//FONCTION QUI PERMET AU JOUEUR DE DECIDER QUAND COMMENCER LE JEU
int ask_ready_to_start(char* nomjoueur){

    system("cls");
    center_height();
    center_text(GREEN "READY TO START JOUEUR" RESET);
    printf(" %s ?\n\n", nomjoueur);
    center_text("Etes-vous pret a commencer ?\n\n");
    center_text("1. OUI    2. ATTENDRE\n\n");
    center_text("Choisissez une option :: ");

    int choix;
    scanf("%d", &choix);

    if (choix == 2)
    {
        //GESTION DU TEMPS D'ATTENTE
        int attente;
        center_text("\n");
        center_text("Combien de secondes ? :: ");
        scanf("%d", &attente);
        //count_time_animation(attente);
        sleep(attente);
        return 1;

    } else{

        return 1;
    }

}
```
Après cela nous initialisons la fonction `srand()` qui est en fait une fonction qui permet de générer des nombres aléatoirement. Ensuite la fonction `get_mots_from_file()` qui est la fonction qui nous permet de récupérer les mots de notre fichier `mots.txt` et de les stocker dans notre tableau `mots`. Après cela nous initialisons le chronomètre en utilisant `time_t debut = time(NULL)`. Ensuite en fonction du nombre de mots à saisir choisi par l’utilisateur nous appelons la fonction `choose_word_aleatory()` qui est une fonction qui renvoie un nombre aléatoire et ce nombre sera utilisé comme indice dans notre tableau de mots et va ainsi permettre de proposer des mots aléatoirement au joueur. Par la suite nous utilisons une boucle `do…while()` pour afficher à l’utilisateur le même mot aussi longtemps qu’il ne l’a pas bien saisi. Dans cette boucle nous appelons la fonction `show_player_name()` qui nous permet d’afficher le nom du joueur actuel et la fonction `suggest_get_user_word()` qui permet d’afficher le mot à saisir et de récupérer le mot saisi par le joueur. Nous utilisons la fonction `strcmp()` de la bibliothèque string pour comparer le mot à saisir et le mot saisi par le joueur. Si le joueur saisit le mot correctement on lui affiche le message correct cela en appelant la fonction `correct_message()` et inversement nous lui affichons le message `Mot incorrect`. Lorsque le joueur a fini de saisir tous les mots proposés selon le nombre choisi précédemment nous mettons fin à notre chronomètre en utilisant `time_t fin = time(NULL)`. Ensuite nous appelons la fonction `speed_calculation()` en lui envoyant comme paramètre `difftime(fin, debut)` et le nombre de mots choisi par le joueur. Cette fonction permet de calculer la vitesse de frappe du joueur et renvoie la valeur qui sera stockée dans la variable `vitesse`. La fonction `difftime()` renvoie le temps mis en seconde par le joueur pour saisir les mots. Après cela nous avons une condition qui nous permet d’appeler la fonction `write_in_file()` et `compare_joueur()` si l’indice actuel donc le statut reçu correspond au deuxième joueur.
```c
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
        compare_joueur(joueur_data ,joueur_data[0].vitesse, joueur_data[1].vitesse);
    }

}
```
- `compare_joueur()` : C’est la fonction qui nous permet de générer un rapport final et de déterminer lequel des joueurs est le plus rapide. Le rapport reprend toutes les informations concernant les deux joueurs. Après l’affichage du rapport l’ordinateur attend pendant 10 secondes avant d’appeler la fonction `restart_game()`.
```c
//FONCTION QUI PERMET DE DETERMINER LEQUEL DES JOUEURS EST LE PLUS RAPIDE SUR BASE DE LA VITESSE
void compare_joueur(JOUEUR joueur_data[], int vitesse1, int vitesse2){

    system("cls");
    center_height();
    center_text(UNDERLINE "\tRAPPORT FINAL\n\n" RESET);

    int i;

    for(i = 0; i < 2; i++){

        center_text(GREEN "JOUEUR ::: " RESET);
        printf("%s\n", joueur_data[i].nom_joueur);
        center_text(CYAN "Temps ecoule : " RESET);
        printf("%d sec\n", joueur_data[i].temps_mis);
        center_text(CYAN "Vitesse de frappe : " RESET);
        printf(" %d MPM\n\n", joueur_data[i].vitesse);
        center_text("==========================================\n\n");
    }


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

    sleep(10);
    restart_game();

}
```
- `restart_game()` : Cette fonction nous permet de demander aux joueurs s’ils voudraient rejouer une autre partie. Si Oui on appelle la fonction `main_control()` pour relancer le jeu. Si non on met fin à l’exécution du programme.
```c
//FONCTION QUI PERMET AUX JOUEUR DE REJOUER UNE PARTIE
void restart_game(){

    system("cls");
    center_height();
    center_text(BOLD BLUE CLIGNOTANT"\t\tUDBL-"RED"DACTYLOGICIEL"RESET"\n\n");
    center_text("Voulez-vous rejouer une partie ?\n\n");
    center_text("1. OUI    2. NON\n\n");
    center_text("Choisissez une option :: ");

    int choix;
    scanf("%d", &choix);

    if (choix == 2)
    {
        return;

    } else{
        system("cls");
        main_control();
    }

}
```
- `write_in_file()` : Cette fonction nous permet d’écrire les informations concernant les joueurs dans le fichier `joueurs.csv` afin de pouvoir les sauvegarder.
```c
void write_in_file(JOUEUR joueur_data[]){

    FILE* fichier = fopen("joueurs.csv", "a+");

        if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    int i;

    for (size_t i = 0; i < 2; i++)
    {
        fprintf(fichier, "%s,%d,%d\n", joueur_data[i].nom_joueur, joueur_data[i].temps_mis , joueur_data[i].vitesse);
    }

    fclose(fichier);
}
```
- `add_word_in_file()` : Cette fonction est celle appelée lorsque l’utilisateur choisit l’option configurer dans le menu. Cette fonction permet aux utilisateurs d’ajouter des mots dans le fichier `mots.txt`. Dans cette fonction nous demandons au joueur combien de mots il veut ajouter et nous lui permettons d’ajouter autant de mots qu’il a choisi d’ajouter. A chaque fois qu’un mot est ajouté nous affichons le message `Mot ajouté avec succès`.
```c
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

        fprintf(fichier, "%s\n", new_word);//AJOUTE LE MOT DANS LE FICHIER

        center_text("\n\n");
        center_text(GREEN "\tMot ajoute avec succes" RESET);
        sleep(2);
        i++;

    }

    fclose(fichier);
    menu();

}
```
- `aide()` : Cette fonction nous permet d’afficher les informations relatives à notre jeu. Notamment la description, la version, la date de conception, les noms des développeurs et autres. Dans cette fonction nous appelons les fonctions `scroll_animation()` et `return_to_menu()`.
```c
void aide(){

    center_height();
    center_text(UNDERLINE "\tA PROPOS\n\n" RESET);
    center_text(CYAN "\tUDBL-DACTYLOGICIEL " RESET "est un jeu concu pour aider les utilisateur a ameliorer\n");
    center_text("leur vitesse de frappe au clavier.\n\n");
    center_text("Le jeu consiste en fait a evaluer la vitesse de frappe de deux joueurs\n");
    center_text("et determiner lequel des deux est le plus rapide.\n\n");

    center_text(UNDERLINE "\tVERSION\n\n" RESET);
    center_text("Ceci est la version 1.0.1 de UDBL-DACTYLOGICIEL.\n\n");
    center_text("Concu en Juin 2024\n\n");

    center_text(UNDERLINE "\tCONCEPTEURS\n\n" RESET);
    center_text("MUKALA NSABUA GAEL\n");
    center_text("MUJINGA NDAYA MIRADIE \n");
    center_text("MUKAS KASONG CHRISTELLA\n");
    center_text("MIJINGA WA NGOIE ANITA\n\n");

    center_text("Ce jeu est encore en developpement donc vos remarques\n");
    center_text("et conseils constructifs seront les bienvenus\n");

    scroll_animation(3);

    return_to_menu();

}
```
- `scroll_animation()` : Cette fonction nous permet de créer une animation de défilement lors de l’affichage des informations concernant le jeu.
```c
//FONCTION QUI PERMET D'AVOIR UNE ANIMATION DE DEFILEMENT DE L'ECRAN
void scroll_animation(int n){

    int i = 0;
    while (i != n)
    {
        sleep(1);
        printf("\n");
        i++;
    }

}
```
- `return_to_menu()` : Cette fonction permet à l’utilisateur de revenir au menu ou de quitter le jeu après l’affichage des informations concernant le jeu.
```c
void return_to_menu(){

    center_text("Voulez-vous revenir au menu ?\n");
    center_text("1. OUI    2. NON\n\n");
    center_text("Choisissez une option :: ");

    int choix;
    scanf("%d", &choix);

    if (choix == 2)
    {
        return;
    } else{
        system("cls");
        menu();
    }

}
```

En tout, notre jeu a été implémenté dans 22 fonctions nous permettant de gérer l’ensemble du jeu.

## Environnement de développement
Comme environnement de développement nous avons eu à utiliser Visual Studio Code pour écrire nos fonctions. Et nous avons utilisé CodeBlocks pour l’exécution du code et les différents tests. Nous avons utilisé Git pour le versionnage de notre projet dans notre dépôt local et Github pour le dépôt distant.

## Répartition des tâches
- **MUJINGA NDAYA MIRADIE**
  - Fonction qui permet de générer des mots aléatoirement
  - Fonction qui demande à l'utilisateur de saisir un mot jusqu'à ce que l'utilisateur saisisse le mot correctement
- **MUJINGA WA NGOIE ANITA**
  - Fonction qui permet d'afficher le temps que l'utilisateur a mis pour saisir un texte
  - Comment afficher un texte coloré dans la console
- **MUKAS KASONG CHRISTELLA**
  - Fonction qui permet d'écrire des données dans un fichier
  - Fonction qui permet de lire des données écrites dans un fichier
- **MUKALA NSABUA GAEL**
  - Intégration de chaque fonction afin de former un ensemble fonctionnel
  - Gestion des fonctions relatives à l’affichage
  - Développement et implémentation de la logique du jeu
  - Responsable du versionnage avec Git et du dépôt distant sur Github
  - Rédaction du rapport
  - Coordination de l’équipe et répartition des tâches

# CONCLUSION
