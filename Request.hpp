#ifndef REQUEST_HPP
#define REQUEST_HPP

enum REQUESTTYPE { GET, POST, HEAD, ERROR };

class Request
{
    private:
        REQUESTTYPE requestType;
        char *path;
        char *http;
        REQUESTTYPE extractRequestType(char *methodLine);

    public:
        Request(char *buffer);
        REQUESTTYPE getRequestType();
};

#endif // REQUEST_HPP
