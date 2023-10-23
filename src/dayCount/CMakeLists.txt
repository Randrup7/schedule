add_library(
    dayCount STATIC
    ACT360.cpp
    ACT365.cpp
    ACT365_25.cpp
    ACTACT_ISDA.cpp
    Thrity360E.cpp
    #dayCount.cpp
    #I_dayCount.cpp
)

# Specify library's header file location
target_include_directories(
    dayCount PUBLIC
    "${CMAKE_SOURCE_DIR}/include/dayCount"
)

# Link this target to the date library, to access the date class
target_link_libraries(dayCount PRIVATE time)