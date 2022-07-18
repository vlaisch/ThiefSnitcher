cmake_minimum_required(VERSION 3.15)

project(ThiefSnitcher VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig)

# yaml
include(FetchContent)

FetchContent_Declare(yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git)

FetchContent_GetProperties(yaml-cpp)
if(NOT yaml-cpp_POPULATED)
  FetchContent_Populate(yaml-cpp)
  add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# threading
find_package(Threads REQUIRED)

# include pistache library
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)


add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} 
  tracker util 
  Threads::Threads
  PkgConfig::Pistache
  yaml-cpp::yaml-cpp
  )

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)