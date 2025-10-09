#pragma once
#ifndef CHRONOCLI_COMMAND_HPP
#define CHRONOCLI_COMMAND_HPP

#include <map>
#include <vector>

#include "Argument.hpp"

namespace ChronoCLI {

  class Command {
   private:
    std::string m_name;
    std::string m_desc;

    std::map<std::string, std::shared_ptr<FlagArgument>> m_flgArgMap;
    std::map<std::string, std::shared_ptr<KeywordArgument>> m_keyArgMap;
    std::vector<std::unique_ptr<PositionalArgument>> m_posArgVec;

   public:
    Command(const std::string& name, const std::string& description) : m_name(name), m_desc(description) {}

    std::string getName();
    std::string getDesc();

    void RegisterArgument(std::shared_ptr<FlagArgument> arg);
    void RegisterArgument(std::shared_ptr<KeywordArgument> arg);
    void RegisterArgument(std::unique_ptr<PositionalArgument> arg);

    virtual void Exec() const = 0;
    virtual void Help(const std::string& appname = "") const;

    virtual ~Command() = default;
  };

}  // namespace ChronoCLI

#endif