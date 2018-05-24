cmake_minimum_required(VERSION 2.8)
project(lab6)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -ggdb")

find_package(GTest REQUIRED)
include_directories(include ${GTEST_INCLUDE_DIRS})
set(ALGSOURCE src/bohr.cpp  src/ahocorasick.cpp)
set(TESTSOURCE src/lab6tests.cpp)
set(SOURCE src/lab6.cpp)
set(JOKERSOURCE src/lab6joker.cpp)

add_executable(lab6 ${SOURCE} ${ALGSOURCE})

add_executable(lab6joker ${JOKERSOURCE} ${ALGSOURCE})

add_executable(lab6test ${TESTSOURCE} ${ALGSOURCE})
target_link_libraries(lab6test ${GTEST_LIBRARIES} pthread)
enable_testing()
add_test(lab6test "./lab6test")
