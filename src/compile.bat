g++ -c MYNET.cpp -o MYNET.o

g++ -c HttpServer.cpp -o HttpServer.o

ar -rcs libMYNET.a MYNET.o HttpServer.o

del MYNET.o

del HttpServer.o