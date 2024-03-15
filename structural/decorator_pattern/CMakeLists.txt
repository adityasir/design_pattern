cmake_minimum_required(VERSION 3.10)
project(decoratorHumanFilter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create build directory
set(BUILD_DIR ${CMAKE_BINARY_DIR}/build)
file(MAKE_DIRECTORY ${BUILD_DIR})

# Add compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Add cppcheck static code analysis
find_program(CPPCHECK_EXECUTABLE NAMES cppcheck)
if(CPPCHECK_EXECUTABLE)
    list(APPEND CMAKE_CXX_CPPCHECK "${CPPCHECK_EXECUTABLE};--enable=all")
endif()

# Add executable target
add_executable(decoratorHumanFilter decorator_pattern.cpp)

# Set output directory for build artifacts
set_target_properties(decoratorHumanFilter PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})

# Clean target
#message(STATUS "Build directory: ${BUILD_DIR}")

add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BUILD_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/cmake_install.cmake
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Makefile
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
)
