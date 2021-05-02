cmake_minimum_required(VERSION 3.10)

# set the project name
project(RandomNumberInterface)

message(STATUS ${CMAKE_GENERATOR})
message(STATUS ${CMAKE_CXX_COMPILER_ID})
message(STATUS ${CMAKE_SYSTEM_PROCESSOR})

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

include(cmake/compiler.cmake)

set(GTEST_DIR "thirdParty/googletest/includes/googletest/include/gtest")

file(GLOB SOURCES "src/*.cpp")
file(GLOB INCLUDE "includes/*.hpp" "includes/*.h")
file(GLOB TEST_SOURCES "tests/*.cpp")
file(GLOB TEST_INCLUDE "tests/*.hpp" "includes/*.h")
file(GLOB GTEST_INC "${GTEST_DIR}/*.h")

set(INCLUDES ${INCLUDE})
set(SRC ${SOURCES})
set(GTEST_SRC ${GTEST_INC})
set(TEST_SRC ${TEST_SOURCES} ${TEST_INCLUDE})

include_directories(${INCLUDES}
    ${GTEST_DIR})

if(UNIX)
    find_package(PkgConfig REQUIRED)
endif()

# add the executable
add_executable(${PROJECT_NAME}
    ${SRC}
    ${INCLUDES}
    ${GTEST_SRC}
    ${TEST_SRC})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()
if(UNIX)
    target_link_libraries(${PROJECT_NAME})
endif()