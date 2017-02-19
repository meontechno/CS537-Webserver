#ifndef RESPONSE_HPP
#define RESPONSE_HPP

enum STATUS { OK=200, MOVEDPERM=301, BADREQUEST=400, NOTFOUND=404, VERNOTSUPPORTED=505 };

class Response
{
    public:
        Response();
};

#endif // RESPONSE_HPP
