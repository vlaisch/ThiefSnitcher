#pragma once

#include "tracker/thief_tracker.hpp"
#include "util/msg_queue.hpp"
#include "util/monitoring_msg.hpp"

// ugly circular dependency?
// => is the state design pattern really a thing?
class MonitoringState;

class MonitoringSystem {
  public:
    MonitoringSystem(ThiefTracker*, MsgQueue<MonitoringMsg>*);
    void arm();
    void disarm();
    void alert();
    void transitionTo(MonitoringState*); 
    void startTracking();
    void run();
    void setTracker(ThiefTracker*);

  private:
    MonitoringState *state_;
    ThiefTracker *tracker_;
    MsgQueue<MonitoringMsg> *msg_queue_;
    int refresh_rate_ms_ = 500;
};


// circular dependency? 
class MonitoringState {

  protected:
    MonitoringSystem *context_;

  public: 
    virtual ~MonitoringState() = default;
    void setContext(MonitoringSystem*); 
    virtual void arm() = 0;
    virtual void disarm() = 0;
    virtual void alert() = 0;
};

class ArmedState : public MonitoringState {

  public:
    void arm() override;
    void disarm() override;
    void alert();
};

class DisarmedState : public MonitoringState {

  public:
    void arm() override;
    void disarm() override;
    void alert();
};
