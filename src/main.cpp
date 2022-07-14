#include <thread>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

#include "monitoring_system.hpp"
#include "endpoint/rest_server.hpp"
#include "tracker/thief_tracker_impl.hpp"

#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  
  ThiefTracker *tracker = new ThiefTrackerImpl;
  MsgQueue<MonitoringMsg> *msg_queue = new MsgQueue<MonitoringMsg>;

  MonitoringSystem *monitoring_system = new MonitoringSystem(tracker, msg_queue);
  thread thread1(&MonitoringSystem::run, monitoring_system);

  Port port(8080);
  Address addr(Ipv4::any(), port);

  cout << "address: " << addr << endl;

  RestEndpoint server(addr, msg_queue);
  server.init(2);
  server.start();

}