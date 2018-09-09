CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

Project(ClientProject)

LINK_DIRECTORIES(/usr/lib/)


ADD_EXECUTABLE(Client TcpClient.cpp main.cpp)
TARGET_COMPILE_FEATURES(Client PUBLIC  cxx_lambda_init_captures)
