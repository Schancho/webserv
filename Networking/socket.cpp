#include "socket.hpp"
#include <fcntl.h>

Socket::Socket(int domain, int service, int protocol, int port, u_long interface)
{
    address.sin_family = domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(interface);
    sock = socket(domain, service, 0);
     fcntl( sock, F_SETFL, O_NONBLOCK);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    if (bind(sock, (struct sockaddr *)&address, sizeof(address))<0) // already
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
        struct sockaddr_in remote_address;
    if (listen(sock, 1000) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    } 
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

Parser::Parser(std::string request)
{
    std::string line;
    std::stringstream ss(request);

    std::getline(ss, line);
    std::stringstream ss2(line);
    std::getline(ss2, method, ' ');
    std::getline(ss2, target, ' ');
    std::getline(ss2, version, ' ');
    std::getline(ss, line);
    std::stringstream ss3(line);
    std::getline(ss3, header, '\r');
    std::getline(ss3, body, '\r');
    std::stringstream ss4(header);
    std::getline(ss4, line, ':');
    std::getline(ss4, line, ' ');
    std::getline(ss4, host, ':');
    std::getline(ss4, port, ' ');
    std::getline(ss4, path, ' ');
}

std::string Parser::get_target()
{
    return target;
}   
std::string Parser::get_method()
{
    return method;
}
std::string Parser::get_version()
{
    return version;
}
std::string Parser::get_body()
{
    return body;
}
std::string Parser::get_header()
{
    return header;
}
std::string Parser::get_host()
{
    return host;
}
std::string Parser::get_port()
{
    return port;
}
std::string Parser::get_path()
{
    return path;
}

Socket::~Socket()
{
    
}