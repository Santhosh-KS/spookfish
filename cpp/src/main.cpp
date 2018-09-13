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

#include "CaptureVideo.hpp"
#include "FaceCluster.hpp"
#include "RequestHandler.hpp"
#include "TcpServer.hpp"


int main(int argc, char** argv)
{
  int port(1234);
  TcpServer server(port);
  std::cout << "Server Listening on port: " << port << "\n";
  RequestHandler handler;
  while (true) {
    server.Accept();
    std::string jsonRequest = server.Read();
    std::string replay(handler.ProcessRequest(jsonRequest));
    //std::string replay("300 OK");
    server.Send(replay);
  }
  server.Close();
#if 0
  try {
    //auto clusterConfig("../data/ClusterConfig.json");
    //auto dataPathConfig("../data/DataPaths.json");
    auto dataPathConfig("./data/bkup_DataPaths.json");
    auto clusterConfig("./data/bkup_ClusterConfig.json");
    CaptureVideo vidCapture(dataPathConfig);
    FaceCluster cluster(clusterConfig);
    vidCapture.Run();

    // Enable clustering only when required.
    //cluster.Run();
  }
  catch(const std::exception& e ) {
    std::cerr << e.what() << "\n";
  }
#endif
  return 0;
}
