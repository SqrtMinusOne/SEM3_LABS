cmake_minimum_required(VERSION 2.8)
project(lab6)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -ggdb")

find_package(GTest REQUIRED)
include_directories(include ${GTEST_INCLUDE_DIRS})
set(TESTSOURCE src/bohr.cpp src/lab6tests.cpp src/ahocorasick.cpp)
set(SOURCE src/bohr.cpp src/lab6.cpp src/ahocorasick.cpp)

add_executable(lab6 ${SOURCE})

# add_executable(lab6test ${TESTSOURCE})
# target_link_libraries(lab6test ${GTEST_LIBRARIES} pthread)
# enable_testing()
# add_test(lab6test "./lab6test")