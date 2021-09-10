cmake_minimum_required(VERSION 3.19)
project(IN_PI42TAS C)

set(CMAKE_C_STANDARD 99)

include(cpm/CPM.cmake)
CPMAddPackage("gh:JeroenVandezande/LowLevelCInterfaces@1.1.0")

add_library(${PROJECT_NAME} IN_PI42TAS.c IN_PI42TAS.h)

target_link_libraries(${PROJECT_NAME} LowLevelCInterfaces)

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})