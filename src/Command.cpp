#include "Command.hpp"

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