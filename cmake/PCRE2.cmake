set(PCRE2_BUILD_PCRE2_8 OFF CACHE BOOL "Build 8bit PCRE2 library")
set(PCRE2_BUILD_PCRE2_32 ON CACHE BOOL "Build 32bit PCRE2 library")

find_library(PCRE2_LIB pcre2-32)
find_path(PCRE2_INCLUDE_DIR pcre2.h)
add_subdirectory(3rd/pcre2 EXCLUDE_FROM_ALL)

set(PCRE2_LIB pcre2-32)
include_directories(${PCRE2_INCLUDE_DIR})
