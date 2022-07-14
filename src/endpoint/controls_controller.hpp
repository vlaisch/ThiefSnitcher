#pragma once

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

#include "../util/msg_queue.hpp"
#include "../util/monitoring_msg.hpp"

using namespace Pistache;

class ControlsController {
  public:
    ControlsController(MsgQueue<MonitoringMsg>*);
    void arm(const Rest::Request&, Http::ResponseWriter);
    void disarm(const Rest::Request&, Http::ResponseWriter);

  private:
    MsgQueue<MonitoringMsg> *msg_queue_; 
};