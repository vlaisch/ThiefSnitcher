#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class MsgQueue {
  public:
    void enqueue(T msg) {
      std::lock_guard<std::mutex> lock(mutex_);
      queue_.push(msg);
      cond_.notify_one();
    }

    T dequeue() {
      std::unique_lock<std::mutex> lock(mutex_);
      while (queue_.empty()) {
        // release lock
        cond_.wait(lock);
      }
      T msg = queue_.front();
      queue_.pop();
      return msg;
    }

  private:
    mutable std::mutex mutex_;
    std::queue<T> queue_;
    std::condition_variable cond_;
};
