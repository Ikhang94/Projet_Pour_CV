#include "ClientSocket.h"
#include "ServeurSocket.h"
#include <winsock2.h>
#include <string.h>
#include "TraitementImage.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

int main(int argc, char *argv[]) {

    u_short numPortserveur=1234;
    u_short numPortclient=2345;
    char nomfic[100] = "imageCv.jpg";
    char adresse[16];
    char message[26]="";
    int nbRecu;
    int nbEmis;
    //std::cout << "ServeurSocket : Entrez un numero de port compris entre 1024 et 65535 : ";
    //std::cin >> numPortserveur;
    ServeurSocket monserveur(numPortserveur);
    //std::cout << "CLIENT : Entrez un numero de port compris entre 1024 et 65535 :";
    //std::cin >> numPortclient;
    std::cout << "CLIENT : Entrez le numero IP de la station destinatrice : ";
    std::cin >> adresse;
    ClientSocket monClient(numPortclient, (char*) adresse);
    //std::cout << "CLIENT : Entrez le nom du fichier :" << std::endl;

    //remove(nomfic); //supprime l'image si existe déjà

    while (true){

    std::cout << "Attente de recevoir un fichier image"<<std::endl;
    nbRecu = monserveur.recoitFic(nomfic);
    if (nbRecu != SOCKET_ERROR) {
        std::cout << "Reception de " << nbRecu << " octets dans " << nomfic <<
                  std::endl;
    } else {

        std::cout << "Probleme d'emission !!!" << std::endl;
        return 0;

    }


    Mat image = imread(nomfic);
    resize(image, image, Size(),0.3,0.3, INTER_LINEAR); //change la taille de l'image
    //imshow("photo",image);// affiche l'image original
    Mat image_copy = image.clone();//copie de l'image original
    std::vector<std::vector<Point> > squares; // variable de type vector qui stocke d'autre vector contenant des Points
    std::vector<std::vector<int> > carton; // vector contenant d'autre vector contenant eux même des éléments de type int
    localiserCarre(image,squares); // localise le carré blanc de chaque carton dans l'image
    IdentificationReponse(image_copy,squares,carton);// detecte les cartons dans l'image et construit un vector de réponses


    for (int i=0;i<carton.size();i++){ // boucle permettant d'envoyer toute les réponses construites
        for (int j=0;j<carton[i].size();j++){
            // conversion de int en char
            if (carton[i][j]==1){

                message[j]='1';
            }
            else{

                message[j]='0';

            }
            //std::cout<<message[j];
        }
        //std::cout<<std::endl;

        // envoie de message contenant une réponse tirée d'un carton
        nbEmis = monClient.emet(strlen(message), message);
        if (nbEmis != SOCKET_ERROR) { // verifie si nbEmis=code d'erreur socket
            std::cout << "Emission de " << nbEmis << " octets : " << message <<
                      std::endl;
        } else {
            std::cout << "Probleme d'emission !!!" << std::endl;

        }

        }
    if (int erreurfic=remove(nomfic)!=0){//supprime l'image reçu
        std::cout<<"impossible de supprimer"<<erreurfic<<std::endl;

    }
    else{
        std::cout<<"fichier "<<nomfic <<" supprimer"<<std::endl;
    }

    }

    return 0;
}

