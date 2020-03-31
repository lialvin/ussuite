
include_directories(${PROJECT_SOURCE_DIR}/fc/include)
include_directories(${PROJECT_SOURCE_DIR}/include   ${PROJECT_SOURCE_DIR}/dappserv )

link_directories(${PROJECT_BINARY_DIR}/lib  /usr/local/lib)


#ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
set(MAIN_SRC_LIST
 uskeytool.cpp time_deal.hpp
  )

set(MAIN_HEADERS
  uskeytool.h
)

#file(GLOB HEADERS "*.h")
#add_library(ethcore ${SRC_LIST} ${HEADERS})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#add_executable(testma ${APP_SRC})

set(IMPORTLIB 
    pthread  boost_system boost_filesystem boost_program_options boost_thread boost_thread boost_chrono boost_date_time 
     gmp  crypto 
)

#link_libraries(“/home/server/third/lib/libcommon.a”)
link_libraries(${PROJECT_BINARY_DIR}/lib/libfc_debug.a)
link_libraries(${PROJECT_BINARY_DIR}/lib/libsecp256k1.a)
add_executable(uskeytool ${MAIN_SRC_LIST}  ${MAIN_HEADERS})
target_link_libraries(uskeytool ${IMPORTLIB} )

