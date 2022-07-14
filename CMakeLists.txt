cmake_minimum_required(VERSION 3.15)

project(ThiefSnitcher VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# threading
find_package(Threads REQUIRED)

# include pistache library
find_package(PkgConfig)
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)


add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} 
  endpoint tracker util 
  Threads::Threads
  PkgConfig::Pistache
  )


target_compile_options(${PROJECT_NAME} PRIVATE -Wall)