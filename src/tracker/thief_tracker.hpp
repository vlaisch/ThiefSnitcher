#pragma once

class ThiefTracker {
  public:
    virtual ~ThiefTracker() {}
    virtual void startTracking() = 0;
    virtual void publish() = 0;
};