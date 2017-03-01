#include "ResponseGenerator.hpp"
#include "Request.hpp"

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Response *GetResponseGenerator::generateResponse(Request *request)
{
    Response *response = new Response();
    long fileSize;
    ifstream fileToRead (request->getPath().c_str());
    if(fileToRead.is_open())
    {
        /* Get file data */
        fileToRead.seekg(0, ios::end);
        fileSize = fileToRead.tellg();
        char *fileDataBuff = new char[fileSize];
        fileToRead.seekg(0, ios::beg);
        fileToRead.read(fileDataBuff, fileSize);
        fileToRead.close();
        response->setBody(string(fileDataBuff));
        delete fileDataBuff;

        cout << "Response File Size: " << fileSize << endl;

        /* Set values for response header lines */
        time_t currentTime = time(0);
        stringstream timeStream;
        timeStream << ctime(&currentTime);
        string time = timeStream.str();
        size_t pos = time.find("\n");
        if(pos != string::npos) {
            time.erase(pos, time.size());
        }

        stringstream bodySizeStream;
        bodySizeStream << fileSize;

        /* Sent response header lines */
        response->setStatus(OK);
        response->addToHeaderLine("Date: " + time + REQ_DELIMITER);
        response->addToHeaderLine("Server: Customized" + REQ_DELIMITER);
        response->addToHeaderLine("Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT" + REQ_DELIMITER);
        response->addToHeaderLine("Content-Length: " + bodySizeStream.str() + REQ_DELIMITER);
        response->addToHeaderLine("Content-Type: text/html; charset=iso-8859-1" + REQ_DELIMITER);
        response->addToHeaderLine("Connection: Closed" + REQ_DELIMITER);
        response->addToHeaderLine(REQ_DELIMITER);

        /* Clear stringstreams */
        timeStream.str(string());
        timeStream.clear();

        bodySizeStream.str(string());
        bodySizeStream.clear();

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

ResponseGenerator *getResponseGenerator(REQUESTTYPE generator)
{
    switch(generator)
    {
        case GET:
            return new GetResponseGenerator();
            break;
        case POST:
            return new PostResponseGenerator();
            break;
        case HEAD:
            return new HeadResponseGenerator();
            break;
        default:
            return new DefaultResponseGenerator();
            break;
    }
}
