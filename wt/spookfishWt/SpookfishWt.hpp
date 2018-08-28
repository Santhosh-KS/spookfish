#ifndef SPOOKFISH_WT_HPP
#define SPOOKFISH_WT_HPP

#include <Wt/WContainerWidget>
#include <Wt/WApplication>
#include <Wt/WBootstrapTheme>

#include <Wt/WText>
#include <Wt/WLink>
#include <Wt/WLineEdit>
#include <Wt/WVideo>
#include <Wt/WPushButton>
#include <memory>

using namespace Wt;

class SpookfishApplication : public WApplication
{
private:
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
public:
  SpookfishApplication(const WEnvironment& env);
  ~SpookfishApplication();
};

#endif // SPOOKFISH_WT_HPP
