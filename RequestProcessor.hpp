#ifndef REQUESTPROCESSOR_HPP
#define REQUESTPROCESSOR_HPP

#include "Request.hpp"
#include "Response.hpp"

class RequestProcessor
{
    private:
        RequestProcessor *processor;

    public:
        virtual Response *handleRequest(Request *request) {};
        void setProcessor(RequestProcessor *processor);
};

class ValidateRequestProcessor : public RequestProcessor
{
    public:
        Response *handleRequest(Request *request);
};

class ProcessRequestProcessor : public RequestProcessor
{
    public:
        Response *handleRequest(Request *request);
};

RequestProcessor *getProcessors();

#endif // REQUESTPROCESSOR_HPP
