#include "CommandRegistry.hpp"

#include <iostream>

#include "ArgumentParser.hpp"

using namespace ChronoCLI;

void CommandRegistry::Help(const std::string& appname) const {
  std::cout << "Usage:\n";
  std::cout << "  " << appname << " [COMMAND] [OPTIONS] <ARGUMENTS>\n";

  std::cout << "\nAvailable options:\n";
  std::cout << "  --help,-h              " << "Get help\n";
  std::cout << "  --version,-v           " << "Get app version\n";
  if (m_gArgs.size() > 0) {
    for (auto& [k, v] : m_gArgs.getMap()) {
      if (k.substr(1, 1) != "-") continue;

      std::string s = "  " + v->getKey();
      if (v->hasShortKey()) s += "," + v->getShortKey();
      int i = s.size();
      while (i < 25) {
        s += " ";
        ++i;
      }
      s += v->getDesc();
      std::cout << s << "\n";
    }
  }

  if (m_cmdMap.size() > 0) {
    std::cout << "\nAvailable commands:\n";
    for (auto& [_, v] : m_cmdMap) {
      std::string s = "  " + v->getName();
      int i = s.size();
      while (i < 25) {
        s += " ";
        ++i;
      }
      s += v->getDesc();
      std::cout << s << "\n";
    }
  }

  std::cout << "\nUse --help, -h option with commands to get command help.";
  std::cout << std::endl;
}

void CommandRegistry::RegisterCommand(Command* cmd) {
  if (!cmd) return;
  if (m_cmdMap.find(cmd->getName()) != m_cmdMap.end()) throw Exception("CmdRegError", "Command " + cmd->getName() + " already registered");
  m_cmdMap.emplace(cmd->getName(), cmd);
}

void CommandRegistry::RegisterGlobalArgument(Argument* arg) {
  if (!arg) return;
  m_gArgs.RegisterArgument(arg);
}

void CommandRegistry::Run(int argc, const char* argv[]) {
  try {
    ArgumentParser m_parser(argc, argv);

    if (m_parser.hasGlobalOption("-h") || m_parser.hasGlobalOption("--help")) {
      Help(m_parser.getAppName());
      return;
    }

    if (m_parser.hasGlobalOption("-v") || m_parser.hasGlobalOption("--version")) {
      AppVersion();
      return;
    }

    for (auto& [gk, gv] : m_parser.getGlobalOptions()) {
      if (!(m_gArgs.setOption(gk, gv))) {
        throw CommandError::UnknownOption(gk);
      }
    }

    if (GlobalExec() != 0) return;

    if (m_parser.hasCommand()) {
      auto cit = m_cmdMap.find(m_parser.getCommandName());
      if (cit == m_cmdMap.end()) throw CommandError::UnknownCommand(m_parser.getCommandName());

      if (m_parser.hasOption("-h") || m_parser.hasOption("--help")) {
        cit->second->Help(m_parser.getAppName());
        return;
      }

      for (auto [ok, ov] : m_parser.getOptions()) {
        if (!(cit->second->setArgument(ok, ov))) {
          throw CommandError::UnknownOption(ok);
        }
      }

      auto pos = m_parser.getPositionals();
      for (int i = 0; i < pos.size(); ++i) {
        if (!(cit->second->setPositional(i, pos[i]))) {
          throw CommandError::TooManyArguments();
        }
      }

      cit->second->Exec(GlobalArgRegistry(m_gArgs));
    }
  } catch (Exception& e) {
    e.print();
  }
}

CommandRegistry::~CommandRegistry() {
  for (auto& [_, v] : m_cmdMap) {
    delete v;
  }
  m_cmdMap.clear();
}