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

#include <cstdlib>
#include <fstream>
#include <thread>
#include <signal.h>

#include <Wt/WBreak>
#include <Wt/WMessageBox>

#include "SpookfishWt.hpp"


// Private Methods.
void SpookfishApplication::VideoAnalyzer(std::string str)
{
  LinkApp link("");
  link.Run(str);
}

void SpookfishApplication::SetVideoPlaybackStatus(const std::string str)
{
  VideoPlaybackStatus->setText(str.c_str());
}

void SpookfishApplication::SetupVideoPlayer()
{
//  std::string mp4Video = "https://www.webtoolkit.eu/videos/sintel_trailer.mp4";
//  VideoPlayer->addSource(Wt::WLink(mp4Video));
  VideoPlayer->resize(680, 400);
  //VideoPlayerDiv->setStyleClass(Wt::WString::fromUTF8("col-md-6"));
  //VideoPlayerDiv->setStyleClass(Wt::WString::fromUTF8("input-group"));

  std::string str("<p>Video playing</p>");
  VideoPlayer->playbackStarted().connect(boost::bind(&SpookfishApplication::SetVideoPlaybackStatus, this, str));
  str.clear();
  str = "<p>Video paused</p>";
  VideoPlayer->playbackPaused().connect(boost::bind(&SpookfishApplication::SetVideoPlaybackStatus, this, str));
  str.clear();
  str = "<p>Volume changed</p>";
  VideoPlayer->volumeChanged().connect(boost::bind(&SpookfishApplication::SetVideoPlaybackStatus, this, str));
  str.clear();
  str = "<p>Video Ended</p>";
  VideoPlayer->ended().connect(boost::bind(&SpookfishApplication::SetVideoPlaybackStatus, this, str));

  VideoPlayerDivVideoWidgetDiv->addWidget(VideoPlayer.get());
  VideoPlayerDiv->addWidget(VideoPlayerDivVideoWidgetDiv.get());
  VideoPlayerDivStatusDiv->addWidget(VideoPlaybackStatus.get());
  VideoPlayerDiv->addWidget(VideoPlayerDivStatusDiv.get());

  MainLeftDiv->addWidget(VideoPlayerDiv.get());
  // let's play hide and seek.
  VideoPlayerDiv->hide();
}

void SpookfishApplication::SetupTheme()
{
  Theme->setVersion(Wt::WBootstrapTheme::Version3);
  setTheme(Theme.get());

  useStyleSheet(Wt::WLink("css/styleSheet.css")); // TODO: Configurable.
  //useStyleSheet(Wt::WLink("resources/main.css")); // TODO: Configurable.
  useStyleSheet(Wt::WLink("resources/themes/bootstrap/3/bootstrap.min.css"));

}

void SpookfishApplication::SetupHeader()
{
  HeaderDiv->setId("header");
  HeaderDiv->setStyleClass(Wt::WString::fromUTF8(""));
  HeaderDivTextDiv->setId("h3");
  HeaderDivTextDiv->addWidget(HeaderText.get());
  HeaderDiv->addWidget(HeaderDivTextDiv.get());
}

void SpookfishApplication::SetupSearchVideoBar()
{
  // To support multi resolution devices need to enable the below line.
  //SearchDiv->setStyleClass(Wt::WString::fromUTF8("col-md-6 col-xs-6 col-lg-6 col-sm-6"));

  SearchDiv->setStyleClass(Wt::WString::fromUTF8("col-md-6"));
  SearchDiv->setStyleClass(Wt::WString::fromUTF8("input-group"));

  // Expirimenting on the single line of class support. Works but need to test more
  // with different set of options.
  //SearchDiv->setStyleClass(Wt::WString::fromUTF8("col-md-12 input-group"));

  SearchLineEdit->setStyleClass(Wt::WString::fromUTF8("form-control"));
  SearchLineEdit->setFocus(true);
  SearchDivPlayButtonDiv->setStyleClass(Wt::WString::fromUTF8("input-group-btn"));
  PlayButton->setStyleClass(Wt::WString::fromUTF8("btn btn-success with-label"));

  SearchDivLineEditDiv->addWidget(SearchLineEdit.get());
  SearchDivPlayButtonDiv->addWidget(PlayButton.get());

  SearchDiv->addWidget(SearchDivLineEditDiv.get());
  SearchDiv->addWidget(SearchDivPlayButtonDiv.get());

  MainLeftDiv->addWidget(SearchDiv.get());

  MainLeftDiv->setId("main_left");
  MainRightDiv->setId("main_right");

  // Setup signal and slot when user press enter after entering the URL.
  SearchLineEdit->enterPressed().connect
        (boost::bind(&SpookfishApplication::OnPlayButtonPressed, this));
  PlayButton->clicked().connect(this, &SpookfishApplication::OnPlayButtonPressed);

}

void SpookfishApplication::SetupFooter()
{
  FooterDiv->setId("footer");
  FooterDivTextDiv->addWidget(FooterText.get());
  FooterDiv->addWidget(FooterDivTextDiv.get());
}

