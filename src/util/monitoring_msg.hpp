#pragma once

enum class MonitoringCmd {
  controlsArm = 0,
  controlsDisarm = 1,
  sensorAlert = 2,
};

struct MonitoringMsg {
  MonitoringCmd cmd;
};
