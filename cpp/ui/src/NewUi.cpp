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



#include <fstream>
#include <string>
#include <vector>
#include <signal.h>

#include <Wt/WMessageBox.h>
#include <Wt/WAnchor.h>

#include "NewUi.hpp"
#include "TcpClient.hpp"
#include "JsonParser.hpp"


void NewUiApplication::SetupTheme()
{
  //setCssTheme("bootstrap3");
  useStyleSheet(Wt::WLink("css/styleSheet.css")); // TODO: Configurable.
  useStyleSheet(Wt::WLink("resources/themes/bootstrap/3/bootstrap.min.css"));
  //useStyleSheet(Wt::WLink("resources/main.css")); // TODO: Configurable.
}

void NewUiApplication::SetupHeader()
{
  Wt::WContainerWidget *HeaderDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  HeaderDiv->setId("header");
  //HeaderDiv->setStyleClass("page-header");
  Wt::WContainerWidget *HeaderDivTextDiv = HeaderDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  HeaderDivTextDiv->setId("h3");
  Wt::WText *HeaderText = HeaderDivTextDiv->addWidget(std::make_unique<Wt::WText>(Wt::WString::fromUTF8("spookfish")));
}

void NewUiApplication::SetupVideoSearchBar(Wt::WContainerWidget *mainLeft)
{
  Wt::WContainerWidget *RowDiv = mainLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
  RowDiv->setStyleClass("row");

  Wt::WContainerWidget *ColumnLeftDiv = RowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  ColumnLeftDiv->setStyleClass("col-md-3  col-xs-1 col-sm-1");

  Wt::WContainerWidget *ColumnMiddleDiv = RowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  ColumnMiddleDiv->setStyleClass("col-md-6  col-xs-3 col-sm-3");

  Wt::WContainerWidget *SearchDiv = ColumnMiddleDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  SearchDiv->setStyleClass("input-group");
  Wt::WContainerWidget *SearchDivLineEditDiv = SearchDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  //SearchLineEdit = SearchDivLineEditDiv->addWidget(std::make_unique<Wt::WLineEdit>(Wt::WString::fromUTF8("Give me Youtube URL")));
  SearchLineEdit = SearchDivLineEditDiv->addWidget(std::make_unique<Wt::WLineEdit>(Wt::WString::fromUTF8("https://www.youtube.com/watch?v=giYeaKsXnsI")));
  SearchLineEdit->setStyleClass("form-control");
  SearchLineEdit->setFocus();
  Wt::WContainerWidget *ButtonDiv = SearchDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  ButtonDiv->setStyleClass("input-group-btn");
  PlayButton = ButtonDiv->addWidget(std::make_unique<Wt::WPushButton>("Play"));
  PlayButton->setStyleClass(Wt::WString::fromUTF8("btn btn-success with-label"));

  Wt::WContainerWidget *ColumnRightDiv= RowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  ColumnRightDiv->setStyleClass("col-md-3  col-xs-1 col-sm-1");

  SearchLineEdit->enterPressed().connect
    (std::bind(&NewUiApplication::OnPlayButtonPressed, this));

  PlayButton->clicked().connect(this, &NewUiApplication::OnPlayButtonPressed);
}

