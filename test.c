 FILE* fichier = fopen("joueurs.txt", "r");

        if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    char ligne[100];
    int i = 0;
    int vitesse1;
    int vitesse2;

    // //fgets(ligne, sizeof(ligne), fichier);
    // fscanf(fichier, "%s %d %d", joueur1.nom_joueur, &joueur1.temps_mis, &vitesse1);
    // fscanf(fichier, "%s %d %d", joueur2.nom_joueur, &joueur2.temps_mis, &vitesse2);
    // printf("Nom : %s, Temps mis : %d, Vitesse :%d\n", joueur1.nom_joueur, joueur1.temps_mis, vitesse1);

    
    printf("Nom : %s, Temps mis : %d, Vitesse :%d\n", joueur2.nom_joueur, joueur2.temps_mis, vitesse2);


    // while (fgets(ligne, sizeof(ligne), fichier) != NULL) {

    //     sscanf(ligne, "%[^ ] %.0f %.2f", joueur[].nom_joueur, &joueur_DATA[i].temps_mis, &joueur_DATA[i].vitesse);
    //     printf("Nom : %s, Temps mis : %.0f, Vitesse :%.2f\n", joueur_DATA[i].nom_joueur, joueur_DATA[i].temps_mis, joueur_DATA[i].vitesse);

    //     i++;
    // }

    fclose(fichier);