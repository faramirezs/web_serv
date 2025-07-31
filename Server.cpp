#include "Server.hpp"

Server::Server()
{
    std::cout << "Server default constructor called" << std::endl;
}

Server::Server(int port)
{
    snprintf(serv_buffer, sizeof(serv_buffer), "Hello from server on port %d.\n", port);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw std::runtime_error("Error creating socket");
    }

    fcntl(serverSocket, F_SETFL, O_NONBLOCK);

    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        close(serverSocket);
        throw std::runtime_error("Error binding socket");
    }

    if (listen(serverSocket, 5) == -1) {
        close(serverSocket);
        throw std::runtime_error("Error listening on socket");
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