#ifndef SERVER_H
#define SERVER_H

#include "head.h"

typedef struct sockaddr SOCKADDR;
class UdpServer
{
    int m_iFd;
    struct sockaddr_in m_sockServer;
    struct sockaddr_in m_sockClient;   

public:
    UdpServer();
    UdpServer(const char *ip, unsigned int port);	
    ~UdpServer();
    int fnSendDataToServer(const char*msg, int len );
    int fnReadDataFromServer();
};
    


#endif



