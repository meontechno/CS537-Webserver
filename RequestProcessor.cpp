#include "RequestProcessor.hpp"
#include "ResponseGenerator.hpp"
#include "Response.hpp"

void RequestProcessor::setProcessor(RequestProcessor *processor)
{
    RequestProcessor::processor = processor;
}

Response *ValidateRequestProcessor::handleRequest(Request *request)
{
    return new Response();
}

Response *ProcessRequestProcessor::handleRequest(Request *request)
{
    ResponseGenerator responseGenerator = getResponseGenerator(request->getRequestType());
    return responseGenerator.generateResponse(request);
}

RequestProcessor *getProcessors()
{
    RequestProcessor *requestParser = new ValidateRequestProcessor();
    RequestProcessor *requestProcessor = new ProcessRequestProcessor();

    requestParser->setProcessor(requestProcessor);

    return requestParser;
}

