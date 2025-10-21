#pragma once
#ifndef CHRONOCLI_COMMANDREGISTRY_HPP
#define CHRONOCLI_COMMANDREGISTRY_HPP

#include "ArgumentParser.hpp"
#include "Command.hpp"

namespace ChronoCLI {

  class CommandRegistry {
   private:
    std::map<std::string, Command*> m_cmdMap;
    ArgumentParser m_parser;
    GlobalArgRegistry m_gArgs;

   protected:
    void RegisterCommand(Command&& cmd);
    void RegisterGlobalArgument(Argument&& arg);

    virtual void Help(const std::string& appname) const;
    virtual void AppVersion() const = 0;
    virtual int GlobalExec(GlobalArgRegistry args) const { return 0; };

   public:
    CommandRegistry(int argc, const char* argv[]) : m_parser(argc, argv) {}
    void Run();
    ~CommandRegistry();
  };

}  // namespace ChronoCLI

#endif