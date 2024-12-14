cmake_minimum_required(VERSION 3.5.0)
project(tcp_client VERSION 0.1.0 LANGUAGES C CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Use FetchContent to include Boost
include(FetchContent)
FetchContent_Declare(
    boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.87.0
)

# Ensure Boost is downloaded and available
FetchContent_MakeAvailable(boost)

# Find pthread for POSIX threading
find_package(Threads REQUIRED)

add_executable(client1 src/client.cpp src/aggregate.cpp src/main.cpp)

# Include Boost headers
target_include_directories(client1 PRIVATE include ${Boost_INCLUDE_DIRS})

# Link posix libraries that boost wants to use
target_link_libraries(client1 PRIVATE Threads::Threads)

# Add testing support
#include(CTest)
#enable_testing()

