#ifndef RESPONCE_HPP
#define RESPONCE_HPP

#include "socket.hpp"
#include <fcntl.h>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <poll.h>
#include <time.h>
#include <sys/time.h>

class Responce
{
    private:
        Socket *socket;

        std::string responce;
        std::string status;
        std::string content_type;
        std::string content_length;
        std::string connection;
        std::string server;
        std::string date;
        std::string last_modified;
        std::string etag;
        std::string set_cookie;
        std::string x_frame_options;
        std::string vary;
        std::string transfer_encoding;
        std::string content_encoding;
        std::string access_control_allow_origin;

    public:
        Responce(Socket socket);
        void set_status(std::string status);
        void set_content_type(std::string content_type);
        void set_content_length(std::string content_length);
        void set_connection(std::string connection);
        void set_server(std::string server);
        void set_date(std::string date);
        void set_last_modified(std::string last_modified);
        void set_etag(std::string etag);
        void set_set_cookie(std::string set_cookie);
        void set_vary(std::string vary);
        void set_transfer_encoding(std::string transfer_encoding);
        void set_accept_encoding(std::string accept_encoding);
        void set_access_control_allow_origin(std::string access_control_allow_origin);
        void set_x_frame_options(std::string x_frame_options);
        void set_responce(std::string target, std::string body_request);//, std::string method, std::string version);//, std::string body);
        std::string get_responce();

};


#endif