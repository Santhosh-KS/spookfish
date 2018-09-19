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


#ifndef NEW_UI_WT_HPP
#define NEW_UI_WT_HPP


#include <Wt/WApplication.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WVideo.h>
#include <memory>


class NewUiApplication : public Wt::WApplication
{
private:
  Wt::WLineEdit *SearchLineEdit;
  Wt::WPushButton *PlayButton;
  Wt::WVideo *VideoPlayer;
  Wt::WText *VideoPlaybackStatus;
  Wt::WContainerWidget *MainVideoDiv;
  Wt::WContainerWidget *MainVideoContainer;
  Wt::WContainerWidget *MainImageGallaryDiv;
  Wt::WContainerWidget *MainNavToolDiv;
  Wt::WContainerWidget *FooterDiv;
  Wt::WContainerWidget *ThumbnailDiv;
  Wt::WContainerWidget *ClusterImageGallaryDiv;
  typedef std::map<std::string, std::string> TImageAnchorLinkMap;
//  std::string PersonEditedName;
  bool IsClusterEnabled;
  void SetupTheme();
  void SetupHeader();
  void SetupMainBody();
  void SetupVideoSearchBar(Wt::WContainerWidget *mainLeft);
  void SetupVideoPlayer(Wt::WContainerWidget *mainLeft);
  //void SetupImageGallary(Wt::WContainerWidget *mainRight);
  void SetupImageGallary(Wt::WContainerWidget *mainRight, TImageAnchorLinkMap &imgAnchorLinkMap);
  //void SetupImageGallary(Wt::WContainerWidget *mainRight, std::vector<std::string> &testVec, std::string imgDir);
  //void SetupImageGallary(Wt::WContainerWidget *mainRight, std::vector<std::string> &testVec);
  void SetupFooter();
  void OnPlayButtonPressed();
  void OnClusterButtonPressed();
  void OnAllImagesButtonPressed();
  void OnSaveButtonPressed();
  void OnPersonNameChanged(int index, std::string str);
  void SetVideoPlaybackStatus(const std::string str);
  void SetupNavToolBar(Wt::WContainerWidget *navToolDiv);
  void SetupProgressBar(Wt::WContainerWidget *div);
  bool SendVideoAnalysisRequest(std::string &action, std::string &playUrl);
  //void CreateServer();
  void CreateServer(Wt::WContainerWidget *ptr);
  void SetupRefreshTimer();
  void TimeOutReached();
  //std::vector<std::string> GetImageFiles(std::string &path);
  TImageAnchorLinkMap GetImageFiles(std::string &inFile);
public:
  NewUiApplication(const Wt::WEnvironment& env);
  ~NewUiApplication();
};

#endif // NEW_UI_WT_HPP
