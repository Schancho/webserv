#include "socket.hpp"
#include "responce.hpp"
#include <fcntl.h>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <poll.h>
#include <time.h>
#include <sys/time.h>

// std::string getContentTypeByFileName(std::string &fileName)
// {
//     std::map<std::string, std::string> map;

//     map.insert(std::pair<std::string, std::string>("html", "text/html"));
//     map.insert(std::pair<std::string, std::string>("css", "text/css"));
//     map.insert(std::pair<std::string, std::string>("js", "application/javascript"));
//     map.insert(std::pair<std::string, std::string>("jpg", "image/jpeg"));
//     map.insert(std::pair<std::string, std::string>("png", "image/png"));
//     map.insert(std::pair<std::string, std::string>("gif", "image/gif"));
//     map.insert(std::pair<std::string, std::string>("pdf", "application/pdf"));
//     map.insert(std::pair<std::string, std::string>("txt", "text/plain"));
//     map.insert(std::pair<std::string, std::string>("mp3", "audio/mpeg"));
//     map.insert(std::pair<std::string, std::string>("mp4", "video/mp4"));
//     return map.find(fileName.substr(fileName.find_last_of(".") + 1))->second;

// }
// std::string  responce(std::string target)
// {
//     std::string body;
//     std::string rt;
//     target = "/Users/schancho/Desktop/webserv/Networking" + target;
//     int ret = open(target.c_str(), O_RDONLY);
//     if (ret < 0)
//     {
//         rt = ("HTTP/1.1 404 Not found\nContent-Type: text/plain\nConnection: close\nContent-Length: 9\n\nnot found");
//         return rt;
//     }
//     rt = ("HTTP/1.1 200 OK\nContent-Type: " + getContentTypeByFileName(target) + "\nContent-Length: ");
//     int red;
//     char buff[4000];
//     int size = 0;
//     while ((red = read(ret, buff, 4000)) > 0)
//     {
//         body.append(buff, red);
//         size += red;
//     }
//     rt.append(std::to_string(size));
//     rt.append("\n\n");
//     rt.append(body.c_str(), body.size());
//     std::cerr << "========> contet " <<  std::to_string(size) << "   " << body.size() << std::endl;
//     return rt;
// }

int main()
{
    char *buff;
    struct pollfd fds[100];
    nfds_t nfds = 1;
    int i;
    int new_socket = -1, valread ;
    Socket sock(AF_INET, SOCK_STREAM, 0, 1338, INADDR_ANY); 
    char buffer[30000] = {0};
    struct sockaddr_in remote_address;
    socklen_t len =  sizeof(sockaddr_in);
    memset(fds, 0 , sizeof(fds));
    std::map<int , Parser *> map_request;
    std::map<int , Responce *> map_responce;

    fds[0].fd = sock.get_socket();
    fds[0].events = POLLIN;
    while (1)
    {
        int ret = poll(fds, nfds, -1);
        if (ret < 0)
        {
            perror("poll");
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < nfds; i++)
        {   
            if (fds[i].revents & POLLIN)
            {
                 if (fds[i].fd== sock.get_socket())
                {
                    new_socket = accept(fds[i].fd, (struct sockaddr *)&remote_address, &len);
                    fcntl(new_socket, F_SETFL, O_NONBLOCK);
                    if (new_socket < 0)
                    {
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }
                    fds[nfds].fd = new_socket;
                    fds[nfds].events = POLLIN;
                    nfds++;
                    continue; ;
                }
                
                valread = read(fds[i].fd, buffer, 3000);
        
                //printf("sdfsdfd    %s\n",buffer);
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
                Parser *parser;
                if (map_request.find(fds[i].fd) != map_request.end())
                {
                        //append
                      map_request.find(fds[i].fd)->second->append_request(request);
                        //parser.append(buffer );
                }
                else
                {
                    parser = new Parser(request);
                     map_request.insert(std::make_pair(fds[i].fd,parser));

                }
                //std::cout << "=========>" << parser->finshed << "=======" <<  parser->get_method() << "=======" << std::endl;
                if (parser->isError)
                {
                    std::cout << "ERror" << std::endl;
                     close(fds[i].fd);
                    fds[i].fd = -1;

                }
                if (parser->finshed ==  true)
                    fds[i].events = POLLOUT;
                continue;
            }
            else if (fds[i].revents & POLLOUT)
            {              

                Parser *parser = map_request.find(fds[i].fd)->second;
                Responce resp(sock);
            
                if (parser->get_target() == "/")
                    resp.set_responce("/index.html", parser->get_body());
                else
                    resp.set_responce(parser->get_target(), parser->get_body()) ;
                
                signal(SIGPIPE, SIG_IGN);
                int ret =   write(fds[i].fd , resp.get_responce().c_str() , resp.get_responce().size());
                map_request.erase(fds[i].fd);

                // if (ret == 0)
                // {
                close(fds[i].fd);
                fds[i].fd = -1;
                // }
            }   
        }
    }
    return 0;
}


