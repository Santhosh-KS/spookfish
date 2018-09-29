/*
   MIT License

   Copyright (c) 2018 santhoshachar08@gmail.com

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/



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

void TcpClient::Connect(std::string &str)
{
  if (SocketFd < 1) {
    std::cerr << "ERROR in SocketFd\n";
    return;
  }
  if (connect(SocketFd, (struct sockaddr *) &ServerAddress, sizeof(ServerAddress)) < 0) {
    std::cerr << "ERROR connecting\n";
    return;
  }
//  std::cout << "Please enter the message: ";
  bzero(Buffer, sizeof(Buffer));
  //fgets(Buffer, sizeof(Buffer),stdin);
  str.copy(Buffer, str.length());
  Buffer[str.length()+1] = '\0';
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
