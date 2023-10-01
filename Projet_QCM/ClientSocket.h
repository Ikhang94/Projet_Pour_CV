#include <winsock2.h>
#include <iostream>
#include <fstream>
#define VERSION 0x0101
#ifndef PROJET_QCM_CLIENT_H
#define PROJET_QCM_CLIENT_H
typedef char (TT_AdrIP)[16];
class ClientSocket {


private :
    SOCKET prise;
    SOCKADDR_IN connection;
public :
    ClientSocket(u_short, TT_AdrIP); // recoit le numero de port et l'adresse IP
    ~ClientSocket();
    int emet(int, char FAR const *) const;

};


#endif //PROJET_QCM_CLIENT_H
