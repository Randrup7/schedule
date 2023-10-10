add_library(
    schedule STATIC
    dayAdjustment.cpp
    schedule.cpp
    stub.cpp
    holidayCalendar.cpp
)

# Specify library's header file location
target_include_directories(
    schedule PUBLIC
    "${CMAKE_SOURCE_DIR}/include/schedule"
)

# Link this target to the date library, to access the date class
target_link_libraries(schedule PRIVATE date)