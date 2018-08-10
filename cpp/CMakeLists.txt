CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

PROJECT(SpookFish)

FIND_PACKAGE( OpenCV REQUIRED )

# all source files
SET(bin_src src/main.cpp)
# binary name
SET(bin_name videoAnalyser)

# set your dlib path
SET(dlib_path /opt/dlib/dlib/cmake)

INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS})
INCLUDE(${dlib_path})


ADD_EXECUTABLE(${bin_name} ${bin_src})
TARGET_LINK_LIBRARIES(${bin_name} ${OpenCV_LIBS} dlib::dlib)

TARGET_INCLUDE_DIRECTORIES(${bin_name} PUBLIC inc)

TARGET_COMPILE_FEATURES(${bin_name} PUBLIC  cxx_lambda_init_captures)

#ADD_COMPILE_OPTIONS(-Wall -Wextra -Wpedantic -Werror)
ADD_COMPILE_OPTIONS(-Wall -Wextra -Wpedantic )

INSTALL(TARGETS ${bin_name} EXPORT ${bin_name} 
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

