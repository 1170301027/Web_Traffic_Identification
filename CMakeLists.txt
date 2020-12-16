cmake_minimum_required(VERSION 3.17)
project(Web_Traffic_Identification)

set(CMAKE_CXX_STANDARD 14)

link_libraries(ws2_32)

add_executable(Web_Traffic_Identification WebCrawl.h test.cpp MyPaser.h FileHandle.h DataStructure.h Keys.h)