void NewUiApplication::SetupNavToolBar(Wt::WContainerWidget *navToolDiv)
{
  Wt::WContainerWidget *btnGrp = navToolDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  btnGrp->setStyleClass("btn-group btn-group-justified");

  Wt::WContainerWidget *btnDiv1= btnGrp->addWidget(std::make_unique<Wt::WContainerWidget>());
  btnDiv1->setStyleClass("btn-group");
  Wt::WPushButton *btn1 = btnDiv1->addWidget(std::make_unique<Wt::WPushButton>("Primary"));
  btn1->setStyleClass("btn btn-primary");

  Wt::WContainerWidget *btnDiv2= btnGrp->addWidget(std::make_unique<Wt::WContainerWidget>());
  btnDiv2->setStyleClass("btn-group");
  Wt::WPushButton *btn2 = btnDiv2->addWidget(std::make_unique<Wt::WPushButton>("Info"));
  btn2->setStyleClass("btn btn-info");

  Wt::WContainerWidget *btnDiv3= btnGrp->addWidget(std::make_unique<Wt::WContainerWidget>());
  btnDiv3->setStyleClass("btn-group");
  Wt::WPushButton *btn3 = btnDiv3->addWidget(std::make_unique<Wt::WPushButton>("Success"));
  btn3->setStyleClass("btn btn-success");

  Wt::WContainerWidget *btnDiv4= btnGrp->addWidget(std::make_unique<Wt::WContainerWidget>());
  btnDiv4->setStyleClass("btn-group");
  Wt::WPushButton *btn4 = btnDiv4->addWidget(std::make_unique<Wt::WPushButton>("Warning"));
  btn4->setStyleClass("btn btn-warning");

  Wt::WContainerWidget *btnDiv5= btnGrp->addWidget(std::make_unique<Wt::WContainerWidget>());
  btnDiv5->setStyleClass("btn-group");
  Wt::WPushButton *btn5 = btnDiv5->addWidget(std::make_unique<Wt::WPushButton>("Danger"));
  btn5->setStyleClass("btn btn-danger");

  Wt::WContainerWidget *btnDiv6= btnGrp->addWidget(std::make_unique<Wt::WContainerWidget>());
  btnDiv6->setStyleClass("btn-group");
  Wt::WPushButton *btn6 = btnDiv6->addWidget(std::make_unique<Wt::WPushButton>("Default"));
  btn6->setStyleClass("btn btn-default");
  MainNavToolDiv->hide();
}

void NewUiApplication::SetupVideoPlayer(Wt::WContainerWidget *mainLeft)
{
  MainVideoContainer = mainLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
  Wt::WContainerWidget *rowDiv = MainVideoContainer->addWidget(std::make_unique<Wt::WContainerWidget>());
  rowDiv->setStyleClass("row");

  Wt::WContainerWidget *columnLeftDiv = rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  columnLeftDiv->setStyleClass("col-md-3  col-xs-1 ");

  Wt::WContainerWidget *ColumnMiddleDiv = rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  ColumnMiddleDiv->setStyleClass("col-md-6 col-xs-3");

  Wt::WContainerWidget *VideoPlayerDiv = ColumnMiddleDiv->addWidget(std::make_unique<Wt::WContainerWidget>());

  VideoPlayerDiv->setStyleClass("embed-responsive embed-responsive-4by3");
  VideoPlayer = VideoPlayerDiv->addWidget(std::make_unique<Wt::WVideo>());

  VideoPlaybackStatus = ColumnMiddleDiv->addWidget(std::make_unique<Wt::WText>("Playback Not started."));
  VideoPlaybackStatus->setStyleClass("videoStatus");
  Wt::WContainerWidget *columnRightDiv = rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  columnRightDiv->setStyleClass("col-md-3  col-xs-1 ");

  std::string str("<p>Video playing</p>");
  VideoPlayer->playbackStarted().connect(std::bind(&NewUiApplication::SetVideoPlaybackStatus, this, str));
  str.clear();
  str = "<p>Video paused</p>";
  VideoPlayer->playbackPaused().connect(std::bind(&NewUiApplication::SetVideoPlaybackStatus, this, str));
  str.clear();
  str = "<p>Volume changed</p>";
  VideoPlayer->volumeChanged().connect(std::bind(&NewUiApplication::SetVideoPlaybackStatus, this, str));
  str.clear();
  str = "<p>Video Ended</p>";
  VideoPlayer->ended().connect(std::bind(&NewUiApplication::SetVideoPlaybackStatus, this, str));
  MainVideoContainer->hide();
}

