#include "CommandRegistry.hpp"

#include "Exception.hpp"

using namespace ChronoCLI;

void CommandRegistry::RegisterCommand(const Command* cmd) {
  if (cmd == nullptr) return;

  m_commands[cmd->GetName()] = cmd;
}

void CommandRegistry::RegisterOption(const Argument* arg) {
  if (arg == nullptr) return;

  if (arg->IsRequired()) throw Error::RuntimeError("Required arguments cannot be registered as global options.");

  m_options[arg->GetKey()] = arg;
}

int CommandRegistry::Run(int argc, const char* argv[]) {
  // TODO: Implement command execution logic
  return 0;
}