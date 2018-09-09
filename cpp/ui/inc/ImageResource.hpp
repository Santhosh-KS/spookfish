#ifndef IMAGE_RESOURCE_HPP
#define IMAGE_RESOURCE_HPP

#include "NotCopyable.hpp"

#include <Wt/WContainerWidget>
#include <Wt/WImage>
#include <Wt/WText>
#include <Wt/WAnchor>


class ImageResource
//class ImageResource : public NotCopyable
{
private:
#if 0
  std::unique_ptr<Wt::WContainerWidget> ImageColumnDiv;
  std::unique_ptr<Wt::WContainerWidget> ImageThumbnailDiv;
  std::unique_ptr<Wt::WContainerWidget> ImageDiv;
  std::unique_ptr<Wt::WContainerWidget> CaptionDiv;
  std::unique_ptr<Wt::WImage> Image;
  std::unique_ptr<Wt::WText> Caption;
#endif
  std::shared_ptr<Wt::WContainerWidget> ImageColumnDiv;
  std::shared_ptr<Wt::WContainerWidget> ImageThumbnailDiv;
  std::shared_ptr<Wt::WContainerWidget> ImageDiv;
  std::shared_ptr<Wt::WContainerWidget> CaptionDiv;
  std::shared_ptr<Wt::WImage> Image;
  std::shared_ptr<Wt::WText> Caption;
  std::shared_ptr<Wt::WAnchor> Anchor;
  int Id;
  ImageResource() = delete;
public:
  ImageResource(int id);
  ~ImageResource();
  bool SetupDisplayImage(int id, std::string link);
  std::shared_ptr<Wt::WContainerWidget> GetImgContainer(int id);
};
#endif // IMAGE_RESOURCE_HPP
