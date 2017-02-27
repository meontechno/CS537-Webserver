#include "ResponseGenerator.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Response *GetResponseGenerator::generateResponse(Request *request)
{
    Response *response = new Response();
    ifstream fileToRead (request->getPath().c_str());
    string dataInFile;
    if(fileToRead.is_open())
    {
        while(getline(fileToRead, dataInFile))
        {
            response->setBody(response->getBody() + dataInFile);
        }
        fileToRead.close();
        response->setStatus(OK);
        return response;
    }

    response->setStatus(INTERNALERROR);
    return response;
}

Response *PostResponseGenerator::generateResponse(Request *request)
{
    Response *response = new Response();

    if(!request->getBody().empty())
    {
        ofstream fileToWrite (request->getPath().c_str(), ios::out | ios::trunc);
        if(fileToWrite.is_open())
        {
            fileToWrite << request->getBody().c_str();
            fileToWrite.close();
            response->setStatus(OK);
            return response;
        }
    }

    response->setStatus(INTERNALERROR);
    return response;
}

Response *HeadResponseGenerator::generateResponse(Request *request)
{
    return new Response();
}

Response *DefaultResponseGenerator::generateResponse(Request *request)
{
    Response *response = new Response();
    response->setStatus(NOTIMPLEMENTED);
    return response;
}

ResponseGenerator getResponseGenerator(REQUESTTYPE generator)
{
    switch(generator)
    {
        case GET:
            return GetResponseGenerator();
            break;
        case POST:
            return PostResponseGenerator();
            break;
        case HEAD:
            return HeadResponseGenerator();
            break;
        default:
            return DefaultResponseGenerator();
            break;
    }
}
