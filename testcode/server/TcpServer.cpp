#include <iostream>
#include <strings.h>

#include "TcpServer.hpp"

TcpServer::TcpServer(int port):
  ServerPort(port),
  SocketFd(socket(AF_INET, SOCK_STREAM, 0)),
  ServerAddress(),
  ClientAddress()
{
  if (SocketFd < 0 || ServerPort < 1) {
    throw("Error Opening Socket\n");
  }
  ServerAddress.sin_family = AF_INET;
  ServerAddress.sin_addr.s_addr = INADDR_ANY;
  ServerAddress.sin_port = htons(ServerPort);

  if (bind(SocketFd, (struct sockaddr *) &ServerAddress,
        sizeof(ServerAddress)) < 0) {
    throw("ERROR on binding\n");
  }
  listen(SocketFd,5);
  ClientLen = sizeof(ClientAddress);

}

TcpServer::~TcpServer()
{
  close(ConnectionSockFd);
  close(SocketFd);
}

void TcpServer::Run()
{
  while(1) {
    ConnectionSockFd  = accept(SocketFd,
        (struct sockaddr *) &ClientAddress, &ClientLen);
    if (ConnectionSockFd < 0) {
      //error("ERROR on accept");
      std::cout << "ERROR on accept\n";
      continue;
    }
    std::cout << "Server: Got Connection from "
      <<  inet_ntoa(ClientAddress.sin_addr)
      << " on port " << ntohs(ClientAddress.sin_port) << "\n";

    send(ConnectionSockFd, "200 OK\n", 6, 0);

    bzero(Buffer,sizeof(Buffer));

    int n = read(ConnectionSockFd, Buffer, sizeof(Buffer));
    if (n < 0)  {
      std::cerr << "ERROR reading from socket\n";
      continue;
    }
    std::cout << "Here is the Message: " << Buffer << "\n";
  }
  close(ConnectionSockFd);
  close(SocketFd);
}
