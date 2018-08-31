#ifndef LINK_APP_HPP
#define LINK_APP_HPP

#include "CaptureVideo.hpp"
#include "FaceCluster.hpp"
#include "JsonParser.hpp"


class LinkApp: public NonCopyable
{
public:
  LinkApp(std::string);
  ~LinkApp();
};

#endif // LINK_APP_HPP
