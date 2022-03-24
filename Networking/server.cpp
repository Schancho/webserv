#include "socket.hpp"
# include <fcntl.h>
#include <string>

// std::string  respnce(std::string targe)
// {
//     // open()
// }

int main()
{
    int new_socket = -1, valread ;
    Socket sock(AF_INET, SOCK_STREAM, 0, 1339, INADDR_ANY);
    char *hello= strdup("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 10\n\nHello world!");
    struct sockaddr_in address = sock.get_address();
    int addrlen = sizeof(address);
    if (bind(sock.get_socket(), (struct sockaddr *)&address, sizeof(address))<0)
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
        
        printf("%s\n",buffer );
        write(new_socket , hello , strlen(hello));
        printf("%d...------------------Hello message sent-------------------\n",new_socket);
        close(new_socket);
    }
    return 0;
}