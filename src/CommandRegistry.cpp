#include "CommandRegistry.hpp"

#include "ArgumentParser.hpp"
#include "Exception.hpp"

using namespace ChronoCLI;

void CommandRegistry::RegisterCommand(Command& cmd) {
  m_commands[cmd.GetName()] = &cmd;
}

void CommandRegistry::RegisterOption(Argument& arg) {
  if (arg.IsRequired()) throw Exception("Required arguments cannot be registered as global options.");

  m_options[arg.GetKeyName()] = &arg;
}

int CommandRegistry::Run(int argc, const char* argv[]) {
  try {
    ArgumentParser parser(argc, argv);

    if (parser.HasCommand()) {
      auto cit = m_commands.find(parser.GetCommandName());
      if (cit == m_commands.end()) throw CommandError::UnknownCommand(parser.GetCommandName());

      // Populate command arguments with values
      auto& args = cit->second->GetArgs();
      for (auto& a : args) {
        if (parser.HasKey(a.first)) {
          std::string res = parser.GetValue(a.first);
          a.second->SetValue(res);
        } else {
          if (a.second->IsRequired()) throw CommandError::MissingArgument(a.first);
        }
      }

      cit->second->Exec();
    } else {
      // UNDONE: Process global arguments
    }
  } catch (Exception& e) {
    e.print();
  }
  return 0;
}