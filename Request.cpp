#include "Request.hpp"
#include <cstring>
#include <string>

Request::Request(char *buffer)
{
    char *bufferLines = strtok(buffer, "\r\n");
    char *requestLine = strtok(bufferLines, " ");
    this->requestType = this->extractRequestType(requestLine);
    this->path = (requestLine + 1);
    this->http = (requestLine + 2);
    //do others after.
}

REQUESTTYPE Request::extractRequestType(char *methodLine)
{
    std::string method(methodLine);

    if(method.compare("GET"))
        return GET;
    else if(method.compare("POST"))
        return POST;
    else if(method.compare("HEAD"))
        return HEAD;

    return ERROR;
}

REQUESTTYPE Request::getRequestType()
{
    return Request::requestType;
}
