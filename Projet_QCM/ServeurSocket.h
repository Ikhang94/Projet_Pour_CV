//
// Created by caoth on 07/02/2023.
//

#ifndef PROJET_QCM_SERVEURSOCKET_H
#define PROJET_QCM_SERVEURSOCKET_H
#include <winsock2.h>
#include <iostream>
#include <fstream>
#define VERSION 0x0101

class ServeurSocket
{
private :
    SOCKET			prise;
    SOCKADDR_IN		connection;

public :
    ServeurSocket(u_short);
    ~ServeurSocket();
    int recoit(int, char FAR * const) const;
    unsigned long recoitFic(char FAR *const) const;
};


#endif //PROJET_QCM_SERVEURSOCKET_H
