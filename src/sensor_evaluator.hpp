#pragma once

#include <unordered_map>

#include "util/monitoring_msg.hpp"
#include "util/sensor.hpp"

class SensorEvaluator {
  public:
    virtual ~SensorEvaluator() {}
    void addSensor(Sensor);
    void update(std::string, bool);
    void clearAll();
    virtual bool evaluate() = 0;

  protected:
    std::unordered_map<std::string, Sensor> sensors_;
    std::unordered_map<std::string, bool> sensor_states_;
};