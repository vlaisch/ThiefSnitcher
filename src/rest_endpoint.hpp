#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

#include "util/msg_queue.hpp"
#include "util/monitoring_msg.hpp"

using namespace Pistache;

class RestEndpoint {
  public:
    explicit RestEndpoint(Address, MsgQueue<MonitoringMsg>*);
    void init(size_t);
    void start();
    void arm(const Rest::Request&, Http::ResponseWriter);
    void disarm(const Rest::Request&, Http::ResponseWriter);


  private:
    void setupRoutes();

    std::shared_ptr<Http::Endpoint> http_endpoint_;
    Rest::Router router_;
    MsgQueue<MonitoringMsg> *msg_queue_;
};
