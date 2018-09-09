#include <iostream>
#include <string>

#include "TcpClient.hpp"

int main(int argc, char** argv)
{
  if (argc != 3) {
    std::cout << "Usage: ./client <server_ip> <port>\n";
    return -1;
  }
  std::string serverIp(argv[1]);
  std::string port(argv[2]);
  TcpClient client(serverIp, std::stoi(port));
  client.Connect();
  return 0;
}
