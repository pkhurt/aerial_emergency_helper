cmake_minimum_required (VERSION 2.6)
project (aerial_emergency_helper)
find_package( OpenCV REQUIRED )
add_executable(aerial_emergency_helper main.cpp)
target_link_libraries( aerial_emergency_helper ${OpenCV_LIBS} )
