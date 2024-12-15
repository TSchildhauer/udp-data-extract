cmake_minimum_required(VERSION 3.5.0)
project(tcp_client VERSION 0.1.0 LANGUAGES C CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Option 1: Include boost from system
# find_package(Boost 1.87.0 REQUIRED COMPONENTS json)

# Option 2: for offline builds: Download boost and extract it to external/
# set(Boost_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/boost_1_87_0)

# Option 3: Fetch boost from git
include(FetchContent)
FetchContent_Declare(
    boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.87.0
)
FetchContent_MakeAvailable(boost)
# add_definitions(-DBOOST_ALL_NO_LIB)

# # Option 4: Boost as submodule from git.
# set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/external/boost)

# # Include Boost headers (it is header-only for json/asio)
# add_library(Boost INTERFACE)
# target_include_directories(Boost INTERFACE ${BOOST_ROOT})

# # Ensure Boost is initialized and available
# if (NOT EXISTS "${BOOST_ROOT}/boost/json.hpp")
#     message(FATAL_ERROR "Boost submodule is not initialized. Run 'git submodule update --init --recursive'.")
# endif()

# Find pthread for POSIX threading
find_package(Threads REQUIRED)

add_executable(client1 src/client.cpp src/aggregate.cpp src/main.cpp)

# Include Boost headers
target_include_directories(client1 PRIVATE include ${boost_SOURCE_DIR})

# Link posix libraries that boost wants to use
target_link_libraries(client1 PRIVATE Threads::Threads)

# Add standalone json support
# target_compile_definitions(client1 PRIVATE BOOST_JSON_STANDALONE)

# Add testing support
#include(CTest)
#enable_testing()

