#include "ImageResource.hpp"
#if 0
ImageResource::ImageResource(int id) :
  Id(id), // Keeping it as a placeholder for factory methods.
  ImageColumnDiv(std::make_unique<Wt::WContainerWidget>()),
  ImageThumbnailDiv(std::make_unique<Wt::WContainerWidget>()),
  ImageDiv(std::make_unique<Wt::WContainerWidget>()),
  CaptionDiv(std::make_unique<Wt::WContainerWidget>()),
  Image(std::make_unique<Wt::WImage>()),
  Caption(std::make_unique<Wt::WText>("Image-Name"))
{
  ImageColumnDiv->setStyleClass("col-md-5 col-xs-3");
  ImageThumbnailDiv->setStyleClass("thumbnail");
  // TODO create an anchor tag.
  Image->setStyleClass("img-responsive");
  CaptionDiv->setStyleClass("caption");
}

ImageResource::~ImageResource()
{
  // Empty
}

bool ImageResource::SetupDisplayImage(int id, std::string link)
{
  if (id != Id) {
    throw("Invalid ID\n");
  }
  // setup image.
  Image->setImageLink(Wt::WLink(link));
  ImageDiv->addWidget(Image.get());
  ImageThumbnailDiv->addWidget(ImageDiv.get());

  // setup captioni for the image.
  // TODO: Set the caption text.
  CaptionDiv->addWidget(Caption.get());
  ImageThumbnailDiv->addWidget(CaptionDiv.get());

  // put everything in one div.
  ImageColumnDiv->addWidget(ImageThumbnailDiv.get());
}

std::unique_ptr<Wt::WContainerWidget> ImageResource::GetImgContainer(int id)
{
  if (id == Id) {
  return ImageColumnDiv;
  }
  else {
    throw("Invalid ID");
  }
}
#endif

ImageResource::ImageResource(int id) :
  Id(id), // Keeping it as a placeholder for factory methods.
  ImageColumnDiv(std::make_shared<Wt::WContainerWidget>()),
  ImageThumbnailDiv(std::make_shared<Wt::WContainerWidget>()),
  ImageDiv(std::make_shared<Wt::WContainerWidget>()),
  CaptionDiv(std::make_shared<Wt::WContainerWidget>()),
  Image(std::make_shared<Wt::WImage>()),
  Anchor(std::make_shared<Wt::WAnchor>()),
  Caption(std::make_shared<Wt::WText>("Image-Name"))
{
  ImageColumnDiv->setStyleClass("col-md-5 col-xs-3");
  ImageThumbnailDiv->setStyleClass("thumbnail");
  // TODO create an anchor tag.
  Image->setStyleClass("img-responsive");
  CaptionDiv->setStyleClass("caption");
}

ImageResource::~ImageResource()
{
  // Empty
}

bool ImageResource::SetupDisplayImage(int id, std::string link)
{
  if (id != Id) {
    throw("Invalid ID\n");
  }
  // setup image.
  Image->setImageLink(Wt::WLink(link));
  Wt::WLink anchorLink = Wt::WLink(link);
  anchorLink.setTarget(Wt::LinkTarget::NewWindow);
  Anchor->setLink(anchorLink);
  ImageDiv->addWidget(Image.get());
  ImageDiv->addWidget(Anchor.get());
  ImageThumbnailDiv->addWidget(ImageDiv.get());

  // setup captioni for the image.
  // TODO: Set the caption text.
  CaptionDiv->addWidget(Caption.get());
  ImageThumbnailDiv->addWidget(CaptionDiv.get());

  // put everything in one div.
  ImageColumnDiv->addWidget(ImageThumbnailDiv.get());
}

std::shared_ptr<Wt::WContainerWidget> ImageResource::GetImgContainer(int id)
{
  if (id == Id) {
  return ImageColumnDiv;
  }
  else {
    throw("Invalid ID");
  }
}
