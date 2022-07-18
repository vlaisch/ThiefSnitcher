#include "rest_endpoint.hpp"

RestEndpoint::RestEndpoint(Address addr, MsgQueue<MonitoringMsg> *msg_queue)
    : http_endpoint_(std::make_shared<Http::Endpoint>(addr)) {
  msg_queue_ = msg_queue;
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

  Routes::Get(router_, "/controls/arm", Routes::bind(&RestEndpoint::arm, this));
  Routes::Get(router_, "/controls/disarm", Routes::bind(&RestEndpoint::disarm, this));

}

void RestEndpoint::arm(const Rest::Request& req, Http::ResponseWriter response) {
  MonitoringMsg msg = {MonitoringCmd::controlsArm};
  msg_queue_->enqueue(msg);
  response.send(Http::Code::Ok);
}

void RestEndpoint::disarm(const Rest::Request& req, Http::ResponseWriter response) {
  MonitoringMsg msg = {MonitoringCmd::controlsDisarm};
  msg_queue_->enqueue(msg);
  response.send(Http::Code::Ok);
}


