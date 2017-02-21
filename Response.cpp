#include "Response.hpp"

void Response::setStatusLine(STATUS status)
{
    Response::statusLine = "HTTP/1.0 " + status.code + status.msg + "\r\n";
}

void Response::addToHeaderLine(string line)
{
    Response::headerLine.push(line);
}

void Response::setBody(string body)
{
    Response::body = body;
}
