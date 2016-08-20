cmake_minimum_required(VERSION 3.5)
project(nginx-instaban)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lconfig++ -lconfig")
set(SOURCE_FILES main.cpp strFuncs.h banMgr.h banMgr.cpp banMgr.h nginxConfigReader.cpp nginxConfigReader.h IpParser.h IpHashTableGeneric.cpp IpHashTableGeneric.h BanRecord.h IpParser.cpp BinaryOps.h CheckIpHashTable.cpp CheckIpHashTable.h Configuration.cpp Configuration.h)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules")
FIND_PACKAGE(Config++ REQUIRED)
add_executable(nginx-instaban ${SOURCE_FILES})
target_link_libraries(nginx-instaban libconfig++.a)