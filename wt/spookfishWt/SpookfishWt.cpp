#include "SpookfishWt.hpp"

SpookfishApplication::SpookfishApplication(const WEnvironment& env)
  : WApplication(env),
  Theme(std::make_unique<Wt::WBootstrapTheme>()),
  BodyDiv(std::make_unique<Wt::WContainerWidget>(root())),
  HeaderDiv(std::make_unique<Wt::WContainerWidget>()),
  HeaderDivTextDiv(std::make_unique<Wt::WContainerWidget>()),
  HeaderText(std::make_unique<Wt::WText>("spookfish")),
  MainLeftDiv(std::make_unique<Wt::WContainerWidget>()),
  MainRightDiv(std::make_unique<Wt::WContainerWidget>()),
  SearchDiv(std::make_unique<Wt::WContainerWidget>()),
  SearchDivLineEditDiv(std::make_unique<Wt::WContainerWidget>()),
  SearchLineEdit(std::make_unique<Wt::WLineEdit>("Give me Youtube URL")),
  SearchDivPlayButtonDiv(std::make_unique<Wt::WContainerWidget>()),
  PlayButton(std::make_unique<Wt::WPushButton>("Play"))
{
  Theme->setVersion(Wt::WBootstrapTheme::Version3);
  setTheme(Theme.get());

  useStyleSheet(Wt::WLink("styleSheet.css"));
  //useStyleSheet(Wt::WLink("resources/main.css"));
  useStyleSheet(Wt::WLink("resources/themes/bootstrap/3/bootstrap.min.css"));

  HeaderDiv->setId("header");
  HeaderDiv->setStyleClass(Wt::WString::fromUTF8(""));
  HeaderDivTextDiv->setId("h3");
  HeaderDivTextDiv->addWidget(HeaderText.get());
  HeaderDiv->addWidget(HeaderDivTextDiv.get());

  MainLeftDiv->setId("main_left");
  MainRightDiv->setId("main_right");

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
  SearchDivPlayButtonDiv->setInline(1);
  PlayButton->setStyleClass(Wt::WString::fromUTF8("btn btn-success with-label"));

  SearchDivLineEditDiv->addWidget(SearchLineEdit.get());
  SearchDivPlayButtonDiv->addWidget(PlayButton.get());

  SearchDiv->addWidget(SearchDivLineEditDiv.get());
  SearchDiv->addWidget(SearchDivPlayButtonDiv.get());
  MainLeftDiv->addWidget(SearchDiv.get());

  BodyDiv->addWidget(HeaderDiv.get());
  BodyDiv->addWidget(MainRightDiv.get());
  BodyDiv->addWidget(MainLeftDiv.get());
}

SpookfishApplication::~SpookfishApplication()
{
  // Empty
}
