#list( APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/libraries/fc/GitVersionGen" )
#include( GetGitRevisionDescription )
#get_git_head_revision(GIT_REFSPEC UOS_GIT_REVISION_SHA)
#get_git_unix_timestamp(UOS_GIT_REVISION_UNIX_TIMESTAMP)
#git_describe(UOS_GIT_REVISION_DESCRIPTION --tags)
cmake_minimum_required(VERSION 3.5)

include_directories(${PROJECT_SOURCE_DIR}/include )
include_directories(${PROJECT_SOURCE_DIR}/fc/include/)

message("PROJECT_SOURCE_DIR= ${PROJECT_SOURCE_DIR}")

link_directories(${PROJECT_BINARY_DIR}/lib  /usr/local/lib)

if(NOT UOS_GIT_REVISION_DESCRIPTION)
    set(UOS_GIT_REVISION_DESCRIPTION "unknown")
endif(NOT UOS_GIT_REVISION_DESCRIPTION)

file(GLOB HEADERS "include/uosio/utilities/*.hpp")

set(sources
   key_conversion.cpp
   string_escape.cpp
   tempdir.cpp
   words.cpp
   ${HEADERS})

#configure_file("${CMAKE_CURRENT_SOURCE_DIR}/git_revision.cpp.in" "${CMAKE_CURRENT_BINARY_DIR}/git_revision.cpp" @ONLY)
#list(APPEND sources "${CMAKE_CURRENT_BINARY_DIR}/git_revision.cpp")

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../lib)

add_library( uos_utilities
             ${sources}
             ${HEADERS} )
target_link_libraries( uos_utilities fc  )
target_include_directories( uos_utilities
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
       )

if (USE_PCH)
  set_target_properties(uos_utilities PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
  cotire(uos_utilities)
endif(USE_PCH)

