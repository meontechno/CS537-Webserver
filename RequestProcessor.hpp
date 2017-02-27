#ifndef REQUESTPROCESSOR_HPP
#define REQUESTPROCESSOR_HPP

#include "Request.hpp"
#include "Response.hpp"

const string VALID_HTTP = "HTTP/1.0";

class RequestProcessor
{
    private:
        RequestProcessor *nextProcessor;

    protected:
        virtual Response *handleRequest(Request *request) {};

    public:
        Response *process(Request  *request);
        void setNextProcessor(RequestProcessor *nextProcessor);
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
