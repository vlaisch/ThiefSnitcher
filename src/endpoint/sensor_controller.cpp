#include "sensor_controller.hpp"

SensorController::SensorController(MsgQueue<MonitoringMsg> *queue) {
  msg_queue_ = queue;
}