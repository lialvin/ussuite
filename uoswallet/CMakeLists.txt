
include_directories(${PROJECT_SOURCE_DIR}/fc/include)
include_directories(${PROJECT_SOURCE_DIR}/include   ${PROJECT_SOURCE_DIR}/uoswallet )

link_directories(${PROJECT_BINARY_DIR}/lib  /usr/local/lib)

find_package(OpenSSL)
if(NOT OPENSSL_FOUND)
  message(FATAL_ERROR "OpenSSL not found!")
endif(NOT OPENSSL_FOUND)

#ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
set(MAIN_SRC_LIST
 uoswallet.cpp
 wallet.cpp
 wallet_mgr.cpp
  )

set(MAIN_HEADERS
  uoswallet.h
  wallet.hpp 
  wallet_mgr.hpp
)

#file(GLOB HEADERS "*.h")
#add_library(ethcore ${SRC_LIST} ${HEADERS})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#add_executable(testma ${APP_SRC})

set(IMPORTLIB 
 pthread  secp256k1_debug  ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY}   boost_system boost_filesystem boost_program_options boost_thread boost_thread boost_chrono boost_date_time gmp 

)

#link_libraries(“/home/server/third/lib/libcommon.a”)
link_libraries(${PROJECT_BINARY_DIR}/lib/libfc_debug.a)
link_libraries(${PROJECT_BINARY_DIR}/lib/libuosio_chain.a)
#link_libraries(libfc_debug.a)
add_executable(uoswallet ${MAIN_SRC_LIST}  ${MAIN_HEADERS})
target_link_libraries(uoswallet ${IMPORTLIB} )
