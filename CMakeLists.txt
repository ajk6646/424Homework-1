# CMakeList.txt : CMake project for Homework 1, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CMakeTarget "Question67.cpp" "Homework 1.h" "Question1.cpp" "Question8.cpp" "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
