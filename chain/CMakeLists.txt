cmake_minimum_required(VERSION 3.5)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/uosio/chain/core_symbol.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/include/uosio/chain/core_symbol.hpp)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/genesis_state_root_key.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/genesis_state_root_key.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include )
include_directories(${PROJECT_SOURCE_DIR}/fc/include/)

file(GLOB HEADERS "include/uosio/chain/*.hpp"
                  "${CMAKE_CURRENT_BINARY_DIR}/include/uosio/chain/core_symbol.hpp" )

## SORT .cpp by most likely to change / break compile
add_library( uosio_chain
             merkle.cpp
             name.cpp
             transaction.cpp
             block_header.cpp
             block_header_state.cpp
             block_state.cpp
             fork_database.cpp
             resource_limits.cpp
             block_log.cpp
             chain_config.cpp
             chain_id_type.cpp
             genesis_state.cpp
             ${CMAKE_CURRENT_BINARY_DIR}/genesis_state_root_key.cpp


#             get_config.cpp
#             global_property_object.cpp
#
#             contracts/chain_initializer.cpp


#             transaction_metadata.cpp
             ${HEADERS}
             )

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../lib)

target_link_libraries( uosio_chain uos_utilities fc chainbase Logging  Runtime
      s passes cfg ast emscripten-optimizer support softfloat builtins wabt
                     )

target_include_directories( uosio_chain
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include"
                            )

#install( TARGETS uosio_chain
#   RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
#   LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
#   ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
#)
# install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/uosio/chain/
#      DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/uosio/chain
#      FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h" PATTERN "webassembly" EXCLUDE
#)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/uosio/chain/core_symbol.hpp DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/uosio/chain)

