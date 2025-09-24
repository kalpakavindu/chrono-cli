#include "CommandRegistry.hpp"

#include <iostream>

#include "ArgumentParser.hpp"

using namespace ChronoCLI;

void CommandRegistry::m_Help(const std::string& appname) const {
  std::cout << "Usage:\n";
  std::cout << "  " << appname << " [COMMAND] [OPTIONS] <ARGUMENTS>\n";
  std::cout << "\nAvailable commands:\n";
  for (auto& it : m_commands) {
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

void CommandRegistry::RegisterCommand(Command& cmd) {
  m_commands[cmd.getName()] = &cmd;
}

void CommandRegistry::Run(int argc, const char* argv[]) {
  if (m_commands.size() == 0) throw Exception("No commands were registered");

  ArgumentParser parser(argc, argv);  // Initialize parser

  if (parser.hasGlobalKey("-h") || parser.hasGlobalKey("--help")) {
    return m_Help(parser.getAppName());
  }

  if (parser.hasCommand()) {
    auto cit = m_commands.find(parser.getCommandName());
    if (cit == m_commands.end()) throw CommandError::UnknownCommand(parser.getCommandName());

    if (parser.hasKey("-h") || parser.hasKey("--help")) {
      return cit->second->Help(parser.getAppName());
    }

    // Populate command arguments
    for (auto& a : cit->second->getArgs()) {
      if (parser.hasKey(a.first)) {
        a.second->set(parser.getValue(a.first));
      } else {
        if (a.second->isRequired()) throw CommandError::MissingArgument(a.first);
      }
    }

    // Populate positional arguments
    auto& positionals = cit->second->getPositionalArgs();
    for (int i = 0; i < positionals.size(); i++) {
      if ((parser.getPositionalArgs().size() > 0) && (positionals.size() <= parser.getPositionalArgs().size())) {
        positionals[i]->set(parser.getPositionalArgs()[i]);
      } else {
        if (positionals[i]->isRequired()) throw CommandError::MissingArgument(positionals[i]->getKeyName());
      }
    }

    cit->second->Exec();
  } else {
    throw CommandError::CommandError("UsageError", "No command specified");
  }
}