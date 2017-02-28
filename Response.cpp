#include "Response.hpp"
#include "Request.hpp"
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
    return Response::statusLine = "HTTP/1.1 " + this->getStatus().code + " " + this->getStatus().msg + REQ_DELIMITER;
}

void Response::addToHeaderLine(string line)
{
    Response::headerLine.push(line);
}

void Response::setBody(char *body)
{
    Response::body = body;
}

char *Response::getBody()
{
    return Response::body;
}

string Response::getResponseString()
{
    string response = "";
    response += this->getStatusLine();

    while(!this->headerLine.empty())
    {
        response += headerLine.front();
        headerLine.pop();
    }

    /*if(!this->getBody().empty())
    {
        response += this->getBody();
    }*/

    return response;
}
