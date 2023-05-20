#include"src/HttpServer.hpp"


int main()
{

    WSADATA wsa;
	
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		return 1;
	}


    HttpServer server(AF_INET, SOCK_STREAM, 3340, 10);


    HttpRoute rt("routes.html", "/", GET);
    HttpRoute rt1("index.html", "/internal-image", GET);
    HttpRoute rt2("index2.html", "/external-image", GET);
    HttpRoute rt3("form_test.html","/form-test", POST);
    HttpRoute rt4("index3.html", "/main", GET);
    HttpRoute rt5("index4.html", "/video-test", GET);

    server.run();

    return 0;

}