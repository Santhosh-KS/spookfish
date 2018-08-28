CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

Project(SpookfishProject)

INCLUDE_DIRECTORIES(/usr/include/Wt/)
LINK_DIRECTORIES(/usr/lib/Wt/)


ADD_EXECUTABLE(SpookfishWt main.cpp SpookfishWt.cpp)
TARGET_COMPILE_FEATURES(SpookfishWt PUBLIC  cxx_lambda_init_captures)

TARGET_LINK_LIBRARIES(SpookfishWt
  debug wtd      optimized wt
  debug wthttpd  optimized wthttp
  #  debug lhpdfd optimized lhpdf # only required for if you write pdfs
)


