Project(WtUiProject)

SET(bin_src ui/src/NewUi.cpp ui/src/main.cpp)
SET(bin_name NewUiWt)

ADD_EXECUTABLE(${bin_name} ${bin_src}) 
TARGET_COMPILE_FEATURES(${bin_name} PUBLIC  cxx_lambda_init_captures)
TARGET_INCLUDE_DIRECTORIES(${bin_name} PUBLIC ui/inc /usr/include/Wt)

TARGET_LINK_LIBRARIES(${bin_name}
  debug wtd      optimized wt
  debug wthttpd  optimized wthttp)
