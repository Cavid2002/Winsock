#include"src/MYNET.hpp"


int main(int argc , char *argv[])
{
    WSADATA wsa;
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		return 1;
	}
	
	SOCKET lsock = create_socket(AF_INET, SOCK_STREAM);

    bind_to_port(lsock, AF_INET, 3340);
    
    start_listing(lsock, 10);

    char* buff = (char*)malloc(1000);

    const char* msg = "HTTP/1.0 200 OK\r\n\r\nHello, World!";
    
    fprintf(stdout, "[INFO]Listing at port: 127.0.0.1:3340\n");

    while(1)
    {
        sockaddr_in client;
        SOCKET cl_sock = accept_connection(lsock, &client);
        
        int c = recv(cl_sock, buff, 1000, 0);

        buff[c] = '\0';

        fprintf(stdout ,"[INFO]Request data:\n%s", buff);

        send(cl_sock, msg, strlen(msg), 0);

        closesocket(cl_sock);

    }

	return 0;
}