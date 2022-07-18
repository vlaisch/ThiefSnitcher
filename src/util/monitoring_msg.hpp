#pragma once

enum class MonitoringCmd {
  controlsArm,
  controlsDisarm,
  sensorPush,
};

struct MonitoringMsg {
  MonitoringCmd cmd;
  std::string name;
  bool alert;
};
