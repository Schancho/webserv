#include "socket.hpp"
#include <fcntl.h>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <poll.h>
#include <time.h>
#include <sys/time.h>

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
    target = "/Users/schancho/Desktop/webserv/Networking" + target;
    int ret = open(target.c_str(), O_RDONLY);
    if (ret < 0)
    {
        rt = ("HTTP/1.1 404 Not found\nContent-Type: text/plain\nConnection: close\nContent-Length: 9\n\nnot found");
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
    std::cerr << "========> contet " <<  std::to_string(size) << "   " << body.size() << std::endl;
    return rt;
}

int main()
{
    char *buff;
    struct pollfd fds[100];
    nfds_t nfds = 1;
    int i;
    int new_socket = -1, valread ;
    Socket sock(AF_INET, SOCK_STREAM, 0, 1337, INADDR_ANY); 
    char buffer[30000] = {0};
    struct sockaddr_in remote_address;
    socklen_t len =  sizeof(sockaddr_in);
    memset(fds, 0 , sizeof(fds));

    fds[0].fd = sock.get_socket();
    fds[0].events = POLLIN;
    while (1)
    {
        int ret = poll(fds, nfds, -1);
        if (ret < 0)
        {
            perror("poll");
            exit(1);
        }
  
        for (i = 0; i < nfds; i++)
        {   
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
            if (fds[i].revents & POLLIN)
            {
                std::cout << "==================================" << std::endl;
                 if (fds[i].fd== sock.get_socket())
                {
                    new_socket = accept(fds[i].fd, (struct sockaddr *)&remote_address, &len);
                  fcntl(new_socket, F_SETFL, O_NONBLOCK);
                    if (new_socket < 0)
                    {
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }
                    printf("\n+++++++ New connection accepted ++++++++\n\n");
                    fds[nfds].fd = new_socket;
                    fds[nfds].events = POLLIN;
                    nfds++;
                    continue; ;
                }

                valread = read(fds[i].fd, buffer, 3000);
                    
                printf("%s\n",buffer);
                if (valread < 0)
                {
                    close(fds[i].fd);
                    fds[i].fd = -1;
                    continue;
                }
                if (valread == 0)
                {             
                    close(fds[i].fd);
                    fds[i].fd = -1;
                    continue;
                }
                std::string request(buffer);
                std::string str;
                Parser parser(request);
                if (parser.get_target() == "/")
                    str  =  responce("/index.html");
                else
                    str = responce(parser.get_target());
                //std::cout<<parser.get_target()<<std::endl;
                //std::cout << str << std::endl;
                int ret =   write(fds[i].fd , str.c_str() , str.size());
                if (ret == 0)
                {
                close(fds[i].fd);
                fds[i].fd = -1;
                }
                printf("------------------Hello message sent-------------------\n");
            }
   
        }
    }
    return 0;
}