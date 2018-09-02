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

  Wt::WContainerWidget *ThumbnailDiv;
  void SetupTheme();
  void SetupHeader();
  void SetupMainBody();
  //void SetupVideoSearchBar();
  void SetupVideoSearchBar(Wt::WContainerWidget *mainLeft);
  void SetupVideoPlayer(Wt::WContainerWidget *mainLeft);
  void SetupImageGallary(Wt::WContainerWidget *mainRight);
  void SetupFooter();
  void OnPlayButtonPressed();
  void SetVideoPlaybackStatus(const std::string str);
  void SetupNavToolBar(Wt::WContainerWidget *navToolDiv);
  void SetupProgressBar(Wt::WContainerWidget *div);
public:
  NewUiApplication(const Wt::WEnvironment& env);
  ~NewUiApplication();
};


