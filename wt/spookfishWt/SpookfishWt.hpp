#ifndef SPOOKFISH_WT_HPP
#define SPOOKFISH_WT_HPP

#include <Wt/WContainerWidget>
#include <Wt/WApplication>
#include <Wt/WBootstrapTheme>

#include <Wt/WText>
#include <Wt/WLink>
#include <Wt/WLineEdit>
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

  // Analysed image other stats stuff  widgets
  // are groped under this div.
  std::unique_ptr<Wt::WContainerWidget> MainRightDiv;

  SpookfishApplication() = delete;

public:
  SpookfishApplication(const WEnvironment& env);
  ~SpookfishApplication();

};

#endif // SPOOKFISH_WT_HPP
