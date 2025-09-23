#pragma once
#ifndef CHRONOCLI_COMMANDREGISTRY_HPP
#define CHRONOCLI_COMMANDREGISTRY_HPP

#include "Command.hpp"

namespace ChronoCLI {
  class CommandRegistry {
   private:
    std::map<std::string, Command*> m_commands;
    void m_Help(const std::string& appname) const;

   public:
    void RegisterCommand(Command& cmd);

    void Run(int argc, const char* argv[]);
  };

}  // namespace ChronoCLI

#endif