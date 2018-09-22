PROJECT(VideoAnalyserProject)

#####################################################################
#                    Project dependencies                           #
#####################################################################

FIND_PACKAGE( OpenCV REQUIRED )
SET(dlib_path /opt/dlib/dlib/cmake)
SET(rapid_json /opt/rapidjson/include)

#####################################################################
#                                                                   #
#####################################################################

SET(bin_src src/main.cpp
            src/JsonWriter.cpp 
            src/Stats.cpp
            src/CaptureVideo.cpp
            src/DlibHandler.cpp
            src/FaceCluster.cpp
            src/DrawingUtils.cpp
            src/RequestHandler.cpp
            src/LinkApp.cpp
            src/Enroll.cpp
            common/src/JsonFileParser.cpp
            common/src/JsonStringParser.cpp
            common/src/TcpServer.cpp)

# binary name
SET(bin_name videoAnalyser)

INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS})
INCLUDE(${dlib_path})

ADD_EXECUTABLE(${bin_name} ${bin_src})
TARGET_LINK_LIBRARIES(${bin_name} ${OpenCV_LIBS} dlib::dlib)

TARGET_INCLUDE_DIRECTORIES(${bin_name} PUBLIC inc ui/inc common/inc  ${rapid_json})

TARGET_COMPILE_FEATURES(${bin_name} PUBLIC  cxx_lambda_init_captures)

ADD_COMPILE_OPTIONS(-Wall -Wextra -Wpedantic -Werror)
#ADD_COMPILE_OPTIONS(-Wall -Wextra -Wpedantic -g)

INSTALL(TARGETS ${bin_name} EXPORT ${bin_name} 
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)
