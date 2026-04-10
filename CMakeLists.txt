cmake_minimum_required(VERSION 3.16)
project(ProgrammingPractice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Collect all exercise test executables automatically.
# Each exercise directory contains a test.cpp that is built as its own target.
file(GLOB_RECURSE EXERCISE_TESTS CONFIGURE_DEPENDS exercises/*/test.cpp)

foreach(TEST_SOURCE ${EXERCISE_TESTS})
    # Derive a unique target name from the path, e.g. algorithms_01_two_sum
    get_filename_component(TEST_DIR ${TEST_SOURCE} DIRECTORY)
    file(RELATIVE_PATH REL_DIR ${CMAKE_SOURCE_DIR}/exercises ${TEST_DIR})
    string(REPLACE "/" "_" TARGET_NAME ${REL_DIR})

    # Gather all .cpp files in the exercise directory (test + solution)
    file(GLOB EXERCISE_SOURCES CONFIGURE_DEPENDS ${TEST_DIR}/*.cpp)

    add_executable(${TARGET_NAME} ${EXERCISE_SOURCES})
    target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include ${TEST_DIR})

    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endforeach()
