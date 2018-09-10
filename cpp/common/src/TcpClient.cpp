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

std::string TcpClient::Connect(std::string &msg)
{
  if (msg.size() > 2047) {
    std::cerr << "ERROR: Message length is >2047 bytes\n";
    return std::string("");
  }
  if (SocketFd < 1) {
    std::cerr << "ERROR in SocketFd\n";
    return std::string("");
  }
  if (connect(SocketFd, (struct sockaddr *) &ServerAddress, sizeof(ServerAddress)) < 0) {
    std::cerr << "ERROR connecting\n";
    return std::string("");
  }
  bzero(Buffer, sizeof(Buffer));
  //std::cout << "Please enter the message: ";
  //fgets(Buffer, sizeof(Buffer),stdin);
  msg.copy(Buffer, msg.size()+1);
  Buffer[msg.size()+1] = '\0';
  std::cout << "Message to be sent: " << Buffer << "\n";
  int n = write(SocketFd, Buffer, strlen(Buffer));
  if (n < 0) {
    std::cerr << "ERROR writing to socket";
    close(SocketFd);
    return std::string("");
  }
  bzero(Buffer,sizeof(Buffer));
  n = read(SocketFd, Buffer, sizeof(Buffer));
  if (n < 0) {
    std::cerr << "ERROR reading from socket";
    close(SocketFd);
    return std::string("");
  }
  //std::cout << "Server Response: " << Buffer << "\n";
  close(SocketFd);
  return std::string(Buffer);
}
