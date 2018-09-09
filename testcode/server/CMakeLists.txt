CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

Project(ServerProject)

LINK_DIRECTORIES(/usr/lib/)


ADD_EXECUTABLE(Server TcpServer.cpp main.cpp)
TARGET_COMPILE_FEATURES(Server PUBLIC  cxx_lambda_init_captures)

#TARGET_LINK_LIBRARIES(Server pthread)
