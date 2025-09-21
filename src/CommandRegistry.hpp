#pragma once
#ifndef CHRONOCLI_COMMANDREGISTRY_HPP
#define CHRONOCLI_COMMANDREGISTRY_HPP

#include "Command.hpp"

namespace ChronoCLI {

  class CommandRegistry {
   private:
    std::map<std::string, GlobalArgument*> m_options;
    std::map<std::string, Command*> m_commands;

   public:
    void RegisterCommand(Command& cmd);
    void RegisterOption(GlobalArgument& arg);

    void Run(int argc, const char* argv[]);
  };

}  // namespace ChronoCLI

#endif