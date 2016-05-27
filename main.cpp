#include "test1.h"
#include "server.h"

int main()
{
    char *szBuf = "hello";
    UdpServer server("127.0.0.1",8888);
    //server.fnSendDataToServer(szBuf, strlen(szBuf)); 
    server.fnReadDataFromServer();
    return 0;	
}