void SpookfishApplication::OnPlayButtonPressed()
{
  auto url(SearchLineEdit->text().toUTF8());
  // little sanity check on the URL.

  if (url.find("https://www.youtube.com") != std::string::npos
      || url.find("http://www.youtube.com") != std::string::npos)  {
    std::string cmd("python ./ui/scripts/youtube.py -u "); // TODO: Change the path.
    std::string file("/tmp/playablevidlink.txt");
    std::string redirect(" > " + file );
    int ret = system((cmd + url + redirect).c_str());

    if (WIFSIGNALED(ret)
        && (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT)) {
      return;
    }
    std::ifstream infile(file);
    std::string line;
    while (std::getline(infile, line)) {
      if (!line.empty()) {
        VideoPlayerDiv->show();
        VideoPlayer->clearSources();
        VideoPlayer->addSource(Wt::WLink(line));
        // TODO WARNING:  Creating a thread is not the best way to handle this situation.
        // It is not an optimal solution. If multiple users starts accessing the website;
        // then there will be having atleast 1 thread per user/session which will bloat up the
        // system resources in notime and results in very bad end user experiance. Hence this design
        // is not a scalable solution to deploy it as is in the field.
        // This is just a work around to get it running for the demo.
        // Ideally we should span the Video Analyser as a separate Process on a
        // powerful machine and have a pub-sub model to get the work done.
        // Introducing the above mechanism is time consuming and invloves more effort.
        // Hence settling for this approach. This is enough for the demo purpose.
        std::thread analyzerThread(&SpookfishApplication::VideoAnalyzer, this, line);
        analyzerThread.detach();
        break;
      }
    }
  }
  else {
    VideoPlayerDiv->hide();
    Wt::WMessageBox::show("Information", "Please give me youtube URL.", Wt::Ok);
  }
  //VideoPlayerDiv->show();
}

/*
void SpookfishApplication::SetupProgressBar()
{
  ProgressBar->setRange(0,10);
  ProgressBarDiv->addWidget("ProgressBar", ProgressBar.get());
}
*/

std::unique_ptr<Wt::WContainerWidget> SpookfishApplication::SetupImage(std::string &imgPath)
{
  auto imgDiv = std::make_unique<Wt::WContainerWidget>();
  //auto img = std::make_unique<Wt::WImage>(Wt::WLink("images/cluster_0.jpg"));
  auto img = std::make_unique<Wt::WImage>(Wt::WLink(imgPath.c_str()), imgDiv.get());
  img->setAlternateText("SNOW IMAGE");
  std::cout << "Called SetupImage() = " << (img->imageLink().url().c_str()) <<  "\n";
  return imgDiv;
}

void SpookfishApplication::SetupImageDiv()
{
  /*
  std::string link("css/cluster_0.jpg");
  //std::string link("images/cluster_0.jpg");
  std::cout << "Called SetupImageDiv()\n";
  //auto localImgDiv = SetupImage(link);
  ParentImageDiv->addWidget(localImgDiv.get());
*/

/*
  MainRightDiv->setStyleClass("container-fluid");
  ParentImageDiv->setStyleClass("row");
  ImageDiv->setStyleClass("col-md-5 col-xs-3");
  Image->setStyleClass("img-responsive img-thumbnail");
  ImageDiv->addWidget(Image.get());
  ParentImageDiv->addWidget(ImageDiv.get());
  MainRightDiv->addWidget(ParentImageDiv.get());
*/
  MainRightDiv->setStyleClass("container-fluid");
  ParentImageDiv->setStyleClass("row");

  /*
  std::string link("css/cluster_0.jpg");
  int id(0);
  auto imgRes = std::make_unique<ImageResource>(id);
  //ImageResource imgRes(id);
  imgRes->SetupDisplayImage(id, link);
  ImgResource.push_back(imgRes);
  //ParentImageDiv->addWidget(ImgResource[id]->GetImgContainer(id).get());
  ParentImageDiv->addWidget(imgRes->GetImgContainer(id).get());
  MainRightDiv->addWidget(ParentImageDiv.get());
  BodyDiv->addWidget(MainRightDiv.get());
*/

  MainRightDiv->setStyleClass("container-fluid");
  ParentImageDiv->setStyleClass("row");
  int id(10);
  std::string link("images/cluster_4.jpg");
  //std::string link("https://github.com/Santhosh-KS/travis_CI_opencv/blob/master/cluster_3.jpg?raw=true");
  SingleImgResource->SetupDisplayImage(id, link);
  ParentImageDiv->addWidget(SingleImgResource->GetImgContainer(id).get());

  id = 11;
  std::string link2("images/cluster_5.jpg");
  //std::string link("https://github.com/Santhosh-KS/travis_CI_opencv/blob/master/cluster_3.jpg?raw=true");
  SecondImgResource->SetupDisplayImage(id, link2);
  ParentImageDiv->addWidget(SecondImgResource->GetImgContainer(id).get());

  id = 12;
  auto third = std::make_unique<ImageResource>(id);
  std::string link3("images/cluster_0.jpg");
  third->SetupDisplayImage(id, link3);
  ParentImageDiv->addWidget(third->GetImgContainer(id).get());


  MainRightDiv->addWidget(ParentImageDiv.get());

  /*
  auto container = std::make_unique<Wt::WContainerWidget>();
  container->setStyleClass("container-fluid");
  auto row = std::make_unique<Wt::WContainerWidget>();
  row->setStyleClass("row");
  auto column = std::make_unique<Wt::WContainerWidget>();
  column->setStyleClass("col-md-5 col-xs-3");
  auto image = std::make_unique<Wt::WImage>(Wt::WLink("images/cluster_0.jpg"));
  image->setStyleClass("img-responsive img-thumbnail");
  column->addWidget(image.get());
  row->addWidget(column.get());
  container->addWidget(row.get());
  root()->addWidget(container.get());
  */
}

