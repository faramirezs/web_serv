#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <set>

class Request
{
    private:
        /* data */
    public:
        Request();
        Request(Request const & serv);
        Request& operator=(Request const & rhs);
        Request(int port);
        ~Request();

        sockaddr_in clientAddress;
        socklen_t clientSize;
        int clientSocket;
        char clientIP[INET_ADDRSTRLEN];
        int clientPort;
        int servSocket;
};
