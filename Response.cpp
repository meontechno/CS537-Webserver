#include "Response.hpp"

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
    return Response::statusLine = "HTTP/1.0 " + this->getStatus().code + " " + this->getStatus().msg + "\r\n";
}

void Response::addToHeaderLine(string line)
{
    Response::headerLine.push(line);
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
   return getStatusLine();
}
