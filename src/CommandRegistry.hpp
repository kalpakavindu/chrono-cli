#ifndef CHRONOCLI_COMMANDREGISTRY_HPP
#define CHRONOCLI_COMMANDREGISTRY_HPP

#include <map>

#include "Command.hpp"

namespace ChronoCLI {

  class CommandRegistry {
   private:
    std::map<std::string, Command*> m_commands;

   public:
    void Register(Command* cmd);

    int Run(int argc, const char* argv[]);
  };

}  // namespace ChronoCLI

#endif