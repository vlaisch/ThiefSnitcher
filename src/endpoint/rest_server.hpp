#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

#include "sensor_controller.hpp"
#include "controls_controller.hpp"
#include "../util/msg_queue.hpp"
#include "../util/monitoring_msg.hpp"

using namespace Pistache;

class RestEndpoint {
  public:
    explicit RestEndpoint(Address, MsgQueue<MonitoringMsg>*);
    void init(size_t);
    void start();

  private:
    void setupRoutes();

    std::shared_ptr<Http::Endpoint> http_endpoint_;
    Rest::Router router_;
    ControlsController *ccontroller_;
    SensorController *scontroller_;
};
