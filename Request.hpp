#ifndef REQUEST_HPP
#define REQUEST_HPP


class Request
{
    private:
        char *action;
        char *path;
        char *http;

    public:
        Request(char *buffer);
};

#endif // REQUEST_HPP
