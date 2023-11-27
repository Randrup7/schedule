add_subdirectory(time)
add_subdirectory(calendars)
add_subdirectory(schedule)
add_subdirectory(dayCount)
add_subdirectory(interpolate)


# Make library with the date class for use in libraries dayCount and Schedule
add_library(
    rates STATIC
    interestRate.cpp
    #forwardRate.cpp
    )

# Specify library's header file location
target_include_directories(
    rates PUBLIC
    "${CMAKE_SOURCE_DIR}/include"
)

# Link this target to the date library, to access the date class
target_link_libraries(rates PRIVATE time)
target_link_libraries(rates PRIVATE calendars)
target_link_libraries(rates PRIVATE schedule)
target_link_libraries(rates PRIVATE dayCount)
target_link_libraries(rates PRIVATE interpolate)