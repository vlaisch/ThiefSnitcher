#pragma once

#include "thief_tracker.hpp"

class ThiefTrackerImpl : public ThiefTracker {
  public:
    void startTracking() override;
    void publish() override;
};