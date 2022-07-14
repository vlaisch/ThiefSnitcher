#include "thief_tracker_impl.hpp"

#include <iostream>
using namespace std;

void ThiefTrackerImpl::startTracking() {
  for (int i = 0; i < 10; i++) {
    cout << "tracking" << endl;
  }
}

void ThiefTrackerImpl::publish() {
  cout << "publish" << endl;
}