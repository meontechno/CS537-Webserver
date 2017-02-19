#ifndef REQUEST_HPP
#define REQUEST_HPP

enum REQUESTTYPE { GET, POST, HEAD };

class Request
{
    private:
        REQUESTTYPE requestType;
        char *path;
        char *http;

    public:
        Request(char *buffer);
        REQUESTTYPE getRequestType();
};

#endif // REQUEST_HPP
