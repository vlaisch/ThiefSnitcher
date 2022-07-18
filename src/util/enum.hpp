#pragma once

#include <unordered_map>

template <typename Enum>
Enum stringToEnumVal (const std::unordered_map<std::string, Enum> *table, std::string str) {
  auto res = table->find(str);
  if (res == table->end()) {
    throw std::invalid_argument("Invalid string for convertion to enum.");
  }
  return res->second;
}
