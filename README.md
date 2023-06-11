# Schedule
A C++ library to create financial schedules for fixed income securities.

The project has an include folder containing header files and a src folder containing .cpp files.

The main class of the project in the schedule class. At construction, it creates a schedule of payment dates given the inputs.
The schedule class is dependent on the classes finDate, dayAdjustment, stub class and calendar class. This means the schedule can take into account different businessday adjustment conventions and different stub conventions.

## Possible future add-ons:
- Implement a frequency class to handle different coupon intervals, e.g. also allow zero coupons
- Implement more calendars
- More day adjustment types
- More constructors 


# Building
Build by making a build directory (i.e. build/), run cmake in that dir, and then use make to build the desired target.

Example:
```console
> mkdir build
> cd build
> cmake ..
> make
> ./../main
```
