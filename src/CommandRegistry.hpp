#pragma once
#ifndef CHRONOCLI_COMMANDREGISTRY_HPP
#define CHRONOCLI_COMMANDREGISTRY_HPP

#include "Command.hpp"

namespace ChronoCLI {

  class CommandRegistry {
   private:
    std::map<std::string, Command*> m_cmdMap;
    GlobalArgRegistry m_gArgs;

   protected:
    void RegisterCommand(Command* cmd);
    void RegisterGlobalArgument(Argument* arg);

    virtual void Help(const std::string& appname) const;
    virtual void AppVersion() const = 0;
    virtual int GlobalExec() const { return 0; };

   public:
    void Run(int argc, const char* argv[]);
    ~CommandRegistry();
  };

}  // namespace ChronoCLI

#endif