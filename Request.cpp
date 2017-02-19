#include "Request.hpp"

Request::Request(char *buffer)
{
    //ctor
}

REQUESTTYPE Request::getRequestType()
{
    return Request::requestType;
}
