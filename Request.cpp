#include "Request.hpp"

Request::Request()
{
    clientSize = sizeof(clientAddress);
    std::cout << "New Default Request created" << std::endl;
}

// Request::Request(int servSckt)
// {
//     servSocket = servSckt;
//     std::cout << "New Request created with server socket: " << servSocket << std::endl;
// }

Request::Request(Request const & src) 
    : clientAddress(src.clientAddress), clientSize(src.clientSize), clientSocket(src.clientSocket), clientPort(src.clientPort), servSocket(src.servSocket)
{
    for (size_t i = 0; i < INET_ADDRSTRLEN; i++)
    {
        clientIP[i] = src.clientIP[i];
    }
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
        for (size_t i = 0; i < INET_ADDRSTRLEN; i++)
        {
            clientIP[i] = rhs.clientIP[i];
        }
        clientPort = rhs.clientPort;
        servSocket = rhs.servSocket;
	}
	return(*this);
}

bool Request::operator<(const Request& other) const
{
    return(clientSocket < other.clientSocket);
}

Request::~Request()
{
    std::cout << "Request  destructor called." << std::endl;
}