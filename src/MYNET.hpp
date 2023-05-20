#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#include<winsock2.h>
#include<windows.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

void error(const char* msg);

SOCKET create_socket(int ip_family, int trs_protocol);

int bind_to_port(SOCKET sock, int ip_family, unsigned short port);

int start_listing(SOCKET sock, int q_size);

SOCKET accept_connection(SOCKET sock, sockaddr_in* client);

int connect_to_addr(SOCKET sock, int ip_family, const char* ip_addr, unsigned short port);