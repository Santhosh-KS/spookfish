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
  Close();
}
#if 0
void TcpServer::Run()
{
  //while(1) {
    ConnectionSockFd  = accept(SocketFd,
        (struct sockaddr *) &ClientAddress, &ClientLen);
    if (ConnectionSockFd < 0) {
      //error("ERROR on accept");
      std::cout << "ERROR on accept\n";
     // continue;
    }
    std::cout << "Server: Got Connection from "
      <<  inet_ntoa(ClientAddress.sin_addr)
      << " on port " << ntohs(ClientAddress.sin_port) << "\n";

    /*
    send(ConnectionSockFd, "200 OK\n", 6, 0);
    bzero(Buffer,sizeof(Buffer));

    int n = read(ConnectionSockFd, Buffer, sizeof(Buffer));
    if (n < 0)  {
      std::cerr << "ERROR reading from socket\n";
      continue;
    }
    std::cout << "Here is the Message: " << Buffer << "\n";
    */
  //}
  //close(ConnectionSockFd);
  //close(SocketFd);
}
#endif
void TcpServer::Accept()
{
  ConnectionSockFd  = accept(SocketFd,
      (struct sockaddr *) &ClientAddress, &ClientLen);
  if (ConnectionSockFd < 0) {
    std::cout << "ERROR on accept\n";
  }
  std::cout << "Server: Got Connection from "
    <<  inet_ntoa(ClientAddress.sin_addr)
    << " on port " << ntohs(ClientAddress.sin_port) << "\n";
}

std::string TcpServer::Read()
{
  bzero(Buffer,sizeof(Buffer));
  int n = read(ConnectionSockFd, Buffer, sizeof(Buffer));
  if (n < 0)  {
    std::cerr << "ERROR reading from socket\n";
    return std::string("");
  }
  std::cout << "Here is the Message: " << Buffer << "\n";
  return std::string(Buffer);
}

void TcpServer::Send(std::string &str)
{
  send(ConnectionSockFd, str.c_str(), str.length(), 0);
  return;
}

void TcpServer::Close()
{
  close(ConnectionSockFd);
  close(SocketFd);
}
