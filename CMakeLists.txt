cmake_minimum_required(VERSION 3.28)

set(VERSION 0.0.4)

if(WIN32)
    project(NerdFontsIconBrowser VERSION ${VERSION} LANGUAGES CXX)
    set(APPDATA_APP "$ENV{APPDATA}/NerdFontsIconBrowser")
else()
    project(nf-icon-browser VERSION ${VERSION} LANGUAGES CXX)
    set(APPDATA_APP "$ENV{HOME}/.local/share/nf-icon-browser")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(FONTNAME "0xProtoNerdFontPropo-Regular.ttf")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.h"
    "src/*.ui"
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE MACOSX_BUNDLE_ICON_FILE "icon.png")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${APPDATA_APP}" "${APPDATA_APP}/fallback"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/res/glyphnames.json" "${APPDATA_APP}/glyphnames.json"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/res/fallback/${FONTNAME}" "${APPDATA_APP}/fallback/${FONTNAME}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/res/icon/icon.png" "${APPDATA_APP}/icon.png")

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
