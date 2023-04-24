cmake_minimum_required(VERSION 3.26)
include(ExternalProject)

project(SephirothServer VERSION 1.0.1)

set(LUA_VERSION "lua-5.4.4")

ExternalProject_Add(
  lua
  URL https://www.lua.org/ftp/${LUA_VERSION}.tar.gz
  # DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}/download/lua
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/lua
  CONFIGURE_COMMAND ""
  BUILD_COMMAND make all MYCFLAGS=-fPIC
  BUILD_IN_SOURCE true
  BUILD_ALWAYS true
  INSTALL_COMMAND "")

add_library(liblua STATIC IMPORTED)

ExternalProject_Get_Property(lua SOURCE_DIR)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall --std=c++11 -O3 -fPIC")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -fPIC")

aux_source_directory(./src SOURCE_FILES)

# add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
set_target_properties(liblua PROPERTIES IMPORTED_LOCATION
                                        ${SOURCE_DIR}/src/liblua.a)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 1.0.0 SOVERSION 1)

configure_file(Config.h.in Config.h)

target_include_directories(
  ${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}"
                         "${PROJECT_SOURCE_DIR}/include")

target_include_directories(${PROJECT_NAME} PUBLIC "${SOURCE_DIR}/src")

target_link_libraries(${PROJECT_NAME} liblua)

# #########################################libbuffer###############################
add_library(buffer SHARED ${SOURCE_FILES} lua_buffer.cpp)

set_target_properties(buffer PROPERTIES PREFIX "")
# set_target_properties(buffer PROPERTIES LIBRARY_OUTPUT_NAME babuffer)
set_target_properties(buffer PROPERTIES POSITION_INDEPENDENT_CODE True)

target_include_directories(buffer PUBLIC "${PROJECT_BINARY_DIR}"
                                         "${PROJECT_SOURCE_DIR}/include")

target_include_directories(buffer PUBLIC "${SOURCE_DIR}/src")

target_link_libraries(buffer liblua)
