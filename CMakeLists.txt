cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)
project(GLCube)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)
find_package(OpenGL REQUIRED)
find_library(netcdf_c++4 REQUIRED)

include_directories(.)
add_executable(GLCube
    glwidget.h
    glwidget.cpp
    mainwindow.h
    mainwindow.cpp
    main.cpp)

target_link_libraries(GLCube Qt5::Widgets Qt5::OpenGL OpenGL::GL netcdf_c++4)

