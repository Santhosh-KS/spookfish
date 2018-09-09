CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

PROJECT(SpookFish)

#####################################################################
#                    Project dependencies                           #
#####################################################################

FIND_PACKAGE( OpenCV REQUIRED )

SET(dlib_path /opt/dlib/dlib/cmake)
SET(rapid_json /opt/rapidjson/include)

#####################################################################
#                                                                   #
#####################################################################

# all source files
SET(bin_src_ui
  ui/src/main.cpp
  ui/src/NewUi.cpp
  #ui/src/LinkApp.cpp
  src/JsonParser.cpp
  src/JsonWriter.cpp 
  src/Stats.cpp
  src/CaptureVideo.cpp
  src/DlibHandler.cpp
  src/FaceCluster.cpp
  src/DrawingUtils.cpp)


SET(bin_src src/main.cpp
            src/JsonParser.cpp
            src/JsonWriter.cpp 
            src/Stats.cpp
            src/CaptureVideo.cpp
            src/DlibHandler.cpp
            src/FaceCluster.cpp
            src/DrawingUtils.cpp
            ui/SpookfishWt.cpp)

# binary name
SET(bin_name videoAnalyser)

INCLUDE_DIRECTORIES(/usr/include/Wt/)
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS})
INCLUDE(${dlib_path})

ADD_EXECUTABLE(${bin_name} ${bin_src_ui})
TARGET_LINK_LIBRARIES(${bin_name} ${OpenCV_LIBS} dlib::dlib
  debug wtd      optimized wt 
  debug wthttpd  optimized wthttp)

LINK_DIRECTORIES(/usr/lib/Wt/)
TARGET_INCLUDE_DIRECTORIES(${bin_name} PUBLIC inc ui/inc  ${rapid_json})

TARGET_COMPILE_FEATURES(${bin_name} PUBLIC  cxx_lambda_init_captures)

ADD_COMPILE_OPTIONS(-Wall -Wextra -Wpedantic -Werror)
#ADD_COMPILE_OPTIONS(-Wall -Wextra -Wpedantic -g)

INSTALL(TARGETS ${bin_name} EXPORT ${bin_name} 
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)
