#include "Command.hpp"

#include <iostream>

using namespace ChronoCLI;

std::string Command::getName() const {
  return m_name;
}

std::string Command::getDesc() const {
  return m_desc;
}

bool Command::hasFlag(const std::string& key) const {
  if (m_flgArgMap.find(key) != m_flgArgMap.end()) return true;
  return false;
}

bool Command::hasOption(const std::string& key) const {
  if (m_keyArgMap.find(key) != m_keyArgMap.end()) return true;
  return false;
}

bool Command::setFlag(const std::string& id) {
  auto it = m_flgArgMap.find(id);
  if (it == m_flgArgMap.end()) return false;
  it->second->setFlag();
  return true;
}

bool Command::setOption(const std::string& key, const std::string& value) {
  auto it = m_keyArgMap.find(key);
  if (it == m_keyArgMap.end()) return false;
  it->second->setValue(value);
  return true;
}

bool Command::setPositional(const std::string& value) {
  bool vgs = false;
  for (auto& it : m_posArgVec) {
    if (it->hasValue()) continue;
    it->setValue(value);
    vgs = true;
  }
  return vgs;
}

const std::shared_ptr<FlagArgument>& Command::findFlag(const std::string& key) const {
  auto it = m_flgArgMap.find(key);
  if (it != m_flgArgMap.end()) {
    return it->second;
  }
  return nullptr;
}

const std::shared_ptr<KeywordArgument>& Command::findOption(const std::string& key) const {
  auto it = m_keyArgMap.find(key);
  if (it != m_keyArgMap.end()) {
    return it->second;
  }
  return nullptr;
}

const std::unique_ptr<PositionalArgument>& Command::getPositional(const int index) const {
  if (index < m_posArgVec.size()) return m_posArgVec.at(index);
  return nullptr;
}

void Command::RegisterArgument(std::shared_ptr<FlagArgument> arg) {
  if (!arg) return;
  if (m_flgArgMap.find(arg->getKey()) != m_flgArgMap.end()) throw Exception("ArgRegError", "Flag key " + arg->getKey() + " already registered");

  if (arg->hasShortKey()) {
    if (m_flgArgMap.find(arg->getShortKey()) != m_flgArgMap.end()) throw Exception("ArgRegError", "Flag shortkey " + arg->getShortKey() + " already registered");
  }

  m_flgArgMap.emplace(arg->getKey(), arg);
  if (arg->hasShortKey()) m_flgArgMap.emplace(arg->getShortKey(), arg);
}

void Command::RegisterArgument(std::shared_ptr<KeywordArgument> arg) {
  if (!arg) return;
  if (m_keyArgMap.find(arg->getKey()) != m_keyArgMap.end()) throw Exception("ArgRegError", "Keyword argument key " + arg->getKey() + " already registered");

  if (arg->hasShortKey()) {
    if (m_keyArgMap.find(arg->getShortKey()) != m_keyArgMap.end()) throw Exception("ArgRegError", "Keyword argument shortkey " + arg->getShortKey() + " already registered");
  }

  m_keyArgMap.emplace(arg->getKey(), arg);
  if (arg->hasShortKey()) m_keyArgMap.emplace(arg->getShortKey(), arg);
}

void Command::RegisterArgument(std::unique_ptr<PositionalArgument> arg) {
  if (!arg) return;
  for (auto& i : m_posArgVec) {
    if (i->getKey() == arg->getKey()) throw Exception("ArgRegError", "Positional argument name " + arg->getKey() + " already registered");
  }
  m_posArgVec.emplace_back(std::move(arg));
}

void Command::Help(const std::string& appname) const {
  std::cout << m_desc << "\n\nUsage:\n  ";
  if (appname != "") std::cout << appname << " ";
  std::cout << m_name << " [FLAGS] [OPTIONS] <ARGUMENTS>\n";

  if (m_flgArgMap.size() > 0) {
    std::cout << "\nAvailable flags:\n";

    for (auto& it : m_flgArgMap) {
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

  if (m_keyArgMap.size() > 0) {
    std::cout << "\nAvailable options:\n";

    for (auto& it : m_keyArgMap) {
      if (it.first.substr(1, 1) != "-") continue;  // Skip shortkeys

      std::string s = "  " + it.second->getKey();
      if (it.second->hasShortKey()) s += ", " + it.second->getShortKey();
      if (it.second->hasPlaceholder()) s += "=" + it.second->getPlaceholder();

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

  if (m_posArgVec.size() > 0) {
    std::cout << "\nAvailable arguments:\n";

    for (auto& it : m_posArgVec) {
      std::string s = "  " + it->getKey();
      if (it->hasPlaceholder()) s += " " + it->getPlaceholder();

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