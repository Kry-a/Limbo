cmake_minimum_required(VERSION 3.15)
project(Limbo)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED COMPONENTS system)
find_package(Threads REQUIRED)

if(SERVER_LIST)
    add_definitions(-DSERVER_LIST)
endif(SERVER_LIST)

add_executable(Limbo src/main.cpp src/Server.cpp src/Server.hpp src/Session.cpp src/Session.hpp src/utils.hpp src/Buffer.cpp src/Buffer.hpp)
target_include_directories(Limbo PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(Limbo ${Boost_LIBRARIES} Threads::Threads)