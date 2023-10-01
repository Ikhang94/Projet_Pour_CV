#include "ClientSocket.h"
#include <winsock2.h>
/*********************************************************************************
Nom :
Constructeur de la classe ClientSocket
Role :
Cree une socket et l'initialise.
Permet l'emission vers l'adresse IP precisee.
Parametres passes :
port : numero de port auquel relier la socket creee
adrIp : adresse IP du destinataire
Valeur renvoyee :
-
*********************************************************************************/
ClientSocket::ClientSocket(u_short port, TT_AdrIP adrIp) {
    int erreur; // variable qui permet de vérifier si on peut utiliser la DLL Socket
    WSADATA dllDescriptif;
    erreur = WSAStartup(VERSION, &dllDescriptif);//Utilisation de la DLL Socket
    if (erreur != 0) {
        std::cout << "Erreur d'initialisation de la DLL Winsock - " << std::endl;
        exit(1);
    } else {
        std::cout << "Initialisation de la DLL Winsock : OK - " << std::endl;
        prise = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP); //création de la socket
        if (prise == INVALID_SOCKET) {
            std::cout << "Erreur de socket - " << std::endl;
            exit(2);
        } else {
            std::cout << "Initialisation socket : OK - " << std::endl;
            connection.sin_family = AF_INET;//famille d'adresse
            connection.sin_addr.s_addr = inet_addr((char *) adrIp);//adresse IP du serveur de destination
            connection.sin_port = htons(port);//numéro de port du serveur de destination
        }
    }
}
/*********************************************************************************
Nom :
Destructeur de la classe ClientSocket
Role :
Ferme la socket creee par le constructeur.
Parametres passes :
-
Valeur renvoyee :
-
*********************************************************************************/
ClientSocket::~ClientSocket() {
    closesocket(prise);
    WSACleanup();
}

/*********************************************************************************
Nom :
emet
Role :
Envoit des donnees
Parametres passes :
nbrOct : nombre d'octets a envoyer
adrOct : adresse ou sont stockes les octets ‡ envoyer
Valeur renvoyee :
int : nombre d'octets effectivement envoyes
*********************************************************************************/
int ClientSocket::emet(int nbrOct, char FAR const *adrOct) const {

    int octemis; // nb octet envoyé
    int taille = sizeof(SOCKADDR);
    // envoi de d'une chaine de caractère
    octemis = sendto(prise, adrOct, nbrOct, 0, (LPSOCKADDR) &connection, taille);
    if (octemis == SOCKET_ERROR) {
        std::cout << "Erreur d'emission :" << WSAGetLastError() << std::endl;

    }
    return octemis;
}



