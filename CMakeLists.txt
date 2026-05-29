cmake_minimum_required(VERSION 3.15)
project(PM_LAB3)

set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "Build architecture for macOS")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

include_directories(
    ${Boost_INCLUDE_DIRS}
)

add_executable(pm_lab3
    src/main.cpp 
    src/ModifiedLCG.cpp
    src/Timer.cpp
    src/ModifiedXorShift.cpp
    src/ModifiedMiddleSquare.cpp
    src/Statistics.cpp
    src/RandomTests.cpp
)

target_include_directories(pm_lab3 PRIVATE src)
