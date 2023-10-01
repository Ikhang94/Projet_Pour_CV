#ifndef LWSOCKET_LIBRARY_H
#define LWSOCKET_LIBRARY_H

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>


typedef char (TT_AdrIP)[16];
typedef unsigned short ushort;
#define VERSION 0x0101
#define LENGHT 8


class LlwClientSocket {

private:
    SOCKET prise;
    SOCKADDR_IN connexion;

public:
    LlwClientSocket(ushort, TT_AdrIP);
    virtual ~LlwClientSocket();

    int emetChaine(char const *, int) const;
    int recoitChaine(char const *, int) const;

    int tailleFichier(char* ); //fonction de type int qui prend en paramètre le nom d'un fichier de type char
    // et renvoie la taille du fichier
    int emetFichier(char *,int); //fonction de type int qui prend en paramètre le nom d'un fichier de type char et
};



#endif //LWSOCKET_LIBRARY_H
