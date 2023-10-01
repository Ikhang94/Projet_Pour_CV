cmake_minimum_required(VERSION 3.20)
project(codeShifumi)

set(CMAKE_CXX_STANDARD 14)

add_executable(codeShifumi main.cpp codeShifumi.h codeShifumi.cpp)

include_directories(include)
find_library(TEST_SOCKET lwsocket lib)
target_link_libraries(codeShifumi LINK_PUBLIC ${TEST_SOCKET} ws2_32)

#link_directories(lib)
#target_link_libraries(codeShifumi LINK_PUBLIC lwsocket )
