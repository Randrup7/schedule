add_library(
    calendars STATIC
    DKCO.cpp
    TARGET.cpp
    jointCalendar.cpp
    noCalendar.cpp
    holidayFunctions.cpp
)

# Specify library's header file location
target_include_directories(
    calendars PUBLIC
    "${CMAKE_SOURCE_DIR}/include/calendars"
)

# Link this target to the date library, to access the date class
target_link_libraries(calendars PRIVATE time)