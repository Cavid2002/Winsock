#include"MYNET.hpp"

#define BUFF_SIZE 2000
#define PATH_SIZE 100
#define ROUTE_COUNT 20


#define POST 80 
#define GET 71
#define DB "db.txt"


class HttpServer
{

private:

    unsigned short port;
    int ip_family;
    int t_protocol;    
    SOCKET l_sock;
    unsigned int q_size;    

public:
    
    HttpServer(int ip_family, int t_protocol, unsigned short port, unsigned int q_size);

    void read_request(SOCKET cln_sock, char* request, char* path);

    void make_response(SOCKET cln_sock, char* buff, char* path);

    int run();


};


class HttpRoute
{
public:
    static int r_count;
    static HttpRoute* arr[ROUTE_COUNT];


    const char* filename;
    const char* path;
    unsigned int method;
public:
    HttpRoute(const char* filename, const char* path, unsigned int method);

    static int find_route(char* path);

};