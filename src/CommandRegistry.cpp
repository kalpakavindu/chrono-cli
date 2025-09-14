#include "CommandRegistry.hpp"

using namespace ChronoCLI;

void CommandRegistry::Register(Command* cmd) {
  m_commands[cmd->GetName()] = cmd;
}

int CommandRegistry::Run(int argc, const char* argv[]) {
  // TODO: Implement command execution logic
  return 0;
}