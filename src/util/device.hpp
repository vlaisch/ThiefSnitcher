#pragma once

#include <string>

struct Device {
  public:
    Device(std::string name_arg) {
      name = name_arg;
    }
    std::string name;
};