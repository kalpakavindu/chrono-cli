#include "Command.hpp"

#include <iostream>

using namespace ChronoCLI;

std::string Command::getName() {
  return m_name;
}

std::string Command::getDesc() {
  return m_desc;
}

void Command::RegisterArgument(std::shared_ptr<FlagArgument> arg) {
  if (!arg) return;
  auto it = m_flgArgMap.find(arg->getKey());
  if (it != m_flgArgMap.end()) throw Exception("ArgRegError", "Flag key " + arg->getKey() + " already registered");

  if (arg->hasShortKey()) {
    it = m_flgArgMap.find(arg->getShortKey());
    if (it != m_flgArgMap.end()) throw Exception("ArgRegError", "Flag shortkey " + arg->getShortKey() + " already registered");
  }

  m_flgArgMap.emplace(arg->getKey(), arg);
  if (arg->hasShortKey()) m_flgArgMap.emplace(arg->getShortKey(), arg);
}

void Command::RegisterArgument(std::shared_ptr<KeywordArgument> arg) {
  if (!arg) return;
  auto it = m_keyArgMap.find(arg->getKey());
  if (it != m_keyArgMap.end()) throw Exception("ArgRegError", "Keyword argument key " + arg->getKey() + " already registered");

  if (arg->hasShortKey()) {
    it = m_keyArgMap.find(arg->getShortKey());
    if (it != m_keyArgMap.end()) throw Exception("ArgRegError", "Keyword argument shortkey " + arg->getShortKey() + " already registered");
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