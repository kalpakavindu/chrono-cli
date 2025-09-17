#pragma once
#ifndef CHRONOCLI_COMMAND_HPP
#define CHRONOCLI_COMMAND_HPP

#include <map>

#include "Argument.hpp"

namespace ChronoCLI {

  class Command {
   private:
    std::map<std::string, Argument*> m_args;
    std::string m_name;
    std::string m_description;

   protected:
    void RegisterArgument(Argument& arg) {
      m_args[arg.GetKey()] = &arg;
    }

   public:
    Command(const std::string& name, const std::string& description) : m_name(name), m_description(description) {}
    const std::string& GetName() const { return m_name; }
    const std::string& GetDesc() const { return m_description; }
    const std::map<std::string, Argument*>& GetArgs() { return m_args; }

    virtual void Exec() = 0;
    virtual void Help() const = 0;
  };

}  // namespace ChronoCLI

#endif