#include "RequestHandler.hpp"
#include <iostream>

RequestHandler::RequestHandler(std::string str) :
  Parser(std::make_unique<JsonStringParser>(str)),
  SessionId("Session_Id"),
  YoutubeUrl("Youtube_URL"),
  RtpUrl("Rtp_Stream_URL"),
  Epoch("Epoch_Time")
{
}

#if 0
RequestHandler::RequestHandler():
  RequestHandler(std::string("{\"Session_Id\":\"NULL\",
      \"Youtube_URL\":\"NULL\",
      \"Rtp_Stream_URL\":\"NULL\",
      \"Epoch_Time\":\"NULL\"}"))
{
  // Empty;
}
#endif

RequestHandler::RequestHandler(): RequestHandler(std::string("{}"))
{
}

RequestHandler::~RequestHandler()
{
  // Empty;
}

bool RequestHandler::ProcessRequest(std::string &str)
{
  //Parser.reset(std::make_unique<JsonStringParser>(str));
  Parser = std::make_unique<JsonStringParser>(str);
  std::cout << SessionId.c_str() << " : " << Parser->GetString(SessionId).c_str() << "\n";
  std::cout << YoutubeUrl.c_str() << " : " << Parser->GetString(YoutubeUrl).c_str() << "\n";
  std::cout << RtpUrl.c_str() << " : " << Parser->GetString(RtpUrl).c_str() << "\n";
  std::cout << Epoch.c_str() << " : " << Parser->GetString(Epoch).c_str() << "\n";
  return true;
}
