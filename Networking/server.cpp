#include "socket.hpp"
#include <fcntl.h>
#include <string>
#include <iostream>
#include <fstream>

std::string  responce(std::string target)
{
    std::string body;
    std::string rt;
    // js css html jpg -> text/plane  extesnsin
    int ret = open(target.c_str(), O_RDONLY);
    if (ret < 0)
    {
        rt = ("HTTP/1.1 404 Not found\nContent-Type: text/plain\nContent-Length: 9\n\nnot found");
        return rt;
    }
    rt.append("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ");
    int red;
    char buff[4000];
    int size = 0;
    while ((red = read(ret, buff, 4000)) > 0)
    {
        body.append(buff, red);
        size += red;
    }
    rt.append(std::to_string(size));
    rt.append("\n\n");
    rt.append(body.c_str(), body.size());
    return rt;
}

// parser

int main()
{
    char *buff;
    // "/Users/schancho/Desktop/webserv/Networking"

    int new_socket = -1, valread ;
    Socket sock(AF_INET, SOCK_STREAM, 0, 1338, INADDR_ANY);
    //char *hello= strdup("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 16\n\n");
    struct sockaddr_in address = sock.get_address();
    int addrlen = sizeof(address);
    if (bind(sock.get_socket(), (struct sockaddr *)&address, sizeof(address))<0) // already
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
        struct sockaddr_in remote_address;
    if (listen(sock.get_socket(), 1000) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }   
     char buffer[30000] = {0};
   socklen_t len =  sizeof(sockaddr_in);
    while(1)
    {
        
       printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(sock.get_socket(), (struct sockaddr *)&remote_address, &len  ))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        printf("%d -- main  = %d\n", new_socket, sock.get_socket());
        
   
        valread = read( new_socket , buffer, 30000);
        
        printf("%s\n",buffer);
        std::string line;
        std::string from;
        from.append(buffer);
        std::string filename("rrr.txt");
        std::fstream file;
        file.open(filename, std::ios_base::app | std::ios_base::in);
        file << from << std::endl;

        std::getline (file, line, '\n');
        std::cout << "+++++++++++++++++++++from:" <<line << std::endl;
        int pos;
        pos = line.find(" ");
        line = line.substr(pos + 1);
        int pos2;
        pos2 = line.find(" ");
        line = line.substr(0, pos2);
        std::cout << "+++++++++++++++++++++line:" << line << std::endl;
        // std::string bf;
        // bf.append(buffer);
        // std::string line;
        // std::ofstream file;
        // std::getline(file, line);
        // file << buffer;
        // std::cout << responce("2.jpg").length÷() << srt
        std::string str  =  responce("index.html");
        std::cout << str.size() << std::endl;
        write(new_socket , str.c_str() , str.size());
        // write(new_socket, "defr",4);
        printf("%d...------------------Hello message sent-------------------\n",new_socket);
        close(new_socket);
    }
    return 0;
}