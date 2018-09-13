#include "RequestHandler.hpp"
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
  // Empty;
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
    vec.push_back(Parser->GetString(Epoch));
    vec.push_back(Parser->GetString(YoutubeUrl));
    vec.push_back(Parser->GetString(RtpUrl));
    //SessionMap.insert(std::make_pair<std::string, std::vector<std::string>>(Parser->GetString(SessionId), vec));
    SessionMap[Parser->GetString(SessionId)] = vec;
    status.clear();
    status = "200 OK";
    return status;
  }
}
