add_subdirectory(endpoint)
add_subdirectory(util)
add_subdirectory(tracker)

add_executable(${PROJECT_NAME}
  main.cpp
  monitoring_system.cpp
  monitoring_system.hpp
  )
