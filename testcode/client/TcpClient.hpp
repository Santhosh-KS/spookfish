#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


class TcpClient
{
private:
  int  PortNumber;
  int SocketFd;
  struct sockaddr_in ServerAddress;
  struct hostent *AppServer;
  char Buffer[2048];
  TcpClient() = delete;
public:
  void Connect();
  TcpClient(std::string server, int portNum);
  ~TcpClient();
};

#endif // TCP_CLIENT_HPP
