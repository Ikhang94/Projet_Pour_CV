#include <iostream>
#include "codeShifumi.h"
#include <string.h>
#include <stdio.h>
#include "library.h"

int main() {

    int choix ; // la variable choix de type int permet à l'utilisateur de choisir différentes fonctionnalités proposé par le programme
    char seriecoup[11]; // variable seriecoup de type char qui esr une chaîne de caractère utilisé en paramètre pour les différents fonctions utilisées par le programme
    unsigned long nbhexa = 0; // la variable nbhexa de type unsigned long est utilisé en paramètre pour différentes fonctions
    strcpy(seriecoup, " ");// fonction qui copie " " dans la chaîne de caractère seriecoup pour "netoyé" l'adresse mémoire de ce dernier

    FILE *fichier; // pointeur sur un fichier
    char nomf[100];// variable nomf de type char qui est une chaîne de caractère qui stockera le nom du fichier
    LlwClientSocket Cao(1113, "172.20.10.13"); // instanciation de la classe LlwClientSocket avec le n° de port et l'adresse ip du serveur


    do{ // boucle do while qui permet à l'utilisateur de choisir l'option qu'il veut (comme un menu)

        std::cout << "Entrez un chiffre compris entre 0 et 3: " << std::endl;
        std::cout << "1 - Debuter une partie" << std::endl;
        std::cout << "2 - Creer le fichier resultat" << std::endl;
        std::cout << "3 - Envoyer le fichier au serveur" << std::endl;
        std::cout << "0 - Exit" << std::endl;
        std::cin >> choix; // le joueur chosit une des options montré par le programme

        switch (choix) { // structure d'aiguillage multiple (switch case) qui effectue certaine partie de la structure
            // en fonction de la valeur de choix définie par le joueur

            case 1 :
                debutpartie(&nbhexa); // dans le cas de choix=1, le programme fait appel à la fonction debutpartie()
                // qui prend en paramètre l'adresse de seriecoup
                break; // permet de sortir du switch case prématurement

            case 2 :
                std::cout << "Saississez un nom de fichier (sans espaces) :"; // le joueur choisi le nom du fichier
                std::cin >> nomf;
                std::cout << std::endl; //retour à la ligne
                creationfichier(&nbhexa, fichier,nomf);// dans le cas de choix=2, le programme fait appel à la fonction creationfichier()
                // qui prend en paramètre l'adresse de la combinaison en hexadécimal, un fichier et
                // une chaine de caractère qui représente le nom d'un fichier
                break;

            case 3 :
                // dans le cas de choix=3
                int taille; //variable taille de type int qui stockera la taille du fichier
                taille = Cao.tailleFichier(nomf); // appel de la fonction TailleFichier de la classe LlwClientSocket qui renvoie la taille du fichier
                Cao.emetFichier(nomf, taille);//appel de la focntion EmetFichier de la classe LlwClientSocket qui envoie le fichier au serveur
                //std::cout<<"Le fichier est envoye au serveur"<<std::endl;
                break;

            default:
                std::cout<<"Veuillez choisir une option valide"<<endl;
                break;

        }



    }
    while (choix != 0);

    return 0;
}



