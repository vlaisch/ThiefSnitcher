#pragma once

#include <atomic>

class ThiefTracker {
  public:
    virtual ~ThiefTracker() {}
    virtual void startTracking(const std::atomic<bool>&) = 0;
    virtual void publish() = 0;
};