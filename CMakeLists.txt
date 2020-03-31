cmake_minimum_required (VERSION 3.5.1)

project(ussuite C CXX)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/" )
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/fc/CMakeModules")

set(CMAKE_BUILD_TYPE DEBUG)

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_EXTENSIONS ON )
set( CXX_STANDARD_REQUIRED ON)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 9)


#set(CMAKE_CXX_COMPILER  clang++-4.0)
#set(CMAKE_C_COMPILER   clang-4.0)

# http://stackoverflow.com/a/18369825
#if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.0)
#        message(FATAL_ERROR "GCC version must be at least 6.0!")
#    endif()
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
#    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.0)
#        message(FATAL_ERROR "Clang version must be at least 4.0!")
#    endif()
#endif()


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()


message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
IF(CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_CXX_FLAGS_DEBUG "-O0")
  message("Debug build.")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
  set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG")
  message("Release build.")
ELSE()
  message("Some other build type.")
ENDIF()


#set(Secp256k1_INCLUDE_DIR  /usr/local/include)
#set(Secp256k1_LIBRARY  /usr/local/lib)

message(STATUS "PROJECT_BINARY_DIR="  ${PROJECT_BINARY_DIR} )
message(STATUS "PROJECT_SOURCE_DIR="  ${PROJECT_SOURCE_DIR} )
message(STATUS "CMAKE_SOURCE_DIR="  ${CMAKE_SOURCE_DIR} )
message(STATUS "CMAKE_MODULE_PATH="  ${CMAKE_MODULE_PATH} )

set(CXX_FLAGS
 -g
 -DCHECK_PTHREAD_RETURN_VALUE
 -D_FILE_OFFSET_BITS=64
 -Wall
 -Wextra
 -Wsign-compare
# -Werror
# -Wconversion
-Wunused-variable
 -Wno-unused-parameter
# -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
# -Wshadow
 -Wwrite-strings
 -march=native
 # -MMD
 #-std=c++14
 -rdynamic
 -pthread
# -fpermissive
# -fPIC
 )


if(CMAKE_BUILD_BITS EQUAL 32)
  list(APPEND CXX_FLAGS "-m32")
endif()



string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK )

FIND_PACKAGE(Boost COMPONENTS  system  filesystem program_options thread log_setup log  REQUIRED)
if(NOT Boost_FOUND)
  message(FATAL_ERROR "Boost log  not found!")
endif(NOT Boost_FOUND)

find_package(ZLIB)

if(ZLIB_FOUND)
  message(STATUS "found zlib")
endif()


include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})

string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

#add_subdirectory(chainbase) 
#add_subdirectory(utilities) 
#add_subdirectory(chain) 
add_subdirectory(uoswallet) 
#add_subdirectory(uskeytool) 



