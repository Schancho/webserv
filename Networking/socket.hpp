#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

class Socket
{
private:
    int connection;
    struct sockaddr_in address;
    int sock;
public:
    Socket(int domain, int service, int protocol, int port, u_long interface);
    void connect_to_network(int sock, struct sockaddr_in address);
    void test_connection(int item_to_test);
    struct sockaddr_in get_address();
    int get_connection();
    int get_socket();
    ~Socket();
};



// 

#endif