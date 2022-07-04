cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

project(
    date-homework
    DESCRIPTION "basic implementation of c++ idioms"
    LANGUAGES CXX C)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ${CMAKE_PREFIX_PATH})

add_subdirectory(src)

option(ENABLE_TESTING "Enable the tests" ON)

if(ENABLE_TESTING)
  enable_testing()
  message("Building Tests.")
  add_subdirectory(test)
endif()

