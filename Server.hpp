#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <set>

class Server
{
    private:
        /* data */
    public:
        Server(Server const & serv);
        Server& operator=(Server const & rhs);
        Server(int port);
        ~Server();

        sockaddr_in serverAddress;
        int serverSocket;
};
