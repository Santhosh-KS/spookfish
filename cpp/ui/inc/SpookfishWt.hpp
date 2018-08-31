#ifndef SPOOKFISH_WT_HPP
#define SPOOKFISH_WT_HPP

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

#include <Wt/WContainerWidget>
#include <Wt/WApplication>
#include <Wt/WBootstrapTheme>

#include <Wt/WText>
#include <Wt/WLink>
#include <Wt/WLineEdit>
#include <Wt/WVideo>
#include <Wt/WPushButton>
#include <memory>

#include "LinkApp.hpp"

class SpookfishApplication : public Wt::WApplication
{
private:
  std::unique_ptr<LinkApp> BackendLink;
  std::unique_ptr<Wt::WBootstrapTheme> Theme;

  std::unique_ptr<Wt::WContainerWidget> BodyDiv;

  std::unique_ptr<Wt::WContainerWidget> MainLeftDiv;
  // Header stuff.
  std::unique_ptr<Wt::WContainerWidget> HeaderDiv;
  std::unique_ptr<Wt::WContainerWidget> HeaderDivTextDiv;
  std::unique_ptr<Wt::WText> HeaderText;

  // Search box and loading the youtube url widgets
  // are grouped under this div.
  std::unique_ptr<Wt::WContainerWidget> SearchDiv;
  std::unique_ptr<Wt::WContainerWidget> SearchDivLineEditDiv;
  std::unique_ptr<Wt::WLineEdit> SearchLineEdit;
  std::unique_ptr<Wt::WContainerWidget> SearchDivPlayButtonDiv;
  std::unique_ptr<Wt::WPushButton> PlayButton;


  // Video Widget stuff.
  std::unique_ptr<Wt::WContainerWidget> VideoPlayerDiv;
  std::unique_ptr<Wt::WContainerWidget> VideoPlayerDivVideoWidgetDiv;
  std::unique_ptr<Wt::WVideo> VideoPlayer;
  std::unique_ptr<Wt::WContainerWidget> VideoPlayerDivStatusDiv;
  std::unique_ptr<Wt::WText> VideoPlaybackStatus;

  // Analysed image other stats stuff  widgets
  // are grouped under this div.
  std::unique_ptr<Wt::WContainerWidget> MainRightDiv;

  // Footer stuff.
  std::unique_ptr<Wt::WContainerWidget> FooterDiv;
  std::unique_ptr<Wt::WContainerWidget> FooterDivTextDiv;
  std::unique_ptr<Wt::WText> FooterText;

  SpookfishApplication() = delete;
  void SetupTheme();
  void SetupHeader();
  void SetupSearchVideoBar();
  void SetupVideoPlayer();
  void SetVideoPlaybackStatus(const std::string str);
  void SetupFooter();
  void OnPlayButtonPressed();
  void VideoAnalyzer(std::string str);
public:
  SpookfishApplication(const Wt::WEnvironment& env);
  ~SpookfishApplication();
};

#endif // SPOOKFISH_WT_HPP
