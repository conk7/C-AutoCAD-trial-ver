cmake_minimum_required(VERSION 3.20.0)
project(CMakeSFMLProject LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_subdirectory(google)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

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
            src/zoom.cpp)
            
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics sfml-window sfml-system)

if(WIN32)
    target_link_options(CMakeSFMLProject PRIVATE -mwindows)
endif(WIN32)

if(UNIX)
    target_link_options(CMakeSFMLProject PRIVATE)
endif(UNIX)

install(TARGETS CMakeSFMLProject)