#pragma once
#ifndef CHRONOCLI_COMMANDREGISTRY_HPP
#define CHRONOCLI_COMMANDREGISTRY_HPP

#include "ArgumentParser.hpp"
#include "Command.hpp"

namespace ChronoCLI {

  class CommandRegistry {
   protected:
    std::map<std::string, Command*> m_cmdMap;
    ArgumentParser m_parser;
    GlobalArgRegistry m_gArgs;

    void RegisterCommand(Command* cmd);
    void RegisterGlobalArgument(Argument* arg);

   public:
    CommandRegistry(int argc, const char* argv[]) : m_parser(argc, argv) {}
    void Run();

    virtual void Help(const std::string& appname) const;
    virtual void AppVersion() const = 0;
    virtual bool GlobalExec(GlobalArgRegistry args) const { return false; };

    ~CommandRegistry();
  };

}  // namespace ChronoCLI

#endif