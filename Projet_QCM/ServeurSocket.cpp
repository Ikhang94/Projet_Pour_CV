#include "ServeurSocket.h"
#include <stdlib.h>

/*****************************************************************************************
Nom :
	Constructeur de la classe ServeurSocket

Role :
	Cree une socket, l'initialise, et la relie au port indique.
	Permet la reception a partir de n'importe qu'elle adresse IP d'emetteur.

Parametres passes :
	port : numero de port auquel relier la socket creee

Valeur renvoyee :
	-
******************************************************************************************/
ServeurSocket::ServeurSocket(u_short P_port)
{
    int erreur; // variable qui permet de vérifier si on peut utiliser la DLL Socket
    int etat; // variable qui vérifie si la liason socket s'est correctement ouverte
    WSADATA dllDescriptif;

    erreur = WSAStartup(VERSION, &dllDescriptif);//Utilisation de la DLL Socket
    if (erreur != 0) {
        std::cout << "Erreur d'initialisation de la DLL Winsock - " << std::endl;
        exit(1);
    } else {
        std::cout << "Initialisation de la DLL Winsock : OK - " << std::endl;
        prise = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP); //Création du Socket
        if (prise == INVALID_SOCKET) {
            std::cout << "Erreur de socket - " << std::endl;
            exit(2);
        } else {
            std::cout << "Initialisation socket : OK - " << std::endl;
            connection.sin_family = AF_INET;
            connection.sin_addr.s_addr = INADDR_ANY;
            connection.sin_port = htons(P_port); // numéro de port du serveur
            //liason de la socket sur une adresse et un port
            etat = bind(prise, (LPSOCKADDR) &connection, sizeof(connection));
            if (etat == SOCKET_ERROR) {
                std::cout << "Erreur de bind: " << etat << std::endl;
                exit(3);
            }
        }
    }
}


/******************************************************************************************
Nom :
	Destructeur de la classe ServeurSocket

Role :
	Ferme la socket creee par le constructeur.

Parametres passes :
	-

Valeur renvoyee :
	-
******************************************************************************************/
ServeurSocket::~ServeurSocket()
{
    closesocket(prise);
    WSACleanup();
}


/******************************************************************************************
Nom :
	recoit

Role :
	Attend de recevoir des donnees (bloquant)

Parametres passes :
	nbrOct : nombre d'octets attendus
	adrOct : adresse ou mettre les octets recus

Valeur renvoyee :
	int : nombre d'octets effectivement recus
******************************************************************************************/
int ServeurSocket::recoit(int nbrOct, char FAR *const adrOct) const {
    int octrecus;
    int taille = sizeof(SOCKADDR);

    octrecus = recvfrom(prise, adrOct, nbrOct, 0, (LPSOCKADDR) &connection, &taille);
    if (octrecus == SOCKET_ERROR) {
        std::cout << "Erreur de réception :" << WSAGetLastError() << std::endl;
    } else {
        if (octrecus == 0)
            std::cout << "Liaison fermée" << std::endl;
    }
    return octrecus;
}

unsigned long ServeurSocket::recoitFic(char FAR *const nomFic) const {
    //HANDLE fic;
    FILE *pFichier=NULL; // pointeur vers un fichier
    unsigned long recu = 0;// nb octet reçu pour une trame reçu
    unsigned long nboctet = 0;// nb octet reçu lors de la reception de la taille de l'image
    int taille = sizeof(SOCKADDR); // taille de la structure SOCKADDR
    unsigned long octetrecu;// nb octet reçu
    //char data[1024];
    char bufftaille[100];// buffer qui va contenir la taille du fichier
    int tailleRecu=0; // variable pour vérifier s'il y a une erreur de réception
    int taillefic=0; // taille du fichier reçu
    pFichier=fopen(nomFic, "wb");// ouverture du fichier
    if (pFichier!=NULL) { // vérifie si le fichier s'est bien ouvert

        //Le serveur socket va attendre jusqu'à recevoir la taille d'un fichier
        tailleRecu = recvfrom(prise, bufftaille, sizeof(bufftaille), 0, (LPSOCKADDR) &connection, &taille);
        if (tailleRecu == SOCKET_ERROR) { // verifie si tailleRecu=code d'erreur socket
            std::cout << "Erreur de réception :" << WSAGetLastError() << std::endl;
        }
        taillefic = atoi(bufftaille); // convertie un char en int
        std::cout << "taille du fichier egal a : "<<taillefic << std::endl; // affiche la taille du fichier sur la console
        auto cpt = 0;
        while(taillefic>0) { // boucle qui continue tant que tout les octets nécessaires n'ont pas été envoyés
            std::cout << "tour " << cpt++ << std::endl;
            if (taillefic<1024){ //Vérifie si le nombre d'octet à recevoir est inférieur à 1024

                const auto tailleBuffer=taillefic;
                char data[taillefic]; //Buffer avec une taille égale aux derniers octets du fichier à recevoir
                //reception des derniers octets du fichier à recevoir
                nboctet = recvfrom(prise, data, tailleBuffer, 0, (LPSOCKADDR) &connection, &taille);
                if (nboctet == SOCKET_ERROR) { // verifie si nboctet=code d'erreur socket
                    std::cout << "Erreur de réception :" << WSAGetLastError() << std::endl;
                }
                fwrite(data,tailleBuffer,1,pFichier);// écriture des octets reçus dans le fichier
                octetrecu+=taillefic;//ajout des octets récemment reçu au nombre total d'octet reçu
                taillefic=0;

            }
            else {

                const auto tailleBuffer=1024;
                char data[tailleBuffer]; //Buffer avec une taille égale à 1024 octets
                //reception d'une trame de 1024 octet
                nboctet = recvfrom(prise, data, tailleBuffer, 0, (LPSOCKADDR) &connection, &taille);
                if (nboctet == SOCKET_ERROR) {// verifie si nboctet=code d'erreur socket
                    std::cout << "Erreur de réception :" << WSAGetLastError() << std::endl;
                }
                fwrite(data,tailleBuffer,1,pFichier);// écriture des octets reçus dans le fichier
                taillefic-=nboctet;// reduit le nombre d'octet restant à recevoir
                octetrecu+=nboctet;// ajout des octets récemment reçu au nombre total d'octet reçu
            }

        }

    }
    else {

        printf("ERREUR: Impossible d'ouvrir le fichier \n");
        exit(-1);

    }
    fclose(pFichier); // fermeture du fichier
    return octetrecu;

}

