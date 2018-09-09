#include <iostream>
#include <unistd.h>
#include "TcpClient.hpp"


TcpClient::TcpClient(std::string server, int portNum):
  PortNumber(portNum),
  SocketFd(socket(AF_INET, SOCK_STREAM, 0)),
  AppServer(gethostbyname(server.c_str()))
{
  if (PortNumber < 1) {
    throw("ERROR: Invalid Port.\n");
  }
  if (AppServer == nullptr) {
    throw("ERROR: No such host\n");
  }
  if (SocketFd < 0) {
    std::cerr << "ERROR opening socket";
    SocketFd = -1;
  }
  else {
    bzero((char*) &ServerAddress, sizeof(ServerAddress));
    ServerAddress.sin_family = AF_INET;
    bcopy((char *)AppServer->h_addr,
      (char *)&ServerAddress.sin_addr.s_addr,
      AppServer->h_length);
    ServerAddress.sin_port = htons(PortNumber);
  }
}

TcpClient::~TcpClient()
{
  close(SocketFd);
}

void TcpClient::Connect()
{
  if (SocketFd < 1) {
    std::cerr << "ERROR in SocketFd\n";
    return;
  }
  if (connect(SocketFd, (struct sockaddr *) &ServerAddress, sizeof(ServerAddress)) < 0) {
    std::cerr << "ERROR connecting\n";
    return;
  }
  std::cout << "Please enter the message: ";
  bzero(Buffer, sizeof(Buffer));
  fgets(Buffer, sizeof(Buffer),stdin);
  int n = write(SocketFd, Buffer, strlen(Buffer));
  if (n < 0) {
    std::cerr << "ERROR writing to socket";
    return;
  }
  bzero(Buffer,sizeof(Buffer));
  n = read(SocketFd, Buffer, sizeof(Buffer));
  if (n < 0) {
    std::cerr << "ERROR reading from socket";
    return;
  }
  std::cout << "Server Response: " << Buffer << "\n";
  close(SocketFd);
}
