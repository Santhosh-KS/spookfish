#ifndef LINK_APP_HPP
#define LINK_APP_HPP

#include <memory>
#include <string>

#include "NotCopyable.hpp"
#include "CaptureVideo.hpp"
#include "FaceCluster.hpp"
#include "JsonParser.hpp"


class LinkApp: public NotCopyable
{
private:
  std::string DataPathConfig;
  std::string ClusterConfig;
  std::unique_ptr<CaptureVideo> VideoCapture;
  std::unique_ptr<FaceCluster> Cluster;
public:
  LinkApp(std::string);
  ~LinkApp();
  int Run(std::string &link);
};

#endif // LINK_APP_HPP
