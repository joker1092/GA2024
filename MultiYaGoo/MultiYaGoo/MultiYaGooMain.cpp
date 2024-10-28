#include <cstdio>
#include <string>
#include <queue>
#include "SessionManager.h"

#pragma comment(lib, "ws2_32.lib")


class MultiYaGooMain
{
public:
    MultiYaGooMain()
    {
        
    }
    ~MultiYaGooMain()
    {
    }
  
    void Run(std::string listenIp, const int listenPort)
    {

        if (m_sessionManager.Start(listenIp.c_str(), listenPort) == false)
        {
            printf("Failed to listen : \n", WSAGetLastError());
            return;
        }

        while (true)
        {
           m_sessionManager.Update();

           // Sleep(1);

           //GameUpdate();
       }
    }

    private:

    ClientSessionManager m_sessionManager;

};


MultiYaGooMain g_appMain;

int main(int argc, char* argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s <ip> <port>\n", argv[0]);
       
        return 1;
    }

   
    std::string ip = argv[1];
    int port = std::atoi(argv[2]);
    
    InitWinSock();

    printf("ip: %s, port: %d\n", ip.c_str(), port);

    g_appMain.Run(ip, port);
   

    CleanupWinSock();


    return 0;
}

