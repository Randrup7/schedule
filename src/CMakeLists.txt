# Make library with the date class for use in libraries dayCount and Schedule
add_library(
    date STATIC
    date.cpp
    )

# Specify library's header file location
target_include_directories(
    date PUBLIC
    "${CMAKE_SOURCE_DIR}/include"
)

add_subdirectory(schedule)
add_subdirectory(dayCount)