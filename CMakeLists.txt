cmake_minimum_required(VERSION 3.5.0)
project(tcp_client VERSION 0.1.0 LANGUAGES C CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include boost from system
find_package(Boost 1.75.0 REQUIRED COMPONENTS json system)

# Find pthread for POSIX threading
find_package(Threads REQUIRED)

add_executable(client1 src/client.cpp src/aggregate.cpp src/client1_main.cpp)

# Include Boost headers
target_include_directories(client1 PRIVATE include ${Boost_INCLUDE_DIRS})

# Link posix libraries that boost wants to use
target_link_libraries(client1 PRIVATE Threads::Threads Boost::json)

# Add standalone json support
# target_compile_definitions(client1 PRIVATE BOOST_JSON_STANDALONE)

## Client 2
add_executable(client2 src/client.cpp src/aggregate.cpp src/client2_main.cpp)

# Include Boost headers
target_include_directories(client2 PRIVATE include ${Boost_INCLUDE_DIRS})

# Link posix libraries that boost wants to use
target_link_libraries(client2 PRIVATE Threads::Threads Boost::json)

# Add standalone json support
# target_compile_definitions(client2 PRIVATE BOOST_JSON_STANDALONE)

# Add testing support
#include(CTest)
#enable_testing()

