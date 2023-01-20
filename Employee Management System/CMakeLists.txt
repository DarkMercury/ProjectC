cmake_minimum_required(VERSION 3.0)

project(Employee_Management_System)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall" )  

set(CNAKE_BUILD_TYPE Debug)

add_executable(manage_sys main.cpp src/boss.cpp src/employee.cpp src/Manager.cpp src/worker.cpp src/workerManager.cpp)