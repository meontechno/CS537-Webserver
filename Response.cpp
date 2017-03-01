#include "Response.hpp"
#include "Request.hpp"
#include <iostream>
#include <string>

using namespace std;

void Response::setStatus(STATUS status)
{
    Response::status = status;
}

STATUS Response::getStatus()
{
    return Response::status;
}

string Response::getStatusLine()
{
    return Response::statusLine = "HTTP/1.0 " + this->getStatus().code + " " + this->getStatus().msg + REQ_DELIMITER;
}

void Response::addToHeaderLine(string line)
{
    Response::headerLines.append(line);
}

void Response::setBody(string body)
{
    Response::body = body;
}

string Response::getBody()
{
    return Response::body;
}

string Response::getResponseString()
{
    string response = "";
    response.append(this->getStatusLine());

    if(!this->headerLines.empty()) {
        response.append(headerLines);
    }

    if(!this->getBody().empty()) {
        response.append(this->getBody());
    }

    return response;
}