void NewUiApplication::SetupImageGallary(Wt::WContainerWidget *mainRight)
{
  Wt::WContainerWidget *gallaryDiv = mainRight->addWidget(std::make_unique<Wt::WContainerWidget>());
  gallaryDiv->setStyleClass("container-fluid");
  Wt::WContainerWidget *rowDiv = gallaryDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  rowDiv->setStyleClass("row");
  std::vector<std::string> testVec;
  testVec.push_back("images/30/1534569993258_1_30_30_200_200.jpg");
  testVec.push_back("images/30/1534569993258_1_30_30_200_200.jpg");
  testVec.push_back("images/30/1534569993258_1_30_30_200_200.jpg");
  testVec.push_back("images/30/1534569993258_1_30_30_200_200.jpg");
  testVec.push_back("images/30/1534569993258_1_30_30_200_200.jpg");
  testVec.push_back("images/30/1534569993258_1_30_30_200_200.jpg");
  testVec.push_back("images/30/1534569993258_1_30_30_200_200.jpg");
  std::string link("images/30/1534569993258_1_30_30_200_200.jpg");
  for (auto link: testVec) {
    // Wt::WImage *img = thumbnail->addWidget(std::make_unique<Wt::WContainerWidget>(Wt::WLink(link)));
    // img->setStyleClass("img-responsive ");
    Wt::WContainerWidget *columnDiv = rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
    columnDiv->setStyleClass("col-md-2 col-xs-4");
    Wt::WContainerWidget *thumbnailDiv= columnDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
    thumbnailDiv->setStyleClass("thumbnail");
    Wt::WLink anchorLink = Wt::WLink(link);
    anchorLink.setTarget(Wt::LinkTarget::NewWindow);
    Wt::WAnchor *anchor = thumbnailDiv->addWidget(std::make_unique<Wt::WAnchor>(anchorLink));
    anchor->addNew<Wt::WImage>(Wt::WLink("images/30/1534569993258_1_30_30_200_200.jpg"));
    Wt::WText *caption = thumbnailDiv->addWidget(std::make_unique<Wt::WText>("Unknown"));
  }
  MainImageGallaryDiv->hide();
}

void NewUiApplication::SetupFooter()
{
  Wt::WContainerWidget *FooterDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  FooterDiv->setId("footer");
  Wt::WContainerWidget *FooterDivTextDiv = FooterDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  Wt::WText *Text = FooterDivTextDiv->addWidget(std::make_unique<Wt::WText>(Wt::WString::fromUTF8("© Spookfish. All Rights Reserved.")));
}

void NewUiApplication::SetupProgressBar(Wt::WContainerWidget *div)
{
  Wt::WContainerWidget *mainProgressDiv = div->addWidget(std::make_unique<Wt::WContainerWidget>());
  mainProgressDiv->setId("customProgressBar");

  Wt::WContainerWidget *row = mainProgressDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  row->setStyleClass("row");

  Wt::WContainerWidget *colDiv1 = row->addWidget(std::make_unique<Wt::WContainerWidget>());
  colDiv1->setStyleClass("col-md-3  col-xs-1 ");

  Wt::WContainerWidget *colDiv2 = row->addWidget(std::make_unique<Wt::WContainerWidget>());
  colDiv2->setStyleClass("col-md-6 col-xs-3");
  Wt::WContainerWidget *progressDiv = colDiv2->addWidget(std::make_unique<Wt::WContainerWidget>());
  //Wt::WContainerWidget *progressDiv = div->addWidget(std::make_unique<Wt::WContainerWidget>());
  progressDiv->setStyleClass("progress");

  Wt::WContainerWidget *progressBarDiv = progressDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  //progressBarDiv->setStyleClass("progress-bar progress-bar-striped active");
  progressBarDiv->setStyleClass("progress-bar progress-bar-success progress-bar-striped active");
  //progressBarDiv->setStyleClass("progress-bar");
  //progressBarDiv->setAttributeValue("class",Wt::WString("progress-bar"));
/*  progressBarDiv->setAttributeValue("role",Wt::WString("progressbar"));
  progressBarDiv->setAttributeValue("aria-valuenow", Wt::WString("100"));
  progressBarDiv->setAttributeValue("aria-valuemin", Wt::WString("0"));
  progressBarDiv->setAttributeValue("aria-valuemax", Wt::WString("100"));*/
  progressBarDiv->setAttributeValue("style", Wt::WString("min-width: 2em; width: 100%;"));
   //aria-valuenow="45" aria-valuemin="0" aria-valuemax="100" style="width: 45%">

  Wt::WContainerWidget *currentProgress = progressBarDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  currentProgress->setStyleClass("sr-only");

  Wt::WText *status = currentProgress->addWidget(std::make_unique<Wt::WText>());
  status->setText("45\% complete");

  Wt::WContainerWidget *colDiv3 = row->addWidget(std::make_unique<Wt::WContainerWidget>());
  colDiv3->setStyleClass("col-md-3  col-xs-1 ");
}

