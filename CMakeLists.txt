cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)
project(GLCube)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(.)
add_executable(GLCube
    glwidget.h
    glwidget.cpp
    mainwindow.h
    mainwindow.cpp
    main.cpp)

target_link_libraries(GLCube Qt5::Widgets Qt5::OpenGL OpenGL::GL)
