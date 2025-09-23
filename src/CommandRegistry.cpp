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
    s += it.second->GetDesc();
    std::cout << s << "\n";
  }

  std::cout << "\nUse --help, -h option for get this message or use it with commands to get command help.";
  std::cout << std::endl;
}

void CommandRegistry::RegisterCommand(Command& cmd) {
  m_commands[cmd.GetName()] = &cmd;
}

void CommandRegistry::Run(int argc, const char* argv[]) {
  if (m_commands.size() == 0) throw Exception("No commands were registered");

  ArgumentParser parser(argc, argv);  // Initialize parser

  if (parser.HasGlobalKey("-h") || parser.HasGlobalKey("--help")) {
    return m_Help(parser.GetAppName());
  }

  if (parser.HasCommand()) {
    auto cit = m_commands.find(parser.GetCommandName());
    if (cit == m_commands.end()) throw CommandError::UnknownCommand(parser.GetCommandName());

    if (parser.HasKey("-h") || parser.HasKey("--help")) {
      return cit->second->Help(parser.GetAppName());
    }

    // Populate command arguments
    for (auto& a : cit->second->GetArgs()) {
      if (parser.HasKey(a.first)) {
        a.second->Set(parser.GetValue(a.first));
      } else {
        if (a.second->IsRequired()) throw CommandError::MissingArgument(a.first);
      }
    }

    // Populate positional arguments
    auto& positionals = cit->second->GetPositionalArgs();
    for (int i = 0; i < positionals.size(); i++) {
      if ((parser.GetPositionalArgs().size() > 0) && (positionals.size() <= parser.GetPositionalArgs().size())) {
        positionals[i]->Set(parser.GetPositionalArgs()[i]);
      } else {
        if (positionals[i]->IsRequired()) throw CommandError::MissingArgument(positionals[i]->GetKeyName());
      }
    }

    cit->second->Exec();
  } else {
    throw CommandError::CommandError("UsageError", "No command specified");
  }
}