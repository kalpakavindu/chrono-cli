#pragma once
#ifndef CHRONOCLI_COMMANDREGISTRY_HPP
#define CHRONOCLI_COMMANDREGISTRY_HPP

#include "ArgumentParser.hpp"
#include "Command.hpp"

namespace ChronoCLI {

  class CommandRegistry {
   protected:
    std::map<std::string, std::shared_ptr<Command>> m_cmdMap;
    ArgumentParser m_parser;
    GlobalArgRegistry m_gArgs;

    void RegisterCommand(std::shared_ptr<Command> cmd);

   public:
    CommandRegistry(int argc, const char* argv[]) : m_parser(argc, argv) {}
    void Run();

    virtual void Help(const std::string& appname) const;
    virtual void AppVersion() const = 0;
  };

}  // namespace ChronoCLI

#endif