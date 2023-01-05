# using pd.build https://github.com/pierreguillot/pd.build

cmake_minimum_required(VERSION 3.0)

set(CMAKE_SUPPRESS_REGENERATION true)

include(pd.build/pd.cmake)

# Set the project name
project(leapmotion)

# Set the path to Pure Data sources:
set_pd_sources("C:/Program Files/Pd/src")

# Set the output path for the externals:
set_pd_external_path(build)

# Set include paths (leamotion\include and LeapSDK\include). Note that forward slashes are required here
file(GLOB leapmotion_includes include "C:/msys64/dev/LeapDeveloperKit_2.3.1+31549_win/LeapSDK/include")
include_directories("${leapmotion_includes}")

# Add sources for the external (again, using forward slashes)
file(GLOB leapmotion_sources src/leapmotion.cpp src/Dispatcher.cpp src/LeapMotionObj.cpp)
add_pd_external(leapmotion leapmotion "${leapmotion_sources}")

# Define the Leap library for linking and provide its path using forward slashes
find_library(LEAP_LIBRARY NAMES Leap HINTS "C:/msys64/dev/LeapDeveloperKit_2.3.1+31549_win/LeapSDK/lib/x64")
target_link_libraries(leapmotion ${LEAP_LIBRARY})
