if(UNIX)
set(COMMON_FLAGS " -Wall -Wno-unused-function -Wno-unused-value -Wno-unused-variable -std=c++0x -pthread -ftree-vectorize -ftree-vectorizer-verbose=1 -Werror -Wno-deprecated-declarations -Wdouble-promotion")

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64" OR 
   ${CMAKE_SYSTEM_PROCESSOR} MATCHES "i686")
message(STATUS "Using SIMD")
set(ARCH_FLAGS " -msse4.2")
add_definitions(-D_UNIX)
endif()
if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64" OR
	${CMAKE_SYSTEM_PROCESSOR} MATCHES "armv7l")
set(ARCH_FLAGS "")
add_definitions(-D_UNIX)
endif()

set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} ${ARCH_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE " -O3")

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64")
add_definitions(-D__i386__)
endif()

endif()

if(WIN32)
# TDOD: Need to set appropriate compiler flags for MSVC
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D__i386__)
endif()

macro(link_compiler_options)
if(MSVC)
 target_compile_options(${PROJECT_NAME} PRIVATE "/MP")
endif()
endmacro()
