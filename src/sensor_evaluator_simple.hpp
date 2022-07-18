#pragma once

#include "sensor_evaluator.hpp"

class SensorEvaluatorSimple : public SensorEvaluator {
  public:
    bool evaluate() override;
};