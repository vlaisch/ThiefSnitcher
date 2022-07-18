#pragma once

#include <string>

#include "device.hpp"
#include "enum.hpp"

enum class SensorType {
  motion,
  door,
  window,
  sound,
};

static std::unordered_map<std::string, SensorType> const sensor_type_table = {
  {"motion", SensorType::motion},
  {"door", SensorType::door},
  {"window", SensorType::window},
  {"sound", SensorType::sound},
};

const auto stringToSensorType = [](std::string str) {
  return stringToEnumVal<SensorType>(&sensor_type_table, str);
};

enum class DangerZone {
  low,
  medium,
  high,
};

static std::unordered_map<std::string, DangerZone> const danger_zone_table = {
  {"low", DangerZone::low},
  {"medium", DangerZone::medium},
  {"high", DangerZone::high},
}; 

const auto stringToDangerZone = [](std::string str) {
  return stringToEnumVal<DangerZone>(&danger_zone_table, str);
};

struct Sensor : public Device {

  public: 
    Sensor(std::string name, DangerZone dz, SensorType type, int floor) :
       Device(name), danger_zone(dz), type(type), floor(floor) {}
    DangerZone danger_zone; 
    SensorType type;
    int floor;

    bool operator==(const Sensor &other) const {
      return danger_zone == other.danger_zone
          && type == other.type
          && floor == other.floor
          && name == other.name;
    }
};


// hashing

namespace std {

  template<>
  struct hash<SensorType> {
    std::size_t operator()(const SensorType &t) const {
      return static_cast<std::size_t>(t);
    }
  };

  template<>
  struct hash<DangerZone> {
    std::size_t operator()(const DangerZone &dz) const {
      return static_cast<std::size_t>(dz);
    }
  };

  template <>
  struct hash<Sensor> {
    std::size_t operator()(const Sensor& s) const {
      using std::size_t;
      using std::hash;
      using std::string;

      return hash<DangerZone>()(s.danger_zone)
          ^ hash<SensorType>()(s.type)
          ^ hash<int>()(s.floor)
          ^ hash<string>()(s.name);
    }
  };
}
