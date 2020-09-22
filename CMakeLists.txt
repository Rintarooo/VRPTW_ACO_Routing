cmake_minimum_required(VERSION 3.1)
project(project_name_whatever CXX)

# activate c++11
set(CMAKE_CXX_STANDARD 11)

# set(CMAKE_CXX_FLAGS "-O2 -std=c++11 -Wall -g")
# -g is debugger, -Wall is Warning, -O2 is Optimization
# https://qiita.com/shohirose/items/637f4b712893764a7ec1
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -g")

add_subdirectory(src)

add_executable(main.exe main.cpp)
target_link_libraries(main.exe greetings)
message("absolute path: ${PROJECT_SOURCE_DIR}")
