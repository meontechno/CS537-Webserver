#ifndef RESPONSEGENERATOR_HPP
#define RESPONSEGENERATOR_HPP

#include "Request.hpp"
#include "Response.hpp"

enum RSP_GENERATOR { GET, POST, HEAD };

class ResponseGenerator
{
    public:
        Response generateResponse(Request *request);
};

class GetResponseGenerator : public ResponseGenerator
{
    public:
        Response *generateResponse(Request *request);
};

class PostResponseGenerator : public ResponseGenerator
{
    public:
        Response *generateResponse(Request *request);
};

class HeadResponseGenerator : public ResponseGenerator
{
    public:
        Response *generateResponse(Request *request);
};

class DefaultResponseGenerator : public ResponseGenerator
{
    public:
        Response *generateResponse(Request *request);
};

ResponseGenerator *getResponseGenerator(RSP_GENERATOR generator);

#endif // RESPONSEGENERATOR_HPP
