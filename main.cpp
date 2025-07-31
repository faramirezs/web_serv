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
#include <cerrno>

struct s_master 
{
    std::vector<Server> servVec;
    std::set<int> servPorts;
    fd_set readfds;
    fd_set writefds;
    std::set<int> clients;
    std::map<int, int> requestFds;
    std::map<Request, Server> reqServMap;
    std::map<int, Request> clientFdReqMap; 
    std::map<int, int> clientFdServFd;

    std::map<int, Server*> clientFdServ;
    std::map<Request, int> RequestClientFd;

    int nfds;
    char recv_buffer[1024];
    int recved;
    int sent;
    int select; 
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
        try {
            master.servVec.push_back(Server(*it));
        } catch (std::exception &e) {
            std::cerr << "Failed to create server on port " << *it << ": " << e.what() << std::endl;
        }
    }
    if (master.servVec.empty()) {
        std::cerr << "No servers could be started. Exiting." << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "Successfully created " << master.servVec.size() << " server(s)." << std::endl;
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

void fdSetClientR(s_master &master)
{
    for (std::set<int>::iterator it = master.clients.begin(); it != master.clients.end(); ++it) {
            FD_SET((*it), &master.readfds);
        }
}

void fdSetClientW(s_master &master)
{
    for (std::set<int>::iterator it = master.clients.begin(); it != master.clients.end(); ++it) {
            FD_SET((*it), &master.writefds);
        }
}

void getNfds(s_master &master)
{
    master.nfds = 0;
    for (std::vector<Server>::iterator it = master.servVec.begin(); it != master.servVec.end(); it++)
    {
        if((*it).serverSocket < 0) {
            std::cerr << "Negative fd detected." << std::endl;
            exit(EXIT_FAILURE);
        }

        if(master.nfds < (*it).serverSocket)
            master.nfds = (*it).serverSocket;
    }
    
    for (std::set<int>::iterator it = master.clients.begin(); it !=master.clients.end(); it++)
    {
        if((*it) < 0) {
            std::cerr << "Negative fd detected." << std::endl;
            exit(EXIT_FAILURE);
        }
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
            while (true) {
                Request *req = new Request;
                req->servSocket = (*it).serverSocket;;
                req->clientSize = sizeof(req->clientAddress);
                req->clientSocket = accept((*it).serverSocket, (sockaddr *)&req->clientAddress, &req->clientSize);

                if (req->clientSocket == -1) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        delete req;
                        std::cout << "No more pending connections." << std::endl;
                        break;
                    } else {
                        perror("accept() failed");
                        delete req;
                        break; 
                    }
                }
            
            std::cerr << "Client accepted with socket: " << req->clientSocket << std::endl;

            master.clients.insert(req->clientSocket);
            inet_ntop(AF_INET, &(req->clientAddress.sin_addr), req->clientIP, INET_ADDRSTRLEN);
            req->clientPort = ntohs(req->clientAddress.sin_port);
            // Probably we just need the map storing client fd and server.
            master.clientFdServ.insert(std::make_pair(req->clientSocket, &(*it)));

            master.RequestClientFd.insert(std::make_pair(Request(*req), req->clientSocket));
            master.clientFdReqMap.insert(std::make_pair(req->clientSocket, Request(*req)));

            std::cout << "Accepted connection from " << req->clientIP << ":" << req->clientPort
                    << std::endl;
            master.sent = send(req->clientSocket, master.clientFdServ[req->clientSocket]->serv_buffer, strlen(master.clientFdServ[req->clientSocket]->serv_buffer), 0);
            }
        }
    }
    
}

void receiveRequests(s_master &master) 
{
    int fd;
    if (master.clients.empty()) {
        std::cout << "No more clients connected." << std::endl;
    }
    for (std::set<int>::iterator it = master.clients.begin(); it != master.clients.end();) 
    {
        fd = *it;
        if(FD_ISSET(fd, &master.readfds)) {
            // recv is blocking
            std::string& buffer = master.clientFdReqMap[fd].req_buffer;
            buffer.clear();
            buffer.resize(1024);
            std::cout << "------>recv" << std::endl;
            if((master.recved = recv(fd, &buffer[0], 1024, 0))<= 0) {
                if (master.recved <= 0) {
                    std::cerr << "Client disconnected\n";
                    if(master.recved < 0)
                        perror("recv failed");
                    close(fd);
                    FD_CLR(fd, &master.readfds);
                    master.clients.erase(it++);
                    continue;
                } 
                else {
                    buffer.resize(master.recved);  // Keep only the received part
                    std::cout << "req_buffer: " << buffer << std::endl;
                    //std::cout << "req_buffer: " << master.clientFdReqMap[fd].req_buffer << std::endl;
                    std::cout << "Received " << master.recved << " bytes." << std::endl;
                }
            }
        }
        it++;
    }
}

void responRequests(s_master &master) 
{
    int fd;

    for (std::set<int>::iterator it = master.clients.begin(); it != master.clients.end();) 
    {
        fd = *it;

        if(FD_ISSET(fd, &master.readfds)) {
            const std::string& buffer = master.clientFdReqMap[fd].req_buffer;
            std::cout << "serv_buffer: " << buffer << std::endl;
            master.sent = send(fd, buffer.c_str(), buffer.size(), 0);
            
            if (master.sent <= 0) {
                std::cerr << "Message not sent.\n";
                if(master.sent < 0)
                    perror("sent failed"); 
                master.clients.erase(it++);
                close(fd);
                continue;
            }
            else
                std::cout << "Sent " << master.sent << " bytes." << std::endl;
        }
        it++;
    }
}

int main (int ac, char **av)
{
    if (ac == 1)
        return 1;
    s_master master;
    parse(av, master);
    startServ(master);
    
    struct timeval timeout;
    
    while(true){
        FD_ZERO(&master.readfds); // We rubuild the whole set before select call.
        //FD_ZERO(&master.writefds); 
        fdSetServer(master); // Adds server socket
        fdSetClientR(master); // Adds client socket read
        //fdSetClientW(master); // Adds client socket write
        getNfds(master);
        std::cerr << "getNfds: " << master.nfds << std::endl;

        timeout.tv_sec = 10;

        master.select = select(master.nfds, &master.readfds, NULL, NULL, &timeout);
        if (master.select < 0) {
            perror("select() failed");
            exit(1);
        }
        if (master.select == 0) 
            continue; // timeout, nothing to do.
        
        acceptRequests(master);
        receiveRequests(master);
        responRequests(master);
    }

    closeServSocket(master);

    return 0;
}
