#include "server.h"


UdpServer::UdpServer()
{
}
UdpServer::~UdpServer()
{
    m_iFd = -1;
    close(m_iFd);
}

UdpServer:: UdpServer(const char*ip, const unsigned  port) : m_iFd(-1)
{
    memset(&m_sockServer,0x00, sizeof(m_sockServer));

    if( (m_iFd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)	
    {
	perror("socket:");
        printf("Udp sock is wrong\n");
    }
    m_sockServer.sin_family = AF_INET;
    m_sockServer.sin_addr.s_addr = inet_addr(ip);
    m_sockServer.sin_port = htons(port);

    if( (bind(m_iFd,(struct sockaddr*)&m_sockServer, sizeof(m_sockServer))) == -1)
    {
        printf("Udp bind is wrong\n");
    }
 
}
int UdpServer::fnSendDataToServer(const char*msg, int len)
{
    int iResult = 0;

    iResult = sendto(m_iFd, msg, len, 0, (struct sockaddr*)&m_sockServer,sizeof(SOCKADDR));	
    //printf("server recv=%s\n", msg);
}

int UdpServer::fnReadDataFromServer()
{
    char tmp[10];
    socklen_t iCliLen = sizeof(m_sockClient);

    memset(tmp, 0x00, sizeof(tmp)); 

    timeval timeo, timeo1;

    memset(&timeo, 0x00, sizeof(timeo));
    memset(&timeo1, 0x00, sizeof(timeo1));
    timeo.tv_sec = 10000;
    timeo.tv_usec = 0;	

    setsockopt(m_iFd, SOL_SOCKET,SO_RCVTIMEO, &timeo,sizeof(timeo));
	
    fd_set fdSet;
    FD_ZERO(&fdSet);
    FD_SET(m_iFd, &fdSet);    

    timeo1.tv_sec = 10000;
    timeo1.tv_usec = 0;	

    int result = select(m_iFd+1, &fdSet, NULL,NULL, &timeo1);
   // int result = select(m_iFd+1, &fdSet, NULL,NULL, NULL);
    if( result < 0)
         printf("select is wrong\n");
    else if (result == 0)
         printf("time out");

    recvfrom(m_iFd, tmp, strlen(tmp), 0, (struct sockaddr*)&m_sockClient,&iCliLen);	
    printf("server recv=%s\n", tmp);
    return 0;
}
