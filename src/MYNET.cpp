#include"MYNET.hpp"



void error(const char* msg)
{
    fprintf(stderr, "[ERROR]%s!\n", msg);
    exit(EXIT_FAILURE);
}


SOCKET create_socket(int ip_family, int trs_protocol)
{
    SOCKET sock = socket(ip_family, trs_protocol, IPPROTO_TCP);
    if(sock == INVALID_SOCKET)
    {
        error("Unable to create socket");
    }

    return sock;
}

int bind_to_port(SOCKET sock, int ip_family, unsigned short port)
{
    sockaddr_in name;
    name.sin_family = ip_family;
    name.sin_port = htons(port);
    name.sin_addr.S_un.S_addr = INADDR_ANY;
    char opt = 1;

    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) == SOCKET_ERROR)
    {
        error("Unable to reuse port");
    }

    if(bind(sock, (sockaddr*)&name, sizeof(name)) == SOCKET_ERROR)
    {
        error("Unable to bind");
    }

    return 0;
}


int start_listing(SOCKET sock, int q_size)
{
    if(listen(sock, q_size) == SOCKET_ERROR)
    {
        error("Unable to listen");
    }

    return 0;
}


SOCKET accept_connection(SOCKET sock, sockaddr_in* client)
{
    int client_size = sizeof(sockaddr_in);
    int cln_sock = accept(sock, (sockaddr*)client, &client_size);
    if(cln_sock == SOCKET_ERROR)
    {
        error("Unable to accept");
    }

    return cln_sock;
}


int connect_to_addr(SOCKET sock, int ip_family, const char* ip_addr, unsigned short port)
{
    sockaddr_in name;
    name.sin_addr.S_un.S_addr = inet_addr(ip_addr);
    name.sin_port = htons(port);
    name.sin_family = ip_family;
    if(connect(sock, (sockaddr*)&name, sizeof(name)) == SOCKET_ERROR)
    {
        error("Unable to connect");
    }

    return 0;
}


