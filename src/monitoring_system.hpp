#pragma once

#include <filesystem>

#include "tracker/thief_tracker.hpp"
#include "util/sensor.hpp"
#include "util/msg_queue.hpp"
#include "util/monitoring_msg.hpp"
#include "sensor_evaluator.hpp"

// ugly circular dependency?
// => is the state design pattern really a thing?
class MonitoringState;

class MonitoringSystem {
  public:
    MonitoringSystem(ThiefTracker*, MsgQueue<MonitoringMsg>*, std::filesystem::path,
        SensorEvaluator*);
    void transitionTo(MonitoringState*); 
    void run();
    void setTracker(ThiefTracker*);
    void setTracking(bool);
    bool getTracking();
    void startTracking();
    void publish();
    SensorEvaluator* getEvaluator();

  private:
    void readConfig();
    MonitoringState *state_;
    ThiefTracker *tracker_;
    MsgQueue<MonitoringMsg> *msg_queue_;
    std::filesystem::path config_path_;
    SensorEvaluator *evaluator_;
    int refresh_rate_ms_ = 500;
    std::atomic<bool> tracking_ = false;
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
    virtual void evaluate(MonitoringMsg*) = 0;
};

class ArmedState : public MonitoringState {

  public:
    void arm() override;
    void disarm() override;
    void evaluate(MonitoringMsg*) override;
};

class DisarmedState : public MonitoringState {

  public:
    void arm() override;
    void disarm() override;
    void evaluate(MonitoringMsg*) override;
};


class AlertedState: public MonitoringState {
  public:
    void arm() override;
    void disarm() override;
    void evaluate(MonitoringMsg*) override;

};