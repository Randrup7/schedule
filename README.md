# Schedule
A C++ library to create financial schedules for fixed income securities.

The project has an include folder containing header files and a src folder containing .cpp files.

The main class of the project in the schedule class. At construction, it creates a schedule of payment dates given the inputs.
The library is (currently) split into three libraries:
1. A time library defining dates, intervals and date manipulation functionality.
2. A daycount library defining different daycount calculations (not needed in creation of schedule)
3. A schedule library defining different stuc conventions, day adjustment conventions, holiday calendars and more.

## Possible future add-ons:
- Implement more calendars
- More day adjustment types
- More constructors
- More daycounts
- Better implementation of business days. E.g. date manipulation with business days.


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
