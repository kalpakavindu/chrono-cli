#include "CommandRegistry.hpp"

#include "ArgumentParser.hpp"

using namespace ChronoCLI;

void CommandRegistry::RegisterCommand(Command& cmd) {
  m_commands[cmd.GetName()] = &cmd;
}

void CommandRegistry::RegisterOption(GlobalArgument& arg) {
  if (arg.HasShortKey()) {
    m_options[arg.GetKeyName() + "|" + arg.GetShortkeyName()] = &arg;
  } else {
    m_options[arg.GetKeyName()] = &arg;
  }
}

void CommandRegistry::Run(int argc, const char* argv[]) {
  ArgumentParser parser(argc, argv);  // Initialize parser

  if (parser.HasCommand()) {
    auto cit = m_commands.find(parser.GetCommandName());
    if (cit == m_commands.end()) throw CommandError::UnknownCommand(parser.GetCommandName());

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

    // Execute command
    cit->second->Exec();
  } else {
    // UNDONE: Process global arguments
  }
}