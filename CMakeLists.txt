cmake_minimum_required(VERSION 3.20.0)
project(CMakeSFMLProject LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_subdirectory(google)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Test_grid_run tests/gridtest.cpp src/grid.cpp)
target_link_libraries(Google_Test_grid_run gtest gtest_main)
target_link_libraries(Google_Test_grid_run gmock)

add_executable(Google_Test_polygons_run tests/polygonstest.cpp src/polygons.cpp)
target_link_libraries(Google_Test_polygons_run gtest gtest_main)
target_link_libraries(Google_Test_polygons_run gmock)

add_executable(Google_Test_mouse_run tests/mousetest.cpp src/mouse.cpp)
target_link_libraries(Google_Test_mouse_run gtest gtest_main)
target_link_libraries(Google_Test_mouse_run gmock)

add_executable(Google_Test_line_run tests/linetest.cpp  src/line.cpp )
target_link_libraries(Google_Test_line_run gtest gtest_main)
target_link_libraries(Google_Test_line_run gmock)

add_executable(Google_Test_zoom_run tests/zoomtest.cpp src/zoom.cpp)
target_link_libraries(Google_Test_zoom_run gtest gtest_main)
target_link_libraries(Google_Test_zoom_run gmock)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(CMakeSFMLProject 
            src/main.cpp 
            src/grid.cpp 
            src/polygon.cpp 
            src/polygons.cpp 
            src/line.cpp 
            src/algorithm.cpp 
            src/movingVert.cpp
            src/mouse.cpp
            src/zoom.cpp
            )
            
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics sfml-window sfml-system)

if(WIN32)
    target_link_options(CMakeSFMLProject PRIVATE -mwindows)
endif(WIN32)

if(UNIX)
    target_link_options(CMakeSFMLProject PRIVATE)
endif(UNIX)

install(TARGETS CMakeSFMLProject)