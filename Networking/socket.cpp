#include "socket.hpp"

Socket::Socket(int domain, int service, int protocol, int port, u_long interface)
{
    address.sin_family = domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(interface);
    sock = socket(domain, service, 0);
     memset(address.sin_zero, '\0', sizeof address.sin_zero);
    //connect_to_network(sock, address);
    // test_connection(sock);
    // test_connection(connection);
}

struct sockaddr_in Socket::get_address()
{
    return address;
}
int Socket::get_connection()
{
    return connection;
}
int Socket::get_socket()
{
    return sock;
}
void Socket::test_connection(int item_to_test)
{
    if (item_to_test < 0)
    {
        perror("Failed to connect...");
        exit(EXIT_FAILURE);
    }
}

// void Socket::connect_to_network(int sock, struct sockaddr_in address)
// {
//     if (bind(sock, (struct sockaddr *)&address, sizeof(address))<0)
//     {
//         perror("In bind");
//         exit(EXIT_FAILURE);
//     }
   
//}
Socket::~Socket()
{
    
}