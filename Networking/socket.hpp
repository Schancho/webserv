#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
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

class Parser
{
private:
    std::string target;
    std::string method;
    std::string version;
    std::string body;
    std::string header;
    std::string host;
    std::string port;
    std::string path;
    std::string content_length;
    std::string transfert_encoding;
    std::string requ;

    public:
    Parser(std::string request);
    std::map<std::string, std::string>_headers;
    std::string get_target();
    std::string get_method();
    std::string get_version();
    std::string get_body();
    std::string get_header();
    std::string get_host();
    std::string get_port();
    std::string get_path();
    std::string get_transfert_encoding();
    std::string get_content_length();
    std::string append_request(std::string request);
    
};



#endif