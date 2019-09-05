set(PCRE2_BUILD_PCRE2_8 OFF CACHE BOOL "Build 8bit PCRE2 library")
set(PCRE2_BUILD_PCRE2_32 ON CACHE BOOL "Build 32bit PCRE2 library")

add_subdirectory(3rd/pcre2 EXCLUDE_FROM_ALL)
set(PCRE2_INCLUDE_DIR ${CMAKE_BINARY_DIR}/pcre2/)
set(PCRE2_LIB pcre2-32)

include_directories(${PCRE2_INCLUDE_DIR})
