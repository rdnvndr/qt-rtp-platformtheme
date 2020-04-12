cmake_minimum_required(VERSION 3.5)

project(rtptheme LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(rtptheme SHARED
  main.cpp  
  rtptheme.cpp  
  rtptheme.h  
  rtptheme.json
)

target_link_libraries(rtptheme PRIVATE Qt5::Widgets)
target_link_libraries(rtptheme PRIVATE Qt5::GuiPrivate)

target_compile_definitions(rtptheme PRIVATE RTPTHEME_LIBRARY)

