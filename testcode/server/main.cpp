#include <iostream>
#include <string>

#include "TcpServer.hpp"

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cout << "Usage: ./server <port>\n";
    return -1;
  }
  std::string port(argv[1]);
  TcpServer server(std::stoi(port));
  server.Run();
  return 0;
}
