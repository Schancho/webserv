#include "responce.hpp"

Responce::Responce(Socket socket)
{
    this->socket = &socket;
}

void Responce::set_status(std::string status)
{
    this->status = status;
}

void Responce::set_content_type(std::string content_type)
{
    this->content_type = content_type;
}

void Responce::set_content_length(std::string content_length)
{
    this->content_length = content_length;
}

std::string getContentTypeByFileName(std::string &fileName)
{
    std::map<std::string, std::string> map;

    map["html"] = "text/html";
    map["css"] = "text/css";
    map["js"] = "application/javascript";
    map["jpg"] = "image/jpeg";
    map["jpeg"] = "image/jpeg";
    map["png"] = "image/png";
    map["gif"] = "image/gif";
    map["ico"] = "image/x-icon";
    map["txt"] = "text/plain";
    map["pdf"] = "application/pdf";
    map["mp3"] = "audio/mpeg";
    map["mp4"] = "video/mp4";
    map["wav"] = "audio/wav";
    map["ogg"] = "audio/ogg";
    map["mpg"] = "video/mpeg";
    map["mpeg"] = "video/mpeg";
    map["mov"] = "video/quicktime";
    map["swf"] = "application/x-shockwave-flash";
    map["zip"] = "application/zip";
    map["tar"] = "application/x-tar";
    map["gz"] = "application/x-gzip";
    map["rar"] = "application/x-rar-compressed";
    map["bz2"] = "application/x-bzip2";
    map["7z"] = "application/x-7z-compressed";
    map["doc"] = "application/msword";
    map["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    map["xls"] = "application/vnd.ms-excel";
    map["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    map["ppt"] = "application/vnd.ms-powerpoint";
    map["pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    map["odt"] = "application/vnd.oasis.opendocument.text";
    map["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
    map["odp"] = "application/vnd.oasis.opendocument.presentation";
    map["odg"] = "application/vnd.oasis.opendocument.graphics";
    map["odc"] = "application/vnd.oasis.opendocument.chart";
    map["odf"] = "application/vnd.oasis.opendocument.formula";
    map["odb"] = "application/vnd.oasis.opendocument.database";
    map["odi"] = "application/vnd.oasis.opendocument.image";
    map["oxt"] = "application/vnd.openofficeorg.extension";
    map["rtf"] = "application/rtf";
    map["xml"] = "text/xml";
    map["svg"] = "image/svg+xml";
    map["svgz"] = "image/svg+xml";
    map["ttf"] = "application/x-font-ttf";
    map["otf"] = "application/x-font-otf";
    map["woff"] = "application/font-woff";
    map["woff2"] = "application/font-woff2";
    map["eot"] = "application/vnd.ms-fontobject";
    map["sfnt"] = "application/font-sfnt";
    map["wasm"] = "application/wasm";
    map["json"] = "application/json";
    map["xml"] = "text/xml";
    map["mp4"] = "video/mp4";
    map["webm"] = "video/webm";
    map["ogv"] = "video/ogg";
    map["ogx"] = "application/ogg";
    map["ogg"] = "audio/ogg";
    map["oga"] = "audio/ogg";
    map["ogm"] = "video/ogg";
    map["ogx"] = "application/ogg";
    map["opus"] = "audio/ogg";
    map["flac"] = "audio/flac";
    map["flv"] = "video/x-flv";
    map["m4v"] = "video/x-m4v";
    map["m4a"] = "audio/x-m4a";
    map["m4b"] = "audio/x-m4b";
    map["m4p"] = "audio/x-m4p";
    map["m4r"] = "audio/x-m4r";
    map["m4v"] = "video/x-m4v";
    map["3gp"] = "video/3gpp";
    map["3g2"] = "video/3gpp2";
    map["3gpp"] = "video/3gpp";
    map["3gpp2"] = "video/3gpp2";
    map["3gp2"] = "video/3gpp2";
    
    return map.find(fileName.substr(fileName.find_last_of(".") + 1))->second;

}

void Responce::set_responce(std::string target, std::string body_request)//, std::string method, std::string version)//, std::string body)
{
    std::string body;
    target = "/Users/schancho/Desktop/webserv/Networking" + target;
    int ret = open(target.c_str(), O_RDONLY);
    if (ret < 0)
    {
        this->responce = ("HTTP/1.1 404 Not found\nContent-Type: text/plain\nConnection: close\nContent-Length: 9\n\nnot found");
        return ;
    }
    int red;
    char buff[4000];
    int size = 0;
    while ((red = read(ret, buff, 4000)) > 0)
    {
        body.append(buff, red);
        size += red;
    }
    this->status = "200 ok";
    this->content_type = getContentTypeByFileName(target);
    this->content_length = std::to_string(size);
    this->responce = "HTTP/1.1 " + status + "\r\n";
    this->responce += "Content-Type: " + content_type + "\r\n";
    this->responce += "Content-Length: " + content_length + "\r\n";
    this->responce += "Connection: " + connection + "\r\n";
    this->responce += "Server: " + server + "\r\n";
    this->responce += "Date: " + date + "\r\n";
    this->responce += "Last-Modified: " + last_modified + "\r\n";
    this->responce += "ETag: " + etag + "\r\n";
    this->responce += "Set-Cookie: " + set_cookie + "\r\n";
    this->responce += "Vary: " + vary + "\r\n";
    this->responce += "Transfer-Encoding: " + transfer_encoding + "\r\n";
    this->responce += "Content-Encoding: " + content_encoding + "\r\n";
    this->responce += "Access-Control-Allow-Origin: " + access_control_allow_origin + "\r\n";
    this->responce += "X-Frame-Options: " + x_frame_options + "\r\n";
    this->responce += "\r\n";
    this->responce.append(body.c_str(), body.size());
    std::cout << "========>" << body_request.size()  << std::endl;
     if(body_request.size() > 0)
    {
        std::ofstream file;
        std::cout << "====" << std::endl;
	    file.open("kkll.jpg");
        if (file.is_open())
            file << body_request;
    }

}

std::string Responce::get_responce()
{
    return responce;
}
