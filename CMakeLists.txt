cmake_minimum_required(VERSION 3.28)
project(NerdFontsIconBrowser VERSION 1.0.0 LANGUAGES CXX)

set(EXECUTABLE_NAME "NerdFontsIconBrowser")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.h"
    "src/*.ui"
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${EXECUTABLE_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
