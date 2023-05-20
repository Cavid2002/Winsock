#include"HttpServer.hpp"

HttpServer::HttpServer(int ip_family, int t_protocol, unsigned short port,unsigned int q_size)
{
    this->ip_family = ip_family;
    this->t_protocol = t_protocol;
    this->port = port;       
    this->q_size = q_size;
}


void HttpServer::read_request(SOCKET cln_sock,char* request, char* path)
{
    memset(request, 0, BUFF_SIZE);
    memset(path, 0, PATH_SIZE);
    
    
    int c = recv(cln_sock, request, BUFF_SIZE, 0);

    request[c] = '\0';

    char* ptr1 = strchr(request, '/');
    char* ptr2 = strchr(ptr1, ' ');
    *ptr2 = '\0';
    strcpy(path, ptr1);    
    *ptr2 = ' ';
    
    if(request[0] == POST)
    {
        FILE* db = fopen(DB, "a");
        ptr1 = strstr(request, "\r\n\r\n");
        fputs(ptr1+4, db);
        fclose(db);
    }


        
    fprintf(stdout, "[INFO]Request path:%s\n", path);    
    fprintf(stdout, "[INFO]Request data:\n%s", request);
       
}

void HttpServer::make_response(SOCKET cln_sock, char* buff,char* path)
{
    char temp[50];
    memset(temp, 0, 50);
    memset(buff, 0, BUFF_SIZE);

    char* ptr = strchr(path, '.');
    
    if(ptr != NULL)
    {
        sprintf(temp, "templates%s", path);
        FILE* frontend = fopen(temp, "rb");
        if(frontend == NULL)
        {
            fprintf(stderr ,"File doesn't exists!");
        }

        strcpy(buff, "HTTP/2.0 200 OK\r\n\r\n");
        send(cln_sock, buff, strlen(buff), 0);
        int c = 10;
        while(c > 0)
        {
            c = fread(buff, 1, BUFF_SIZE, frontend);
            send(cln_sock, buff, c, 0);
        }

        fclose(frontend);
    }
    else
    {
        int index = HttpRoute::find_route(path);
        if(index == -1) return;
        
        sprintf(temp, "templates/%s", HttpRoute::arr[index]->filename);
        FILE* frontend = fopen(temp, "r");

        if(frontend == NULL)
        {
            error("File doesn't exists");
        }

        strcpy(buff, "HTTP/2.0 200 OK\r\n\r\n");
        send(cln_sock, buff, strlen(buff), 0);

        while(fgets(buff, BUFF_SIZE, frontend) != NULL)
        {
            send(cln_sock, buff, strlen(buff), 0);
        }

        fclose(frontend);
    }
}

int HttpServer::run()
{
    this->l_sock = create_socket(this->ip_family, this->t_protocol);

    bind_to_port(this->l_sock, this->ip_family, this->port);

    start_listing(this->l_sock, this->q_size);

    char* buff = (char*)malloc(BUFF_SIZE);
    char* path = (char*)malloc(PATH_SIZE);

    fprintf(stdout, "[INFO]Listing at port: 3340");

    while(true)
    {
        sockaddr_in cln_addr;
        SOCKET cln_sock = accept_connection(this->l_sock, &cln_addr);

        read_request(cln_sock, buff, path);

        if(strcmp(path, "/favicon.ico") == 0)
        {
            continue;
        }

        make_response(cln_sock, buff, path);

        closesocket(cln_sock);

    }

    return 0;
}


int HttpRoute::r_count = 0;
HttpRoute* HttpRoute::arr[ROUTE_COUNT];

HttpRoute::HttpRoute(const char* filename, const char* path, unsigned int method)
{
    this->filename = filename;
    this->method = method;
    this->path = path;
    
    arr[r_count] = this;
    r_count++;
}


int HttpRoute::find_route(char* path)
{
    for(int i = 0; i < r_count; i++)
    {
        if(strcmp(path, arr[i]->path) == 0)
        {
            return i;
        }
    }

    return -1;
}