#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <set>
#include <vector>
#include <map>
#include "Server.hpp"
#include "Request.hpp"
#include <cstdio>

struct s_master 
{
    std::vector<Server> servVec;
    std::set<int> servPorts;
    fd_set readfds;
    fd_set writefds;
    std::set<int> clients;
    std::map<int, int> requestFds;
    std::map<Request, Server> reqServMap;
    std::map<int, Request> fdReqMap; 
    std::map<int, int> clientFdServFd;

    std::map<int, Server> clientFdServ;
    std::map<Request, int> RequestClientFd;

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
            // Make pair
            //master.reqServMap.insert(std::make_pair(Request(), (*it)));
            req->servSocket = (*it).serverSocket;
            req->clientSocket = accept((*it).serverSocket, (sockaddr *)&req->clientAddress, &req->clientSize);
            if (req->clientSocket == -1) {
                std::cerr << "Error accepting request" << std::endl;
                delete req;
            }
            std::cerr << "Client accepted with socket: " << req->clientSocket << std::endl;

            master.clients.insert(req->clientSocket);
            inet_ntop(AF_INET, &(req->clientAddress.sin_addr), req->clientIP, INET_ADDRSTRLEN);
            req->clientPort = ntohs(req->clientAddress.sin_port);
            // Probably we just need the map storing client fd and server.
            master.clientFdServ.insert(std::make_pair(req->clientSocket, (*it)));
            master.RequestClientFd.insert(std::make_pair(Request(*req), req->clientSocket));
            
            std::cout << "Accepted connection from " << req->clientIP << ":" << req->clientPort
                    << std::endl;
            //send(req->clientSocket, "Hola from serv\n", 14, 0);
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
                if (master.recved == 0) {
                    std::cerr << "Client disconnected gracefully\n";
                } else {
                    perror("recv failed");
                }
                master.clients.erase(it++);
                close(fd);
                continue;
            }
    
            std::cout << "recv_buffer: " << master.recv_buffer << std::endl;
            std::cout << "Received " << master.recved << " bytes." << std::endl;
            master.sent = send(fd, master.recv_buffer, master.recved, 0);
            std::cout << "Sent " << master.sent << " bytes." << std::endl;
            //close(fd);
            //it++;
            //master.recved = 0;
            //master.sent = 0;
        }
        it++;
    }
}

int main (int ac, char **av)
{
    if ((ac == 1))
        return 1;
    s_master master;
    parse(av, master);
    startServ(master);
    
    struct timeval timeout;
    
    while(true){
        FD_ZERO(&master.readfds); // We rubuild the whole set before select call.
        fdSetServer(master); // Adds server socket
        fdSetClient(master); // Ads client socket
        getNfds(master);
        std::cerr << "getNfds: " << master.nfds << std::endl;

        timeout.tv_sec = 10;
        select(master.nfds, &master.readfds, &master.writefds, NULL, &timeout);
        acceptRequests(master);
        receiveRequests(master);
    }

    closeServSocket(master);

    return 0;
}
