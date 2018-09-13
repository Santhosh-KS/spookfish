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


#include "RequestHandler.hpp"
#include "LinkApp.hpp"
#include <iostream>

RequestHandler::RequestHandler(std::string str) :
  Parser(std::make_unique<JsonStringParser>(str)),
  SessionId("Session_Id"),
  YoutubeUrl("Youtube_URL"),
  RtpUrl("Rtp_Stream_URL"),
  Epoch("Epoch_Time")
{
  // Empty
}

RequestHandler::RequestHandler(): RequestHandler(std::string("{}"))
{
  // Empty
}

RequestHandler::~RequestHandler()
{
  for(auto &t: ThreadVec) {
    t.join();
  }
}

std::string RequestHandler::ProcessRequest(std::string &str)
{
  Parser = std::make_unique<JsonStringParser>(str);
  std::cout << SessionId.c_str() << " : " << Parser->GetString(SessionId).c_str() << "\n";
  std::cout << YoutubeUrl.c_str() << " : " << Parser->GetString(YoutubeUrl).c_str() << "\n";
  std::cout << RtpUrl.c_str() << " : " << Parser->GetString(RtpUrl).c_str() << "\n";
  std::cout << Epoch.c_str() << " : " << Parser->GetString(Epoch).c_str() << "\n";
  auto itr = SessionMap.find(Parser->GetString(SessionId));
  std::string status("404 NOT OK");
  if (itr != SessionMap.end()) {
    std::string newUrl = Parser->GetString(YoutubeUrl);
    if (newUrl.compare(itr->second[1]) == 0) {
      status.clear();
      status = "300 OK"; // Already playing the same URL.
      return status;
    }
    else {
      status.clear();
      status = "500 OK"; // Video Analysis is started for the previous request. User need to wait for it to complete.
      return status;
    }
  }
  else {
    std::vector<std::string> vec;
    std::string rtpUrl(Parser->GetString(RtpUrl));
    // Order in which we push here is important.
    // Do not mess up.
    vec.push_back(Parser->GetString(Epoch));
    vec.push_back(Parser->GetString(YoutubeUrl));
    vec.push_back(rtpUrl);
    SessionMap[Parser->GetString(SessionId)] = vec;
    status.clear();
    status = "200 OK";
    std::thread analyzerThread(&RequestHandler::VideoAnalyzer, this, rtpUrl);
    //analyzerThread.detach();
    ThreadVec.push_back(std::move(analyzerThread));
    return status;
  }
}

void RequestHandler::VideoAnalyzer(std::string str)
{
  auto link = std::make_shared<LinkApp>("") ;
  link->Run(str);
  LinkVec.push_back(link);
  //LinkVec.push_back(std::make_unique<LinkApp>(""));
}
