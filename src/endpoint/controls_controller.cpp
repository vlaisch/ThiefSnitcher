#include "controls_controller.hpp"

ControlsController::ControlsController(MsgQueue<MonitoringMsg> *queue) {
  msg_queue_ = queue;
}

void ControlsController::arm(const Rest::Request& req, Http::ResponseWriter response) {
  MonitoringMsg msg = {MonitoringCmd::controlsArm};
  msg_queue_->enqueue(msg);
  response.send(Http::Code::Ok);
}

void ControlsController::disarm(const Rest::Request& req, Http::ResponseWriter response) {
  MonitoringMsg msg = {MonitoringCmd::controlsDisarm};
  msg_queue_->enqueue(msg);
  response.send(Http::Code::Ok);
}