#include <iostream>
#include <cstdio>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <set>
#include <fcntl.h>

class Server
{
    private:
        /* data */
    public:
        Server();
        Server(Server const & serv);
        Server& operator=(Server const & rhs);
        Server(int port);
        ~Server();

        sockaddr_in serverAddress;
        int serverSocket;
        char serv_buffer[1024];
        
};
