cmake_minimum_required(VERSION 3.21)
project(Projet_QCM)

set(OpenCV_DIR "C:\\Users\\caoth\\CLionProjects\\opencv\\cmake-build-release\\install")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(OpenCV REQUIRED)


include_directories(${OpenCV_INCLUDE_DIRS})


set(CMAKE_CXX_STANDARD 14)
link_libraries(ws2_32)
add_executable(Projet_QCM main.cpp ClientSocket.cpp ClientSocket.h ServeurSocket.cpp ServeurSocket.h TraitementImage.h TraitementImage.cpp)

target_link_libraries(Projet_QCM ${OpenCV_LIBS})