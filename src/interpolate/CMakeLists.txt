add_library(
    interpolate STATIC
    I_interpolate.cpp
    hermite.cpp
    hyman.cpp
    linear.cpp
    loglinear.cpp
)

# Specify library's header file location
target_include_directories(
    interpolate PUBLIC
    "${CMAKE_SOURCE_DIR}/include/interpolate"
)

# Link this target to the date library, to access the date class
target_link_libraries(interpolate PRIVATE time)