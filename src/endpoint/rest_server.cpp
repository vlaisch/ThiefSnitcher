#include "rest_server.hpp"
#include "controls_controller.hpp"
#include "sensor_controller.hpp"

RestEndpoint::RestEndpoint(Address addr, MsgQueue<MonitoringMsg> *msg_queue)
    : http_endpoint_(std::make_shared<Http::Endpoint>(addr)) {
  ccontroller_ = new ControlsController(msg_queue);
  scontroller_ = new SensorController(msg_queue);
}

//TODO replace threads
void RestEndpoint::init(size_t threads = 2) {
  auto options = Http::Endpoint::options()
      .threads(static_cast<int>(threads))
      .flags(Tcp::Options::ReuseAddr);

  http_endpoint_->init(options);
  setupRoutes();
}

void RestEndpoint::start() {
  http_endpoint_->setHandler(router_.handler());
  http_endpoint_->serve();
}

void RestEndpoint::setupRoutes() {
  using namespace Rest;

  Routes::Get(router_, "/controls/arm", Routes::bind(&ControlsController::arm, ccontroller_));
  Routes::Get(router_, "/controls/disarm", Routes::bind(&ControlsController::disarm, ccontroller_));

}


