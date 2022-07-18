#include <chrono>
#include <thread>
#include <yaml-cpp/yaml.h>
#include <future>

#include "monitoring_system.hpp"

MonitoringSystem::MonitoringSystem(ThiefTracker *tracker, MsgQueue<MonitoringMsg> *queue,
    std::filesystem::path path, SensorEvaluator *evaluator) {
  tracker_ = tracker;
  msg_queue_ = queue;
  config_path_ = path;
  evaluator_ = evaluator;
  state_ = new DisarmedState;
  state_->setContext(this);
}

void MonitoringSystem::transitionTo(MonitoringState *state) {
  if (state_ != nullptr) {
    delete state_;
  }
  state_ = state;
  state_->setContext(this);
}     

void MonitoringSystem::startTracking() {
  tracking_ = true;
  tracker_->startTracking(&tracking_);
}

void MonitoringSystem::publish() {
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
        state_->arm();
        break;
      case MonitoringCmd::controlsDisarm:
        state_->disarm();
      case MonitoringCmd::sensorPush:
        state_->evaluate(&msg);
        break;
      default:
        break;
    } 
    std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate_ms_));
  }
}

void MonitoringSystem::readConfig() {
  YAML::Node config = YAML::Load(config_path_);
  const YAML::Node& sensors = config["sensors"];
  for (YAML::const_iterator it = sensors.begin(); it != sensors.end(); it++) {
    const YAML::Node& sensor_config = *it;
    auto dz = stringToDangerZone(sensor_config["danger_zone"].as<std::string>());
    auto type = stringToSensorType(sensor_config["type"].as<std::string>());

    const Sensor sensor = {
      sensor_config["name"].as<std::string>(),
      dz,
      type,
      sensor_config["floor"].as<int>(),
    };

    evaluator_->addSensor(sensor); 
  }
}

SensorEvaluator* MonitoringSystem::getEvaluator() {
  return evaluator_;
}

void MonitoringSystem::setTracking(bool val) {
  tracking_ = val;
}

bool MonitoringSystem::getTracking() {
  return tracking_;
}

void MonitoringState::setContext(MonitoringSystem *context) {
  context_ = context;
}

void ArmedState::arm() {}

void ArmedState::disarm() {
  context_->transitionTo(new DisarmedState);
}

void ArmedState::evaluate(MonitoringMsg *msg) {
  SensorEvaluator *evaluator = context_->getEvaluator();
  evaluator->update(msg->name, msg->alert); 
  if (evaluator->evaluate()) {
    context_->startTracking();
  }
}


void DisarmedState::arm() {
  context_->transitionTo(new ArmedState);
}

void DisarmedState::disarm() {}

void DisarmedState::evaluate(MonitoringMsg *msg) {
  SensorEvaluator *evaluator = context_->getEvaluator();
  evaluator->update(msg->name, msg->alert); 
}


void AlertedState::arm() {}
void AlertedState::disarm() {
  context_->setTracking(false);
  context_->transitionTo(new DisarmedState);
}
void AlertedState::evaluate(MonitoringMsg *msg) {
  if (!context_->getTracking()) {
    context_->publish();
    context_->transitionTo(new DisarmedState);
  }
}