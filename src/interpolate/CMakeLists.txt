add_library(
    interpolate STATIC
    I_interpolate.cpp
    hermite.cpp
    hyman.cpp
)

# Specify library's header file location
target_include_directories(
    interpolate PUBLIC
    "${CMAKE_SOURCE_DIR}/include/interpolate"
)