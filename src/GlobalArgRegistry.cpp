#include "GlobalArgRegistry.hpp"

using namespace ChronoCLI;

void GlobalArgRegistry::RegisterOption(std::shared_ptr<FlagArgument> arg) {
  if (!arg) return;
  if (arg->isRequired()) throw Exception("GArgRegError", "Global options cannot be required. " + arg->getKey() + " registration failed");
  if (m_flgArgMap.find(arg->getKey()) != m_flgArgMap.end()) throw Exception("GArgRegError", "Global flag " + arg->getKey() + " already registered");
  if (arg->hasShortKey()) {
    if (m_flgArgMap.find(arg->getShortKey()) != m_flgArgMap.end()) throw Exception("GArgRegError", "Global flag " + arg->getShortKey() + " already registered");
  }
  m_flgArgMap.emplace(arg->getKey(), arg);
  if (arg->hasShortKey()) m_flgArgMap.emplace(arg->getShortKey(), arg);
}

void GlobalArgRegistry::RegisterOption(std::shared_ptr<KeywordArgument> arg) {
  if (!arg) return;
  if (arg->isRequired()) throw Exception("GArgRegError", "Global options cannot be required. " + arg->getKey() + " registration failed");
  if (m_keyArgMap.find(arg->getKey()) != m_keyArgMap.end()) throw Exception("GArgRegError", "Global option " + arg->getKey() + " already registered");
  if (arg->hasShortKey()) {
    if (m_keyArgMap.find(arg->getShortKey()) != m_keyArgMap.end()) throw Exception("GArgRegError", "Global option " + arg->getShortKey() + " already registered");
  }
  m_keyArgMap.emplace(arg->getKey(), arg);
  if (arg->hasShortKey()) m_keyArgMap.emplace(arg->getShortKey(), arg);
}

bool GlobalArgRegistry::setOption(const std::string& key, const std::string& value) {
  auto it = m_keyArgMap.find(key);
  if (it == m_keyArgMap.end()) {
    auto fit = m_flgArgMap.find(key);
    if (fit == m_flgArgMap.end()) return false;
    fit->second->setFlag();
    return true;
  }
  it->second->setValue(value);
  return true;
}

const std::shared_ptr<FlagArgument>& GlobalArgRegistry::findFlag(const std::string& key) const {
  auto it = m_flgArgMap.find(key);
  if (it != m_flgArgMap.end()) {
    return it->second;
  }
  return nullptr;
}

const std::shared_ptr<KeywordArgument>& GlobalArgRegistry::findOption(const std::string& key) const {
  auto it = m_keyArgMap.find(key);
  if (it != m_keyArgMap.end()) {
    return it->second;
  }
  return nullptr;
}

bool GlobalArgRegistry::hasOption(const std::string& key) const {
  if (m_flgArgMap.find(key) == m_flgArgMap.end()) {
    if (m_keyArgMap.find(key) == m_keyArgMap.end()) return false;
    return true;
  }
  return true;
}