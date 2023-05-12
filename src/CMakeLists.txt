add_library(
    date STATIC
    date.cpp
    dayAdjustment.cpp
    dayCount.cpp
    schedule.cpp
    stub.cpp
)

# Specify library's header file location
target_include_directories(
    date PUBLIC
    "${CMAKE_SOURCE_DIR}/include"
)
