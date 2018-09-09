Project(WtUiProject)

INCLUDE_DIRECTORIES(/usr/include/Wt/)
LINK_DIRECTORIES(/usr/lib/ /usr/lib/Wt)

#ADD_DEFINITIONS(-DHPDF_DLL)

ADD_EXECUTABLE(NewUiWt ui/src/NewUi.cpp ui/src/main.cpp)
TARGET_COMPILE_FEATURES(NewUiWt PUBLIC  cxx_lambda_init_captures)
TARGET_INCLUDE_DIRECTORIES(NewUiWt PUBLIC ui/inc /usr/include/Wt)

TARGET_LINK_LIBRARIES(NewUiWt
  debug wtd      optimized wt
  debug wthttpd  optimized wthttp
  #  debug lhpdfd optimized lhpdf # only required for if you write pdfs
)


