#include "codeShifumi.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "library.h"

using namespace std;

void debutpartie(unsigned long *nbhexa) {
    char seriecoup[11];// variable seriecoup de type char qui est une chaîne de caractère utilisé en paramètre pour les différentes fonctions utilisées par le programme
    strcpy(seriecoup, " ");// fonction qui copie " " dans la chaîne de caractère seriecoup pour "netoyé" l'adresse mémoire de ce dernier
    char coup; // variable coup de type char qui permet au joueur de rentrer un coup (P, F, C)
    char nbbin[45] = "0000 0000 0000 "; // chaine de caractère de 45 emplacements qui enregistre la combinaison de coup sous forme binaire

    for (int i = 0;i < 10; i++) {
        // boucle for qui permet au joueur de rentrer à chaque passage de boucle un coup (P, F, C)

        std::cout << "Entrez votre choix pour le tour " << i << ":";//affiche le tour où est le joueur dans la console
        std::cin >> coup; // l'utlisateur entre une valeur à la variable coup et chosit entre (p, f, c)
        std::cout << std::endl; // retour à la ligne
        coup = toupper(coup); // fonction de la bibliothèque string.h qui permet de mettre en majuscule une chaîne de caractère ou un caractère

        if (coup != 'P' && coup != 'F' && coup != 'C') {
            // condition qui vérifie si la variable coup est égal à P, F ou C
            while (coup != 'P' && coup != 'F' && coup != 'C') {
                // boucle while qui permet au joueur de rentrer un coup valide (P, F, C)

                std::cout << "Entrez un choix valide (P , F ou C) pour le tour " << i << ":";
                std::cin >> coup; // le joueur rentre de nouveau un coup
                coup = toupper(coup); // met en majuscule le caractère
            }
        }
        *(seriecoup + i) = coup; // le coup rentré par le joueur est stocké dans la variable seriecoup
        switch (*(seriecoup +i)) { // structure d'aiguillage multiple (switch case) qui effectue certaine partie de la structure
            // en fonction du coup stocké dans seriecoup
            case 'P':
                strcat(nbbin,"01");// fonction dans la bibliotheque string.h qui rajoute dans nbbin la chaîne de caractère "01"
                strcat(nbbin, " ");// fonction dans la bibliotheque string.h qui rajoute dans nbbin un espace
                *nbhexa += 1;// rajoute à la variable nbhexa 1
                break;// commande qui permet de sortir de la structure

            case 'F':
                strcat(nbbin,"10");// fonction dans la bibliotheque string.h qui rajoute dans nbbin la chaîne de caractère "10"
                strcat(nbbin, " ");
                *nbhexa += 2;// rajoute à la variable nbhexa 2
                break;

            case 'C':
                strcat(nbbin,"11");// fonction dans la bibliotheque string.h qui rajoute dans nbbin la chaîne de caractère "11"
                strcat(nbbin, " ");
                *nbhexa += 3;// rajoute à la variable nbhexa 3
                break;
        }
        if (i !=9) { // condition qui vérifie si i est différent de 9,
            // si oui le programme effectue les instructions en dessous
            *nbhexa = *nbhexa << 2; // décalage de 2 bits à gauche du nombre nbhexa
        }
    }
    std::cout << "Vous avez fait ce choix : " << seriecoup << std::endl;
    // affiche dans la console la combinaison de coup rentrée par le joueur sous forme de lettre
    std::cout << "Le resultat vaut : " << "0x000" << std::hex << *nbhexa << " soit " << nbbin << "en binaire"<< std::endl;
    // affiche dans la console la combinaison de coup rentrée par le joueur sous forme binaire et hexadécimal
}

void creationfichier(unsigned long *nbcombi, FILE *f, char *nomf) {
    if ((f = fopen(nomf, "wb")) != NULL) { // ouverture du fichier f en mode wb
        // condition if qui verifie si le fichier est bien créé
        fwrite("prj1", sizeof(char), 4, f); // écrit en 4 fois dans le fichier "prj1"
        fwrite(nbcombi, sizeof(unsigned long), 1, f); //écrit dans le fichier la valeur hexadécimal de la combinaison de coup
        fclose(f); // ferme le fichier
        std::cout << " le fichier est cree" << std::endl;
    } else {
        std::cout << "Ouverture de fichier impossible" << std::endl;
        exit(-1);
    }
}
