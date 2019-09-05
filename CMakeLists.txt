cmake_minimum_required(VERSION 2.8)
project(nlpxx)
set(CMAKE_CXX_STANDARD 17)

include(cmake/PCRE2.cmake)

file(GLOB HEADERS src/nlpxx.h)
file(GLOB STEM_HEADERS src/stem/*.h)
file(GLOB STEM_SOURCES src/stem/*.cpp)
file(GLOB UTILS_HEADERS src/utils/*.h)
file(GLOB UTILS_SOURCES src/utils/*.cpp)

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${STEM_HEADERS} ${STEM_SOURCES} ${UTILS_HEADERS} ${UTILS_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PCRE2_LIB})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})
install(FILES ${STEM_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/stem)
install(FILES ${UTILS_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/utils)

file(GLOB TEST_HEADERS test/*.h)
add_executable(Tests test/tests.cpp ${TEST_HEADERS})
target_link_libraries(Tests gtest)
target_link_libraries(Tests ${PROJECT_NAME})
