#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <set>
#include <vector>
#include <map>
#include "Server.hpp"
#include "Request.hpp"

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

struct s_master 
{
    std::vector<Server> servVec;
    std::set<int> servPorts;
    fd_set readfds;
    fd_set writefds;
    std::set<int> clients;
    std::map<int, int> requestFds;
    //std::map<int, Client> requestFds;
    std::map<Request, Server> reqServMap;
    std::map<int, Request> fdReqMap; 
    std::map<int, int> clientFdServFd; 
    int nfds;
    char recv_buffer[1024];
    int recved;
    int sent; 
};

void parse(char**av, s_master &master)
{
    size_t i;
    i = 1;
    while(av[i])
    {
        master.servPorts.insert(atoi(av[i]));
        i++;
    }
}

void startServ(s_master &master)
{
    for (std::set<int>::iterator it = master.servPorts.begin(); it != master.servPorts.end(); it++)
    {
        master.servVec.push_back(Server(*it));

    }
    
}

void closeServSocket(s_master &master)
{
    for (std::vector<Server>::iterator it = master.servVec.begin(); it != master.servVec.end(); it++)
    {
        close((*it).serverSocket);
    }
}

void fdSetServer(s_master &master)
{
    // Adds the file descriptor
    for (std::vector<Server>::iterator it = master.servVec.begin(); it != master.servVec.end(); it++)
    {
        FD_SET((*it).serverSocket, &master.readfds);
    }
}

void fdSetClient(s_master &master)
{
    for (std::set<int>::iterator it = master.clients.begin(); it != master.clients.end(); ++it) {
            FD_SET((*it), &master.readfds);
        }
}

void getNfds(s_master &master)
{
    master.nfds = 0;
    for (std::vector<Server>::iterator it = master.servVec.begin(); it != master.servVec.end(); it++)
    {
        if(master.nfds < (*it).serverSocket)
            master.nfds = (*it).serverSocket;
    }
    
    for (std::set<int>::iterator it = master.clients.begin(); it !=master.clients.end(); it++)
    {
        if(master.nfds < (*it))
            master.nfds = (*it);
    }
    master.nfds = master.nfds + 1;
}


void acceptRequests(s_master &master) 
{
    for (std::vector<Server>::iterator it = master.servVec.begin(); it != master.servVec.end(); it++)
    {
        if (FD_ISSET((*it).serverSocket, &master.readfds)) 
        {
            Request *req;
            req = new(Request);
            master.reqServMap.insert({Request(), (*it)});
            req->servSocket = (*it).serverSocket;
            req->clientSocket = accept((*it).serverSocket, (sockaddr *)&req->clientAddress, &req->clientSize);
            if (req->clientSocket == -1) {
                std::cerr << "Error accepting request" << std::endl;
                close((*it).serverSocket);
            }
            master.clients.insert(req->clientSocket);
            inet_ntop(AF_INET, &(req->clientAddress.sin_addr), req->clientIP, INET_ADDRSTRLEN);
            req->clientPort = ntohs(req->clientAddress.sin_port);
            master.fdReqMap.insert({req->clientSocket, Request(*req)});
            std::cout << "Accepted connection from " << req->clientIP << ":" << req->clientPort
                    << std::endl;
        }
    }
    
}

void receiveRequests(s_master &master) 
{
    int fd;

    for (std::set<int>::iterator it = master.clients.begin(); it != master.clients.end();) 
    {
        fd = *it;
        if(FD_ISSET(fd, &master.readfds)) {
            if((master.recved = recv(fd, master.recv_buffer, 1024, 0))<= 0) {
                master.clients.erase(it++);
                close(fd);
                it = master.clients.erase(it);
                continue;
            }
    
            std::cout << "recv_buffer: " << master.recv_buffer << std::endl;
            std::cout << "Received " << master.recved << " bytes." << std::endl;
            master.sent = send(fd, master.recv_buffer, master.recved, 0);
            std::cout << "Sent " << master.sent << " bytes." << std::endl;
            close(fd);
            ++it;
            master.recved = 0;
            master.sent = 0;
        }
    }
}

int main (int ac, char **av)
{
    // if (!(ac == 2))
    //     return 1;
    s_master master;
    parse(av, master);
    startServ(master);
    
    //Create socket
    // int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // if (serverSocket == -1) {
    //     std::cerr << "Error creating socket" << std::endl;
    //     return 1;
    // }

    // fd_set readfds;
    // fd_set writefds;
    // std::set<int> clients;
    struct timeval timeout;


    // FD_SET(serverSocket, &readfds);
    //Create serverAddress
    // sockaddr_in serverAddress;
    // serverAddress.sin_family = AF_INET;
    // serverAddress.sin_port = htons(8080);
    // serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    //bind the socket to server
    // if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1){
    //         std::cerr << "Error binding socket" << std::endl;
    //         close(serverSocket);
    //         return 2;
    //     }

    //Listen
    // if (listen(serverSocket, 5) == -1) {
    //     std::cerr << "Error listening" << std::endl;
    //     close(serverSocket);
    //     return 3;
    // }
    // std::cout << "Server listening on port 8080" << std::endl;
    
    // sockaddr_in clientAddress;
    // socklen_t clientSize = sizeof(clientAddress);
    // int clientSocket;
    // char clientIP[INET_ADDRSTRLEN];
    // int clientPort;
    // int fd;
    // char recv_buffer[1024];
    // int recved;
    // int sent;
    // int nfds;
    
    while(true){
        FD_ZERO(&master.readfds); // We rubuild the whole set before select call.
        fdSetServer(master); // Adds server socket
        fdSetClient(master);
        getNfds(master);
        
        timeout.tv_sec = 10;
        select(master.nfds, &master.readfds, &master.writefds, NULL, &timeout);
        acceptRequests(master);
        receiveRequests(master);
    }
    closeServSocket(master);
    // close(serverSocket);

    return 0;
}
