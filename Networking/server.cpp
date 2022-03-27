#include "socket.hpp"
#include <fcntl.h>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
std::string getContentTypeByFileName(std::string &fileName)
{
    std::map<std::string, std::string> map;

    map.insert(std::pair<std::string, std::string>("html", "text/html"));
    map.insert(std::pair<std::string, std::string>("css", "text/css"));
    map.insert(std::pair<std::string, std::string>("js", "application/javascript"));
    map.insert(std::pair<std::string, std::string>("jpg", "image/jpeg"));
    map.insert(std::pair<std::string, std::string>("png", "image/png"));
    map.insert(std::pair<std::string, std::string>("gif", "image/gif"));
    map.insert(std::pair<std::string, std::string>("pdf", "application/pdf"));
    map.insert(std::pair<std::string, std::string>("txt", "text/plain"));
    map.insert(std::pair<std::string, std::string>("mp3", "audio/mpeg"));
    map.insert(std::pair<std::string, std::string>("mp4", "video/mp4"));
    return map.find(fileName.substr(fileName.find_last_of(".") + 1))->second;

}
std::string  responce(std::string target)
{
    std::string body;
    std::string rt;
    // js css html jpg -> text/plane  extesnsin
    target = "/Users/schancho/Desktop/webserv/Networking" + target;
    int ret = open(target.c_str(), O_RDONLY);
    if (ret < 0)
    {
        rt = ("HTTP/1.1 404 Not found\nContent-Type: text/plain\nContent-Length: 10\n\nnot found");
        return rt;
    }
    rt = ("HTTP/1.1 200 OK\nContent-Type: " + getContentTypeByFileName(target) + "\nContent-Length: ");
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
    Socket sock(AF_INET, SOCK_STREAM, 0, 1337, INADDR_ANY);
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
        
   
        valread = read( new_socket , buffer, 1000000);
        
        printf("%s\n",buffer);
        std::string line;
        std::string from;
        from.append(buffer);
        std::string filename("rrr.txt");
        std::fstream file;
        file.open(filename, std::ios_base::app | std::ios_base::in);
        file << from << std::endl;
        file.close();
        file.open("rrr.txt");

        std::getline (file, line, '\n');
        file.close();
        remove("rrr.txt");
        std::cout << "+++++++++++++++++++++from:" <<line << std::endl;
        int pos;
        pos = line.find(" ");
        line = line.substr(pos + 1);
        int pos2;
        pos2 = line.find(" ");
        line = line.substr(0, pos2);
        std::cout << "+++++++++++++++++++++line:" << line <<std::endl;
        // std::string bf;
        // bf.append(buffer);
        // std::string line;
        // std::ofstream file;
        // std::getline(file, line);
        // file << buffer;
        // std::cout << responce("2.jpg").length÷() << srt
         std::string str;
        if (line == "/")
            str  =  responce("/index.html");
        else
            str  =  responce(line);
        std::cout << str.size() << std::endl;
        write(new_socket , str.c_str() , str.size());
        // write(new_socket, "defr",4);
        printf("%d...------------------Hello message sent-------------------\n",new_socket);
        close(new_socket);
    }
    return 0;
}