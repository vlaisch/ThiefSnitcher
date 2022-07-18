add_subdirectory(util)
add_subdirectory(tracker)

add_executable(${PROJECT_NAME}
  main.cpp
  monitoring_system.cpp
  monitoring_system.hpp
  rest_endpoint.cpp
  rest_endpoint.hpp
  sensor_evaluator.cpp
  sensor_evaluator.hpp
  sensor_evaluator_simple.cpp
  sensor_evaluator_simple.hpp
  )
