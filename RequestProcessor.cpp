#include "RequestProcessor.hpp"
#include "ResponseGenerator.hpp"
#include "Request.hpp"
#include "Response.hpp"

#include <cstdlib>
#include <cstring>
#include <unistd.h>

RequestProcessor::RequestProcessor()
{
    nextProcessor = NULL;
}

Response *RequestProcessor::process(Request  *request)
{
    Response *response = this->handleRequest(request);

    if(response->getStatus().code != BAD_REQUEST_CD
        && response->getStatus().code != NOT_FOUND_CD
        && nextProcessor != NULL)
    {
        return this->nextProcessor->process(request);
    }

    return response;
}

void RequestProcessor::setNextProcessor(RequestProcessor *nextProcessor)
{
    RequestProcessor::nextProcessor = nextProcessor;
}

inline bool isValuesExist(Request *request)
{
    bool requestTypeExist = request->getRequestType() == ERROR;
    bool pathExist = request->getPath().size() == 0;
    bool httpVersionExist = request->getHttp().size() == 0;

    if(requestTypeExist || pathExist || httpVersionExist)
        return false;

    return true;
}

inline bool isPathExist(const string& path)
{
    string basePath(getenv("PWD"));
    return (access( path.c_str(), F_OK ) != -1) && (path.compare(basePath + "/") != 0);
}

Response *ValidateRequestProcessor::handleRequest(Request *request)
{
    Response *response = new Response();

    if(!isValuesExist(request)) //|| request->getHttp() != VALID_HTTP)
    {
        response->setStatus(BADREQUEST);
    }
    else if(!isPathExist(request->getPath()))
    {
        response->setStatus(NOTFOUND);
    }

    return response;
}

Response *ProcessRequestProcessor::handleRequest(Request *request)
{
    ResponseGenerator *responseGenerator = getResponseGenerator(request->getRequestType());
    Response *response = responseGenerator->generateResponse(request);
    delete responseGenerator;
    return response;
}
