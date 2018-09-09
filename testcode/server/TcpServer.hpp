#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class TcpServer {
  private:
    int ServerPort;
    int SocketFd;
    int ConnectionSockFd;
    struct sockaddr_in ServerAddress;
    struct sockaddr_in ClientAddress;
    socklen_t ClientLen;
    char Buffer[2048];
    TcpServer() = delete;
  public:
    TcpServer(int port);
    ~TcpServer();
    void Run();
};

#endif // TCP_SERVER_HPP
