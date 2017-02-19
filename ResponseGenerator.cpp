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

ResponseGenerator *getResponseGenerator(RSP_GENERATOR generator)
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
