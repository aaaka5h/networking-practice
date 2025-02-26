cmake_minimum_required(VERSION 3.20)

project(c-threading LANGUAGES C)

add_library(compute compute.c)
target_include_directories(compute PUBLIC ${CMAKE_SOURCE_DIR})

find_package(Threads REQUIRED)
add_executable(main main.c)
target_link_libraries(main PRIVATE Threads::Threads compute)
