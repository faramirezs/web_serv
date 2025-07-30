#include "Server.hpp"

Server::Server()
{
    std::cout << "Server default constructor called" << std::endl;
}

Server::Server(int port)
{
    snprintf(serv_buffer, sizeof(serv_buffer), "Hello from server on port %d", port);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
    }

    // Bind the socket to server
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1){
        std::cerr << "Error binding socket" << std::endl;
        close(serverSocket);
    }
        
    // Listen
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening" << std::endl;
        close(serverSocket);
    }
    std::cout << "Server listening on port: " << port << std::endl;
}

Server::Server(Server const & src) 
    : serverAddress(src.serverAddress), serverSocket(src.serverSocket)
{
	std::cout << "Server copy constructor called." << std::endl;
    std::memcpy(serv_buffer, src.serv_buffer, sizeof(serv_buffer));
}

Server& Server::operator=(Server const & rhs)
{
	std::cout << "Server assignment constructor called." << std::endl;
	if(this != &rhs)
	{
		serverAddress = rhs.serverAddress;
        serverSocket = rhs.serverSocket;
        std::memcpy(serv_buffer, rhs.serv_buffer, sizeof(serv_buffer));
	}
	return(*this);
}

Server::~Server()
{
    std::cout << "Server  destructor called." << std::endl;
}