cmake_minimum_required(VERSION 2.8)
project(NLPXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB HEADERS src/nlpxx.h)
file(GLOB STEM_HEADERS src/stem/*.h)
file(GLOB STEM_SOURCES src/stem/*.cpp)

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${STEM_HEADERS} ${STEM_SOURCES})
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/nlpxx)
install(FILES ${STEM_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/nlpxx/stem)

add_executable(Tests test/tests.cpp)
target_link_libraries(Tests gtest)
target_link_libraries(Tests ${PROJECT_NAME})
