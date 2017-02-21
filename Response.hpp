#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include <stack>

using namespace std;

struct STATUS
{
    string code;
    string msg;
};

static STATUS OK = { "200", "OK" };
static STATUS MOVEDPERM = { "301", "Moved Permanently" };
static STATUS BADREQUEST = { "400", "Bad Request" };
static STATUS NOTFOUND = { "404", "Not Found" };
static STATUS VERNOTSUPPORTED = { "505", "HTTP Version Not Supported" };

class Response
{
    private:
        string statusLine;
        stack<string> headerLine;
        string body;
    public:
        void setStatusLine(STATUS status);
        void addToHeaderLine(string line);
        void setBody(string body);
};

#endif // RESPONSE_HPP
