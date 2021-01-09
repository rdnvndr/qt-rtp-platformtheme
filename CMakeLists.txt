cmake_minimum_required(VERSION 3.16)

project(rtptheme LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT QT_DEFAULT_MAJOR_VERSION)
    set(QT_DEFAULT_MAJOR_VERSION 5 CACHE STRING "Qt version to use (5 or 6), defaults to 5")
endif()
find_package(Qt${QT_DEFAULT_MAJOR_VERSION} COMPONENTS Widgets REQUIRED)

add_library(rtptheme SHARED
  main.cpp  
  rtptheme.cpp  
  rtptheme.h  
  rtptheme.json
)

target_link_libraries(rtptheme PRIVATE Qt::Widgets)
target_link_libraries(rtptheme PRIVATE Qt::GuiPrivate)

target_compile_definitions(rtptheme PRIVATE RTPTHEME_LIBRARY)

