#include "RequestProcessor.hpp"
#include "ResponseGenerator.hpp"
#include "Request.hpp"
#include "Response.hpp"

#include <unistd.h>

Response *RequestProcessor::process(Request  *request)
{
    Response *response = this->handleRequest(request);

    if(response->getStatus().code != BAD_REQUEST_CD
        && response->getStatus().code != NOT_FOUND_CD
        && nextProcessor)
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
    if(request->getRequestType() == ERROR ||
        request->getPath().size() == 0 ||
        request->getHttp().size() == 0)
        return false;

    return true;
}

inline bool isPathExist(const string& path)
{
    return (access( path.c_str(), F_OK ) != -1);
}

Response *ValidateRequestProcessor::handleRequest(Request *request)
{
    Response *response = new Response();

    if(!isValuesExist(request) || request->getHttp() != VALID_HTTP)
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
    ResponseGenerator responseGenerator = getResponseGenerator(request->getRequestType());
    return responseGenerator.generateResponse(request);
}

RequestProcessor *getProcessors()
{
    RequestProcessor *validateRequest = new ValidateRequestProcessor();
    RequestProcessor *processRequest = new ProcessRequestProcessor();

    validateRequest->setNextProcessor(processRequest);

    return validateRequest;
}

