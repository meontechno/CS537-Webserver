#include "ResponseGenerator.hpp"

Response *GetResponseGenerator::generateResponse(Request *request)
{
    return new Response();
}

Response *PostResponseGenerator::generateResponse(Request *request)
{
    return new Response();
}

Response *HeadResponseGenerator::generateResponse(Request *request)
{
    return new Response();
}

Response *DefaultResponseGenerator::generateResponse(Request *request)
{
    return new Response();
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
