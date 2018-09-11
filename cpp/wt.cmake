Project(WtUiProject)

SET(bin_src ui/src/NewUi.cpp
            ui/src/main.cpp
            common/src/TcpClient.cpp
            common/src/JsonFileParser.cpp)

SET(bin_name NewUiWt)
SET(rapid_json /opt/rapidjson/include)
SET(wt_inc /usr/include/Wt)

ADD_EXECUTABLE(${bin_name} ${bin_src}) 
TARGET_COMPILE_FEATURES(${bin_name} PUBLIC  cxx_lambda_init_captures)
TARGET_INCLUDE_DIRECTORIES(${bin_name} PUBLIC ui/inc common/inc ${rapid_json} ${wt_inc})

TARGET_LINK_LIBRARIES(${bin_name}
  debug wtd      optimized wt
  debug wthttpd  optimized wthttp)
