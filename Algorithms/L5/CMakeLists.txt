cmake_minimum_required(VERSION 2.6)
project(lab5)

find_package(GTest REQUIRED)
include_directories(include ${GTEST_INCLUDE_DIRS})
set (SOURCE src/lab5.cpp src/kmp.cpp src/prefix.cpp)
set (TESTSOURCE src/lab5test.cpp src/kmp.cpp src/prefix.cpp)

add_executable(lab5 ${SOURCE})

if (tests)
    add_executable(lab5test ${TESTSOURCE})
    target_link_libraries(lab5test ${GTEST_LIBRARIES} pthread)
    enable_testing()
    add_test(lab5test "./lab5test")
endif()
