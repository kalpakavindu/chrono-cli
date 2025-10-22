#pragma once
#ifndef CHRONOCLI_COMMAND_HPP
#define CHRONOCLI_COMMAND_HPP

#include <vector>

#include "Argument.hpp"
#include "GlobalArgRegistry.hpp"

namespace ChronoCLI {

  class Command {
   private:
    std::string m_name;
    std::string m_desc;

    std::map<std::string, Argument*> m_argMap;
    std::vector<Positional*> m_posVec;

   protected:
    void RegisterArgument(Argument* arg);
    void RegisterArgument(Positional* arg);

   public:
    Command(const std::string& name, const std::string& description) : m_name(name), m_desc(description) {}

    std::string getName() const;
    std::string getDesc() const;

    bool setArgument(const std::string& key, const std::string& value = "");
    bool setPositional(unsigned int id, const std::string& value);

    virtual void Exec(const GlobalArgRegistry& globalArgs) const { return; }
    virtual void Help(const std::string& appname = "") const;

    ~Command();
  };

}  // namespace ChronoCLI

#endif