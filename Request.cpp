#include "Request.hpp"
#include <string>
#include <queue>
#include <iostream>

using namespace std;

Request::Request(char *buffer)
{
    queue<string> requestLines;
    string requestStream(buffer);
    size_t pos = 0;
    string requestSubStr;

    /* Create a queue of each line of the request based on the delimited (\r\n) */
    while((pos = requestStream.find(REQ_DELIMITER)) != string::npos)
    {
        requestSubStr = requestStream.substr(0, pos);
        requestLines.push(requestSubStr);
        requestStream.erase(0, pos + REQ_DELIMITER.length());
    }

    if(requestLines.size() == 0)
        return;

    requestStream.clear();

    string requestLine = requestLines.front();
    requestLines.pop();

    /* Extract the request type within the first line, which is the request line of the HTTP protocol */
    /* The first string seperated by a space is expected to be the request type. */
    pos = requestLine.find(REQ_LINE_DELIMITER);

    if(pos == string::npos) {
        return;
    }

    requestSubStr = requestLine.substr(0, pos);
    this->requestType = this->extractRequestType(requestSubStr);
    requestLine.erase(0, pos + REQ_LINE_DELIMITER.length());

    cout << "Request Type: " << requestSubStr << " enum: " << this->requestType << endl;

    /* Extract the requested path that is expected to be the second string within the request line. */
    pos = requestLine.find(REQ_LINE_DELIMITER);

    if(pos == string::npos) {
        return;
    }

    requestSubStr = requestLine.substr(0, pos);
    this->path = requestSubStr;
    requestLine.erase(0, pos + REQ_LINE_DELIMITER.length());

    cout << "Path Type: " << requestSubStr << " value set: " << this->path << endl;

     /* Extract the http version that is expected to be the third (remaining) string within the request line. */
    this->http = requestLine;
    requestLine.clear();

    cout << "Http Type: " << requestSubStr << " value set: " << this->http << endl;

    /* Extract headers */
    for(int count = 0; count < requestLines.size(); count++)
    {
        requestLine = requestLines.front();
        requestLines.pop();
        // headers end after a line with only \r\n
        if(requestLine == " ")
            break;

        cout << "Header" << count << ": " << requestLine << endl;
    }

    /* Extract body if exist */
    string requestBody = "";
    for(int count = 0; count < requestLines.size(); count++)
    {
        requestBody += requestLines.front();
        requestLines.pop();
    }
    this->body = requestBody;

    cout << "Body: " << this->body << endl;
}

REQUESTTYPE Request::extractRequestType(string method)
{
    if(method.compare("GET") == 0)
        return GET;
    else if(method.compare("POST") == 0)
        return POST;
    else if(method.compare("HEAD") == 0)
        return HEAD;

    return ERROR;
}

REQUESTTYPE Request::getRequestType()
{
    return Request::requestType;
}

string Request::getPath()
{
    return Request::path;
}

string Request::getHttp()
{
    return Request::http;
}

vector<string> Request::getHeaders()
{
    return Request::headers;
}

string Request::getBody()
{
    return Request::body;
}
