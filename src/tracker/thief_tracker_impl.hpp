#pragma once

#include "thief_tracker.hpp"

class ThiefTrackerImpl : public ThiefTracker {
  public:
    void startTracking(const std::atomic<bool>&) override;
    void publish() override;
};