// Event and button click handlers.
void NewUiApplication::OnPlayButtonPressed()
{
  auto url(SearchLineEdit->text().toUTF8());
  // little sanity check on the URL.
  //std::string jsonRequst("{\"URL\":\"youtube.com\"}");
  std::cout << "OnPlayButtonPressed\n";
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
        VideoPlayer->show();
        VideoPlayer->clearSources();
        VideoPlayer->addSource(Wt::WLink(line));
        // TODO WARNING:  Creating a thread is not the best way to handle this situation.
        // It is not an optimal solution. If multiple users starts accessing the website;
        // then there will be atleast 1 thread per user/session which will bloat up the
        // system resources and results in very bad end user experiance. Hence this design
        // is not a scalable solution to deploy it as is in the field.
        // This is just a work around to get it running for the demo.
        // Ideally we should span the Video Analyser as a separate Process on a
        // powerful machine and have a pub-sub model to get the work done.
        // Introducing the above mechanism is time consuming and invloves more effort.
        // Hence settling for this approach. This is enough for the demo purpose.
        //std::thread analyzerThread(&NewUiApplication::VideoAnalyzer, this, line);
        //analyzerThread.detach();
        SendVideoAnalysisRequest(line);
        break;
      }
    }
  }
  else {
    VideoPlayer->hide();
    Wt::WMessageBox::show("Information", "Please give me youtube URL.", Wt::StandardButton::Ok);
  }
  //VideoPlayer->show();
  MainVideoContainer->show();
  MainNavToolDiv->show();
  MainImageGallaryDiv->show();
}


bool NewUiApplication::SendVideoAnalysisRequest(std::string &plyUriVal)
{
  std::string serverIp("localhost");
  int port(1234);
  std::string jsonFile("./ui/data/Request_format.json");
  JsonParser parser(jsonFile);

  std::string youTubeUrlKey("Youtube_URL");
  std::string sessIdKey("Session_Id");
  std::string plyUriKey("Rtp_Stream_URL");

  std::string youTubeUrlVal(SearchLineEdit->text().toUTF8());
  // Each client connection will have an unique sessionID.
  // same can be used if the user gives multiple youtube links
  // to analyse. And controll the rest of the video processing.
  std::string sessIdVal(sessionId());

  parser.SetString(sessIdKey, sessIdVal);
  parser.SetString(plyUriKey , plyUriVal);
  parser.SetString(youTubeUrlKey, youTubeUrlVal);

  std::string jsonRequst(parser.GetStrigifiedJson());
  //std::cout << " Stringified obj: " << parser.GetStrigifiedJson().c_str();
  TcpClient client(serverIp, port);
  std::string result(client.Connect(jsonRequst));

  if (result.compare("200 OK") == 0) {
    std::cout << "Success: " << result.c_str() << "\n";
  }
  else if (result.compare("300 OK") == 0) {
    std::cout << "Analysis running: " << result.c_str() << "\n";
  }
  else {
    std::cout << "Failed: " << result.c_str() << "\n";
  }
  return true;
}

void NewUiApplication::SetVideoPlaybackStatus(const std::string str)
{
  VideoPlaybackStatus->setText(str.c_str());
  VideoPlaybackStatus->setStyleClass("videoStatus");
}



NewUiApplication::NewUiApplication(const Wt::WEnvironment& env)
  : WApplication(env)
{
  setTitle("Spookfish UI");                            // application title
  SetupTheme();
  SetupHeader();
  //Wt::WContainerWidget *MainRightDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  //MainRightDiv->setId("main_right");
  //SetupImageGallary(MainRightDiv);
  MainVideoDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  MainVideoDiv->setId("main_left");
  SetupVideoSearchBar(MainVideoDiv);
  SetupVideoPlayer(MainVideoDiv);

  MainNavToolDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  MainNavToolDiv->setId("gallaryNavBar");
  SetupNavToolBar(MainNavToolDiv);

  Wt::WContainerWidget *ProgressBar= root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  ProgressBar->setId("customProgressBar");
  SetupProgressBar(ProgressBar);

  MainImageGallaryDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  MainImageGallaryDiv->setId("gallary");
  //MainImageGallaryDiv->setStyleClass("alert alert-success");
  SetupImageGallary(MainImageGallaryDiv);

  SetupFooter();
/*
  root()->addWidget(std::make_unique<Wt::WText>("Your name, please ? ")); // show some text

  nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>()); // allow text input
  nameEdit_->setFocus();                              // give focus

  auto button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
                                                      // create a button
  button->setMargin(5, Wt::Side::Left);                   // add 5 pixels margin

  root()->addWidget(std::make_unique<Wt::WBreak>());    // insert a line breaki*/
}


NewUiApplication::~NewUiApplication()
{
  // Empty;
}
