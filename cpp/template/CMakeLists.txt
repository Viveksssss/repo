cmake_minimum_required(VERSION 3.10)
project(Project_threads)

set(CMAKE_CXX_STANDARD 23)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)

add_executable(main thread_pool.cpp)
    