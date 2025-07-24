#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

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

    //Accept connections
    sockaddr_in clientAddress;
    socklen_t clientSize = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (sockaddr *)&clientAddress, &clientSize);
    if (clientSocket == -1) {
        std::cerr << "Error accepting request" << std::endl;
        close(serverSocket);
        return 4;
    }

    //Get client's IP address and port
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIP, INET_ADDRSTRLEN);
    int clientPort = ntohs(clientAddress.sin_port);
    std::cout << "Accepted connection from " << clientIP << ":" << clientPort
            << std::endl;
    
    // select()implementation
    //int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
    
    //You must never do a read or a write operation without going through poll() (or equivalent)
    
    char recv_buffer[1024];
    int recved = recv(clientSocket, recv_buffer, 1024, 0);
    std::cout << "Received " << recved << " bytes." << std::endl;

    //const char *message = "Hello from server!\n";
    int sent = send(clientSocket, recv_buffer, recved, 0);
    std::cout << "Sent " << sent << " bytes." << std::endl;

    // Close sockets
    close(serverSocket);
    close(clientSocket);

    return 0;
}
