cmake_minimum_required(VERSION 3.20.0)
project(CMakeSFMLProject LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(CMakeSFMLProject 
            src/main.cpp 
            src/grid.cpp 
            src/shape.cpp 
            src/line.cpp 
            src/algorithm.cpp 
            src/isOnVerts.cpp
            )
            
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics sfml-window sfml-system)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

if(WIN32)
    target_link_options(CMakeSFMLProject PRIVATE -mwindows)
endif(WIN32)

if(UNIX)
    target_link_options(CMakeSFMLProject PRIVATE)
endif(UNIX)

install(TARGETS CMakeSFMLProject)