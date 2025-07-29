#include "Server.hpp"

Server::Server(int port)
{
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
    }
    std::cout << "New Server created at port: " << port << std::endl;
}

Server::Server(Server const & src) 
    : serverAddress(src.serverAddress), serverSocket(src.serverSocket)
{
	std::cout << "Server copy constructor called." << std::endl;
}

Server& Server::operator=(Server const & rhs)
{
	std::cout << "Server assignment constructor called." << std::endl;
	if(this != &rhs)
	{
		serverAddress = rhs.serverAddress;
        serverSocket = rhs.serverSocket;
	}
	return(*this);
}

Server::~Server()
{
    std::cout << "Server  destructor called." << std::endl;
}