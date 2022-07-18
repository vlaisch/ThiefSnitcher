#include "sensor_evaluator.hpp"

void SensorEvaluator::addSensor(Sensor sensor) {
  std::string name = sensor.name;

  if (sensors_.find(name) != sensors_.end()) {
    throw std::runtime_error("Error in configuration: 2 or more sensors have the same name.");
  }

  sensors_.insert(std::pair<std::string, Sensor>(name, sensor));
  sensor_states_[name] = false;
}

void SensorEvaluator::update(std::string name, bool alert) {
  sensor_states_[name] = alert;
}

void SensorEvaluator::clearAll() {
  for (auto& [_, value] : sensor_states_) {
    value = false;
  }
}