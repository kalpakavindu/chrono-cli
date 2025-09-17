#include "CommandRegistry.hpp"

#include "Exception.hpp"

using namespace ChronoCLI;

void CommandRegistry::RegisterCommand(Command& cmd) {
  m_commands[cmd.GetName()] = &cmd;
}

void CommandRegistry::RegisterOption(Argument& arg) {
  if (arg.IsRequired()) throw Exception("Required arguments cannot be registered as global options.");

  m_options[arg.GetKey()] = &arg;
}

int CommandRegistry::Run(int argc, const char* argv[]) {
  // TODO: Implement command execution logic
  return 0;
}