cmake_minimum_required(VERSION 3.5.0)
project(tcp_client VERSION 0.1.0 LANGUAGES C CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(client1 src/client1.cpp)

# Include Boost headers
target_include_directories(client1 PRIVATE ${Boost_INCLUDE_DIRS})


# Add testing support
#include(CTest)
#enable_testing()

