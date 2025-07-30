#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <set>

/* struct sockaddr {
    unsigned short sa_family;
    char sa_data[14];
};

struct sockaddr_in {
    short sin_family;
    unsigned short sin_port; // Port Number
    struct in_addr sin_addr; // IP Address
    char sin_zero[8];
};

struct in_addr {
    unsigned long s_addr; // 4 bytes long
}; */



int main ()
{
    //Create socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if (serverSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    fd_set readfds;
    fd_set writefds;
    std::set<int> clients;
    struct timeval timeout;

    FD_SET(serverSocket, &readfds);
    //Create serverAddress
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    //bind the socket to server
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1){
            std::cerr << "Error binding socket" << std::endl;
            close(serverSocket);
            return 2;
        }

    //Listen
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening" << std::endl;
        close(serverSocket);
        return 3;
    }
    std::cout << "Server listening on port 8080" << std::endl;
    
    sockaddr_in clientAddress;
    socklen_t clientSize = sizeof(clientAddress);
    int clientSocket;
    char clientIP[INET_ADDRSTRLEN];
    int clientPort;
    int fd;
    char recv_buffer[1024];
    int recved;
    int sent;
    int nfds;
    
    while(true){
        FD_ZERO(&readfds); // We rubuild the whole set before select call.
        FD_SET(serverSocket, &readfds); // Adds server socket to set
        // Adds client sockets to set
        for (std::set<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
            fd = *it;
            FD_SET(fd, &readfds);
        }

        nfds = serverSocket + 1;
        if (!clients.empty())
            if(*clients.rbegin() > serverSocket)
                nfds = *clients.rbegin() + 1;

        timeout.tv_sec = 10;
        select(nfds, &readfds, &writefds, NULL, &timeout);
        
        if (FD_ISSET(serverSocket, &readfds)) {
            
            clientSocket = accept(serverSocket, (sockaddr *)&clientAddress, &clientSize);
            if (clientSocket == -1) {
                std::cerr << "Error accepting request" << std::endl;
                close(serverSocket);
                return 4;
            }
            clients.insert(clientSocket);
            inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIP, INET_ADDRSTRLEN);
            clientPort = ntohs(clientAddress.sin_port);
            std::cout << "Accepted connection from " << clientIP << ":" << clientPort
                    << std::endl;
        }
        
        for (std::set<int>::iterator it = clients.begin(); it != clients.end();) {
            fd = *it;
            if(FD_ISSET(fd, &readfds)) {
                if((recved = recv(fd, recv_buffer, 1024, 0))<= 0) {
                    clients.erase(it++);
                    close(fd);
                    it = clients.erase(it);
                    continue;
                }

                std::cout << "recv_buffer: " << recv_buffer << std::endl;
                std::cout << "Received " << recved << " bytes." << std::endl;
                sent = send(fd, recv_buffer, recved, 0);
                std::cout << "Sent " << sent << " bytes." << std::endl;
                close(fd);
                ++it;
            }
        }
    }
    close(serverSocket);

    return 0;
}
