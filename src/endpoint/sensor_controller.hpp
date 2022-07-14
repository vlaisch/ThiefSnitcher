#pragma once

#include "../util/msg_queue.hpp"
#include "../util/monitoring_msg.hpp"

class SensorController {
  public:
    SensorController(MsgQueue<MonitoringMsg>*);

  private:
    MsgQueue<MonitoringMsg> *msg_queue_;   
};