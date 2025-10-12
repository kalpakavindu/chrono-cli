#include "CommandRegistry.hpp"

#include <iostream>

#include "ArgumentParser.hpp"

using namespace ChronoCLI;

void CommandRegistry::Help(const std::string& appname) const {
  std::cout << "Usage:\n";
  std::cout << "  " << appname << " [COMMAND] [OPTIONS] <ARGUMENTS>\n";
  std::cout << "\nAvailable commands:\n";
  for (auto& it : m_cmdMap) {
    std::string s = "  " + it.first;
    int i = s.size();
    while (i < 15) {
      s += " ";
      ++i;
    }
    s += it.second->getDesc();
    std::cout << s << "\n";
  }

  std::cout << "\nUse --help, -h option for get this message or use it with commands to get command help.";
  std::cout << std::endl;
}

void CommandRegistry::RegisterCommand(std::shared_ptr<Command> cmd) {
  if (!cmd) return;
  if (m_cmdMap.find(cmd->getName()) != m_cmdMap.end()) throw Exception("CmdRegError", "Command " + cmd->getName() + " already registered");
  m_cmdMap.emplace(cmd->getName(), cmd);
}

void CommandRegistry::Run() {
  if (m_parser.hasGlobalOption("-h") || m_parser.hasGlobalOption("--help")) {
    Help(m_parser.getAppName());
    return;
  }

  if (m_parser.hasGlobalOption("-v") || m_parser.hasGlobalOption("--version")) {
    AppVersion();
    return;
  }

  for (auto gop : m_parser.getOptions()) {
    if (!(m_gArgs.setOption(gop.first, gop.second))) {
      throw CommandError::UnknownOption(gop.first);
    }
  }

  if (m_parser.hasCommand()) {
    auto cit = m_cmdMap.find(m_parser.getCommandName());
    if (cit == m_cmdMap.end()) throw CommandError::UnknownCommand(m_parser.getCommandName());

    if (m_parser.hasOption("-h") || m_parser.hasOption("--help")) {
      cit->second->Help(m_parser.getAppName());
      return;
    }

    for (auto op : m_parser.getOptions()) {
      if (!(cit->second->setOption(op.first, op.second))) {
        throw CommandError::UnknownOption(op.first);
      }
    }

    for (auto pos : m_parser.getPositionals()) {
      if (!(cit->second->setPositional(pos))) {
        throw CommandError::TooManyArguments();
      }
    }

    cit->second->Exec(m_gArgs);
  }
}