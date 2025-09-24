#include "Command.hpp"

#include <iostream>

using namespace ChronoCLI;

void Command::RegisterArgument(Argument& arg) {
  if (arg.hasShortKey()) {
    m_args[arg.getKeyName() + "|" + arg.getShortkeyName()] = &arg;
  } else {
    m_args[arg.getKeyName()] = &arg;
  }
}

void Command::RegisterArgument(PositionalArgument& arg) {
  m_positionals.push_back(&arg);
}

void Command::Help(const std::string& appname) const {
  std::cout << m_description << "\n\nUsage:\n";
  std::cout << "  " << appname << " " << m_name << " [OPTIONS] <ARGUMENTS>\n";

  if (m_args.size() > 0) {
    std::cout << "\nAvailable options:\n";

    for (auto& it : m_args) {
      std::string s = "  " + it.second->getKeyName();

      if (it.second->hasShortKey()) {
        s += ", " + it.second->getShortkeyName();
      }

      int i = s.size();
      while (i < 20) {
        s += " ";
        ++i;
      }
      s += it.second->isRequired() ? " *  " : "    ";
      s += it.second->getDescription();
      std::cout << s << "\n";
    }
  }

  if (m_positionals.size() > 0) {
    std::cout << "\nPositional arguments:\n";

    for (auto& it : m_positionals) {
      std::string s = "  " + it->getKeyName();
      int i = s.size();
      while (i < 20) {
        s += " ";
        ++i;
      }
      s += it->isRequired() ? " *  " : "    ";
      s += it->getDescription();
      std::cout << s << "\n";
    }
  }

  std::cout << std::endl;
}