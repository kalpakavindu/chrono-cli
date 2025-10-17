#include "GlobalArgRegistry.hpp"

using namespace ChronoCLI;

void GlobalArgRegistry::RegisterArgument(Argument* arg) {
  if (!arg) return;
  if (arg->isRequired()) throw Exception("GArgRegError", "Global options cannot be required. " + arg->getKey() + " registration failed");
  if (m_argMap.find(arg->getKey()) != m_argMap.end()) throw Exception("GArgRegError", "Global option " + arg->getKey() + " already registered");
  if (arg->hasShortKey()) {
    if (m_argMap.find(arg->getShortKey()) != m_argMap.end()) throw Exception("GArgRegError", "Global option " + arg->getShortKey() + " already registered");
  }
  m_argMap.emplace(arg->getKey(), arg);
  if (arg->hasShortKey()) m_argMap.emplace(arg->getShortKey(), arg);
}

bool GlobalArgRegistry::setOption(const std::string& key, const std::string& value) {
  auto it = m_argMap.find(key);
  if (it != m_argMap.end()) {
    it->second->setValue(value);
    return true;
  }
  return false;
}

std::optional<Argument> GlobalArgRegistry::findByKey(const std::string& key) const {
  auto it = m_argMap.find(key);
  if (it != m_argMap.end()) {
    return std::optional<Argument>(*(it->second));
  }
  return std::nullopt;
}

bool GlobalArgRegistry::hasArg(const std::string& key) const {
  if (m_argMap.find(key) != m_argMap.end()) return true;
  return false;
}