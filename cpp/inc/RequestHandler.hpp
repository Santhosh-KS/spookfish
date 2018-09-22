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

#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include "JsonStringParser.hpp"
#include "NotCopyable.hpp"
#include "LinkApp.hpp"
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <thread>

class RequestHandler : public NotCopyable
{
private:
  std::unique_ptr<JsonStringParser> Parser;
  std::string SessionId;
  std::string YoutubeUrl;
  std::string RtpUrl;
  std::string Epoch;
  std::string Action;
  typedef std::map<std::string, std::vector<std::string>> TSessionMap;
  TSessionMap SessionMap;
  std::vector<std::thread> ThreadVec;
  std::vector<std::shared_ptr<LinkApp>> LinkVec;
public:
  RequestHandler();
  RequestHandler(std::string str);
  ~RequestHandler();
  std::string ProcessRequest(std::string &str);
  void VideoAnalyzer(std::string str, std::string sessId);
  void Clusterize(std::string sessId);
  void EnrollImages(std::string sessId);
};
#endif // REQUEST_HANDLER_HPP
