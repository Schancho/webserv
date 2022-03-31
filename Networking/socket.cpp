#include "socket.hpp"
#include <fcntl.h>
#include <vector>
#include <map>
#include <stdlib.h>

Socket::Socket(int domain, int service, int protocol, int port, u_long interface)
{
    address.sin_family = domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(interface);
    sock = socket(domain, service, 0);
     fcntl( sock, F_SETFL, O_NONBLOCK);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    if (bind(sock, (struct sockaddr *)&address, sizeof(address))<0) 
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

std::vector<std::string>split (std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;
    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}



std::vector<std::string> split_header (std::string s) {
    size_t pos_start = 0, pos;
    std::string token;
    std::vector<std::string> res;
    s.erase(s.size() - 1);

    if ((pos = s.find (":")) != std::string::npos) 
    {
        if (pos + 2 < s.size() && (s[pos+1] == '\t' || s[pos+1] == ' ') &&!(s[pos+2] == '\t' || s[pos+2] == ' '))
        {
            token = s.substr (0, pos);
            res.push_back (token);
            token = s.substr (pos+2,s.size() - pos);
            res.push_back (token);
        }
    }
    return res;
}

std::string receive_body(std::string line)
{
    int size;
    while (line != "0/r/n")
    {
        std::stringstream d(line);
        d >> std::hex >> size;
        
    }
}

Parser::Parser(std::string request)
{
    this->requ += request;
    std::string line;
    std::stringstream ss(request);
    std::getline(ss, line);
    std::stringstream ss2(line);
    std::getline(ss2, method, ' ');
    std::getline(ss2, target, ' ');
    std::getline(ss2, version, ' ');
    while (std::getline(ss, line))
    {
        if (line[0] == '\r')
        {
            std::getline(ss, line);
            break; 
        }
        std::vector<std::string> list = split_header(line);
        if (list.size() != 2)
            throw  std::exception();
        this->_headers.insert(std::make_pair(list[0], list[1]));
    }
    int size;
    std::stringstream d(line);
    d >> std::hex >> size;
    std::cout << "******" << size << "******" << std::endl;
    std::cout << "3333333 " << line << "333333" << std::endl;
    exit(1);
    // body += receive_body(line);
}


std::string Parser::append_request(std::string request)
{
    
    // this->requ += request;
    return this->requ ;
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