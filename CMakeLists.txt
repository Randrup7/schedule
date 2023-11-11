cmake_minimum_required(VERSION 3.24.2)

project(Main 
        VERSION 1.0.0
        DESCRIPTION "optional description of project"
        LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

add_compile_options(
       -Wall -Werror 
       $<$<CONFIG:RELEASE>:-O2>
       $<$<CONFIG:DEBUG>:-O0>
       $<$<CONFIG:DEBUG>:-ggdb3>
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)

# Linking library targets to executable target ${PROJECT_NAME}
target_link_libraries(${PROJECT_NAME} PRIVATE time)
target_link_libraries(${PROJECT_NAME} PRIVATE calendars)
target_link_libraries(${PROJECT_NAME} PRIVATE schedule)
target_link_libraries(${PROJECT_NAME} PRIVATE dayCount)
target_link_libraries(${PROJECT_NAME} PRIVATE interpolate)
