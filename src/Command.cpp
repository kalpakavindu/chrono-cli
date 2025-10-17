#include "Command.hpp"

#include <iostream>

using namespace ChronoCLI;

std::string Command::getName() const {
  return m_name;
}

std::string Command::getDesc() const {
  return m_desc;
}

bool Command::hasArgument(const std::string& key) const {
  if (m_argMap.find(key) != m_argMap.end()) return true;
  return false;
}

bool Command::setArgument(const std::string& key, const std::string& value) {
  auto it = m_argMap.find(key);
  if (it == m_argMap.end()) return false;
  it->second->setValue(value);
  return true;
}

bool Command::setPositional(unsigned int id, const std::string& value) {
  bool vgs = false;
  for (auto& it : m_posVec) {
    if (it->getId() != id) continue;
    it->setValue(value);
    vgs = true;
  }
  return vgs;
}

std::optional<Argument> Command::getArgument(const std::string& key) const {
  auto it = m_argMap.find(key);
  if (it != m_argMap.end()) {
    return std::optional<Argument>(*(it->second));
  }
  return std::nullopt;
}

std::optional<Positional> Command::getPositional(unsigned int index) const {
  if (index >= m_posVec.size()) return std::nullopt;
  return std::optional<Positional>(*(m_posVec.at(index)));
}

void Command::RegisterArgument(Argument* arg) {
  if (!arg) return;
  if (m_argMap.find(arg->getKey()) != m_argMap.end()) throw Exception("ArgRegError", "Flag key " + arg->getKey() + " already registered");

  if (arg->hasShortKey()) {
    if (m_argMap.find(arg->getShortKey()) != m_argMap.end()) throw Exception("ArgRegError", "Flag shortkey " + arg->getShortKey() + " already registered");
  }

  m_argMap.emplace(arg->getKey(), arg);
  if (arg->hasShortKey()) m_argMap.emplace(arg->getShortKey(), arg);
}

void Command::RegisterArgument(Positional* arg) {
  if (!arg) return;
  for (auto& i : m_posVec) {
    if (i->getId() == arg->getId()) throw Exception("ArgRegError", "Positional argument id " + std::to_string(arg->getId()) + " already registered");
  }
  m_posVec.emplace_back(arg);
}

void Command::Help(const std::string& appname) const {
  std::cout << m_desc << "\n\nUsage:\n  ";
  if (appname != "") std::cout << appname << " ";
  std::cout << m_name << " [FLAGS] [OPTIONS] <ARGUMENTS>\n";

  if (m_argMap.size() > 0) {
    std::cout << "\nAvailable options:\n";

    for (auto& it : m_argMap) {
      if (it.first.substr(1, 1) != "-") continue;  // Skip shortkeys

      std::string s = "  " + it.second->getKey();
      if (it.second->hasShortKey()) s += ", " + it.second->getShortKey();

      int i = s.size();
      while (i < 25) {
        s += " ";
        ++i;
      }
      s += it.second->isRequired() ? " *  " : "    ";
      s += it.second->getDesc();
      std::cout << s << "\n";
    }
  }

  if (m_posVec.size() > 0) {
    std::cout << "\nAvailable arguments:\n";

    for (auto& it : m_posVec) {
      std::string s = "  <" + it->getPlaceHolder() + ">";

      int i = s.size();
      while (i < 25) {
        s += " ";
        ++i;
      }
      s += it->isRequired() ? " *  " : "    ";
      s += it->getDesc();
      std::cout << s << "\n";
    }
  }

  std::cout << std::endl;
}