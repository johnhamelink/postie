# Project-specific config
cmake_minimum_required(VERSION 2.8)
project(POSTIE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/priv)
file(GLOB POSTIE_SRC src/*.c)

# Compiler Settings
SET (CMAKE_C_FLAGS "-g -O3 -pedantic -Wall -Wextra -Wno-unused-parameter -std=c99 -undefined dynamic_lookup -dynamiclib")

# Include more Cmake code to find other libs
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(${CMAKE_SOURCE_DIR}/cmake/FindErlang.cmake)

# Find Erlang using FindErlang.cmake
find_package(Erlang  REQUIRED)

# Use pkg-config to find libpostal
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPOSTAL REQUIRED libpostal)

include_directories(
  SYSTEM
  ${Erlang_EI_INCLUDE_DIR}
  ${Erlang_EI_DIR}/src
  ${LIBPOSTAL_INCLUDE_DIRS}
)


link_directories(
  ${Erlang_EI_LIBRARY_DIR}
  ${LIBPOSTAL_LIBRARY_DIRS}
)

add_executable(postie.so ${POSTIE_SRC})
target_link_libraries(postie.so ${Erlang_EI_LIBRARIES})
target_link_libraries(postie.so ${LIBPOSTAL_LIBRARIES})
