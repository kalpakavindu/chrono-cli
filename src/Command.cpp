#include "Command.hpp"

#include <iostream>

using namespace ChronoCLI;

void Command::RegisterArgument(Argument& arg) {
  if (arg.HasShortKey()) {
    m_args[arg.GetKeyName() + "|" + arg.GetShortkeyName()] = &arg;
  } else {
    m_args[arg.GetKeyName()] = &arg;
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
      std::string s = "  " + it.second->GetKeyName() + ", " + it.second->GetShortkeyName();
      int i = s.size();
      while (i < 20) {
        s += " ";
        ++i;
      }
      s += it.second->IsRequired() ? " *  " : "    ";
      s += it.second->GetDescription();
      std::cout << s << "\n";
    }
  }

  if (m_positionals.size() > 0) {
    std::cout << "\nPositional arguments:\n";

    for (auto& it : m_positionals) {
      std::string s = "  " + it->GetKeyName();
      int i = s.size();
      while (i < 20) {
        s += " ";
        ++i;
      }
      s += it->IsRequired() ? " *  " : "    ";
      s += it->GetDescription();
      std::cout << s << "\n";
    }
  }

  std::cout << std::endl;
}