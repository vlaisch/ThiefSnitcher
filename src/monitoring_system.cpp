#include <chrono>
#include <thread>

#include "monitoring_system.hpp"

MonitoringSystem::MonitoringSystem(ThiefTracker *tracker, MsgQueue<MonitoringMsg> *queue) {
  tracker_ = tracker;
  msg_queue_ = queue;
  state_ = new DisarmedState;
  state_->setContext(this);
}

void MonitoringSystem::arm() {
  state_->arm();
}
void MonitoringSystem::disarm() {
  state_->disarm();
}

void MonitoringSystem::alert() {
  state_->alert();
}

void MonitoringSystem::transitionTo(MonitoringState *state) {
  if (state_ != nullptr) {
    delete state_;
  }
  state_ = state;
  state_->setContext(this);
}     

void MonitoringSystem::startTracking() {
  tracker_->startTracking();
  tracker_->publish();
}

void MonitoringSystem::setTracker(ThiefTracker *tracker) {
  if (tracker_ != nullptr) {
    delete tracker_;
  }
  tracker_ = tracker;
}

void MonitoringSystem::run() {
  while (true) {
    MonitoringMsg msg = msg_queue_->dequeue();
    switch (msg.cmd) {
      case MonitoringCmd::controlsArm:
        arm();
        break;
      case MonitoringCmd::controlsDisarm:
        disarm();
      case MonitoringCmd::sensorAlert:
        alert();
      default:
        break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate_ms_));
  }
}

void MonitoringState::setContext(MonitoringSystem *context) {
  context_ = context;
}

void ArmedState::arm() {}

void ArmedState::disarm() {
  context_->transitionTo(new DisarmedState);
}

void ArmedState::alert() {
  context_->startTracking();
}


void DisarmedState::arm() {
  context_->transitionTo(new ArmedState);
}

void DisarmedState::disarm() {}

void DisarmedState::alert() {}