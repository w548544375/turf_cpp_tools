cmake_minimum_required(VERSION 3.26)
include(ExternalProject)

project(SephirothServer VERSION 1.0.1)

set(LUA_VERSION "lua-5.4.4")

ExternalProject_Add(
  lua
  URL https://www.lua.org/ftp/${LUA_VERSION}.tar.gz
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND make all MYCFLAGS=-fPIC
  BUILD_IN_SOURCE true
  BUILD_ALWAYS true
  INSTALL_COMMAND "")

ExternalProject_Add(
  skynet
  GIT_REPOSITORY "https://github.com/cloudwu/skynet.git"
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}
  BUILD_IN_SOURCE true
  CONFIGURE_COMMAND ""
  BUILD_ALWAYS true
  BUILD_COMMAND make linux
  INSTALL_COMMAND "")

add_library(liblua STATIC IMPORTED)

ExternalProject_Get_Property(lua SOURCE_DIR)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)
set(OPENSSL_USE_STATIC_LIBS TRUE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/seplibs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/seplibs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall --std=c++11 -O3 -fPIC")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -fPIC")

aux_source_directory(./src SOURCE_FILES)

# add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
set_target_properties(liblua PROPERTIES IMPORTED_LOCATION
                                        ${SOURCE_DIR}/src/liblua.a)

# add_executable(${PROJECT_NAME} ${SOURCE_FILES} main.cpp)
#
# set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 1.0.0 SOVERSION 1)
#
# configure_file(Config.h.in Config.h)
#
# target_include_directories( ${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}"
# "${PROJECT_SOURCE_DIR}/include")
#
# target_include_directories(${PROJECT_NAME} PUBLIC "${SOURCE_DIR}/src")
#
# target_link_libraries(${PROJECT_NAME} liblua)

# #########################################libsephiroth###############################
find_package(OpenSSL REQUIRED)

add_library(sephiroth SHARED ${SOURCE_FILES})

set_target_properties(sephiroth PROPERTIES PREFIX "")
# set_target_properties(sephiroth PROPERTIES LIBRARY_OUTPUT_NAME basephiroth)
set_target_properties(sephiroth PROPERTIES POSITION_INDEPENDENT_CODE True)

target_include_directories(sephiroth PUBLIC "${PROJECT_BINARY_DIR}"
                                            "${PROJECT_SOURCE_DIR}/include")
target_include_directories(sephiroth PRIVATE ${OPENSSL_INCLUDE_DIR})
target_include_directories(sephiroth PUBLIC "${SOURCE_DIR}/src")

configure_file(Config.h.in Config.h)

target_link_libraries(sephiroth PRIVATE liblua OpenSSL::Crypto OpenSSL::SSL)
set(COPY_TARGET ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})
set(SKYNET_CSERVICE ${COPY_TARGET}/cservice)
set(SKYNET_SERVICE ${COPY_TARGET}/service)
set(SKYNET_LUALIB ${COPY_TARGET}/lualib)
set(SKYNET_LUACLIB ${COPY_TARGET}/luaclib)
ExternalProject_Get_Property(skynet SOURCE_DIR)

add_custom_target(
  copy_files ALL
  VERBATIM
  COMMAND ${CMAKE_COMMAND} -E make_directory ${SKYNET_CSERVICE}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${SKYNET_SERVICE}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${SKYNET_LUALIB}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${SKYNET_CSERVICE}
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${SOURCE_DIR}/cservice"
          "${SKYNET_CSERVICE}"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${SOURCE_DIR}/service"
          "${SKYNET_SERVICE}"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${SOURCE_DIR}/lualib"
          "${SKYNET_LUALIB}"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${SOURCE_DIR}/luaclib"
          "${SKYNET_LUACLIB}"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SOURCE_DIR}/skynet"
          "${COPY_TARGET}"
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${CMAKE_CURRENT_SOURCE_DIR}/scripts" "${COPY_TARGET}/scripts"
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${CMAKE_CURRENT_SOURCE_DIR}/config" "${COPY_TARGET}/config")

add_dependencies(sephiroth liblua OpenSSL::Crypto OpenSSL::SSL)