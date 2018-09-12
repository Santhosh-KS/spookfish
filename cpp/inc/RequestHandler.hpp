#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include "JsonStringParser.hpp"
#include "NotCopyable.hpp"
#include <string>
#include <memory>

class RequestHandler : public NotCopyable
{
private:
  std::unique_ptr<JsonStringParser> Parser;
  std::string SessionId;
  std::string YoutubeUrl;
  std::string RtpUrl;
  std::string Epoch;
public:
  RequestHandler();
  RequestHandler(std::string str);
  ~RequestHandler();
  bool ProcessRequest(std::string &str);
};


#endif // REQUEST_HANDLER_HPP
