#include "Request.hpp"

Request::Request()
{
    std::cout << "New Default Request created" << std::endl;
}

Request::Request(int servSckt)
{
    servSocket = servSckt;
    std::cout << "New Request created with server socket: " << servSocket << std::endl;
}

Request::Request(Request const & src) 
    : clientAddress(src.clientAddress), clientSize(src.clientSize), clientSocket(src.clientSocket), clientIP(src.clientIP), clientPort(src.clientPort), servSocket(src.servSocket)
{
	std::cout << "Request copy constructor called." << std::endl;
}

Request& Request::operator=(Request const & rhs)
{
	std::cout << "Request assignment constructor called." << std::endl;
	if(this != &rhs)
	{
		clientAddress = rhs.clientAddress;
        clientSize = rhs.clientSize;
        clientSocket = rhs.clientSocket;
        clientIP = rhs.clientIP; 
        clientPort = rhs.clientPort;
        servSocket = rhs.servSocket;
	}
	return(*this);
}

Request::~Request()
{
    std::cout << "Request  destructor called." << std::endl;
}