// Public methods

SpookfishApplication::SpookfishApplication(const Wt::WEnvironment& env)
  : WApplication(env),
  Theme(std::make_unique<Wt::WBootstrapTheme>()),
  BodyDiv(std::make_unique<Wt::WContainerWidget>(root())),
  HeaderDiv(std::make_unique<Wt::WContainerWidget>()),
  HeaderDivTextDiv(std::make_unique<Wt::WContainerWidget>()),
  HeaderText(std::make_unique<Wt::WText>(Wt::WString::fromUTF8("spookfish"))),
  MainLeftDiv(std::make_unique<Wt::WContainerWidget>()),
  MainRightDiv(std::make_unique<Wt::WContainerWidget>()),
  SearchDiv(std::make_unique<Wt::WContainerWidget>()),
  SearchDivLineEditDiv(std::make_unique<Wt::WContainerWidget>()),
  SearchLineEdit(std::make_unique<Wt::WLineEdit>(Wt::WString::fromUTF8("Give me Youtube video URL"))),
  SearchDivPlayButtonDiv(std::make_unique<Wt::WContainerWidget>()),
//  ProgressBarDiv(std::make_unique<Wt::WContainerWidget>()),
//  ProgressBar(std::make_unique<Wt::WProgressBar>()),
  PlayButton(std::make_unique<Wt::WPushButton>(Wt::WString::fromUTF8("Play"))),
  VideoPlayerDiv(std::make_unique<Wt::WContainerWidget>()),
  VideoPlayerDivVideoWidgetDiv(std::make_unique<Wt::WContainerWidget>()),
  VideoPlayer(std::make_unique<Wt::WVideo>()),
  VideoPlayerDivStatusDiv(std::make_unique<Wt::WContainerWidget>()),
  VideoPlaybackStatus(std::make_unique<Wt::WText>(Wt::WString::fromUTF8("Playback not started."))),
  ParentImageDiv(std::make_unique<Wt::WContainerWidget>()),
  ImageThumbnailDiv(std::make_unique<Wt::WContainerWidget>()),
  ImageDiv(std::make_unique<Wt::WContainerWidget>()),
  Image(std::make_unique<Wt::WImage>(Wt::WLink("images/cluster_0.jpg"))),
  SingleImgResource(std::make_unique<ImageResource>(10)),
  SecondImgResource(std::make_unique<ImageResource>(11)),
  FooterDiv(std::make_unique<Wt::WContainerWidget>()),
  FooterDivTextDiv(std::make_unique<Wt::WContainerWidget>()),
  FooterText(std::make_unique<Wt::WText>(Wt::WString::fromUTF8("© Copyrights spookfish. All Rights Reserved.")))
{
  SetupTheme();
  SetupHeader();
  SetupSearchVideoBar();
  SetupVideoPlayer();
  SetupImageDiv();
  SetupFooter();

  // Attach all the containers/divs in the same flow as
  // browser renders the components.

  BodyDiv->addWidget(HeaderDiv.get());
  BodyDiv->addWidget(MainRightDiv.get());
  BodyDiv->addWidget(MainLeftDiv.get());
  BodyDiv->addWidget(FooterDiv.get());
 /*
  auto container = std::make_unique<Wt::WContainerWidget>();
  container->setStyleClass("container-fluid");
  auto row = std::make_unique<Wt::WContainerWidget>();
  row->setStyleClass("row");
  auto column = std::make_unique<Wt::WContainerWidget>();
  column->setStyleClass("col-md-5 col-xs-3");
  auto image = std::make_unique<Wt::WImage>(Wt::WLink("images/cluster_0.jpg"));
  image->setStyleClass("img-responsive img-thumbnail");
  column->addWidget(image.get());
  row->addWidget(column.get());
  container->addWidget(row.get());
  root()->addWidget(container.get());
*/
}

SpookfishApplication::~SpookfishApplication()
{
  // Empty
}
