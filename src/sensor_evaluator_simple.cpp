#include <vector>
#include <algorithm>

#include "sensor_evaluator_simple.hpp"

auto value_selector = [](auto pair) { return pair.second; };

bool SensorEvaluatorSimple::evaluate() {
  std::vector<bool> values(sensor_states_.size());
  transform(sensor_states_.begin(), sensor_states_.end(), values.begin(), value_selector); 
  return std::count(values.begin(), values.end(), true) > 0;
}
