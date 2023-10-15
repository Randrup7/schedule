# Make library with the date class for use in libraries dayCount and Schedule
add_library(
    time STATIC
    date.cpp
    interval.cpp
    )

# Specify library's header file location
target_include_directories(
    time PUBLIC
    "${CMAKE_SOURCE_DIR}/include/time"
)