#pragma once
#ifndef CHRONOCLI_COMMAND_HPP
#define CHRONOCLI_COMMAND_HPP

#include <map>
#include <vector>

#include "Argument.hpp"
#include "GlobalArgRegistry.hpp"

namespace ChronoCLI {

  class Command {
   private:
    std::string m_name;
    std::string m_desc;

    std::map<std::string, std::shared_ptr<FlagArgument>> m_flgArgMap;
    std::map<std::string, std::shared_ptr<KeywordArgument>> m_keyArgMap;
    std::vector<std::shared_ptr<PositionalArgument>> m_posArgVec;

   protected:
    void RegisterArgument(std::shared_ptr<FlagArgument> arg);
    void RegisterArgument(std::shared_ptr<KeywordArgument> arg);
    void RegisterArgument(std::shared_ptr<PositionalArgument> arg);

   public:
    Command(const std::string& name, const std::string& description) : m_name(name), m_desc(description) {}

    static std::shared_ptr<Command> Ptr(const std::string& name, const std::string& description) {
      return std::make_shared<Command>(name, description);
    }

    std::string getName() const;
    std::string getDesc() const;

    bool hasFlag(const std::string& key) const;
    bool hasOption(const std::string& key) const;

    bool setFlag(const std::string& key);
    bool setOption(const std::string& key, const std::string& value);
    bool setPositional(const std::string& value);

    const std::shared_ptr<FlagArgument> findFlag(const std::string& key) const;
    const std::shared_ptr<KeywordArgument> findOption(const std::string& key) const;
    const std::shared_ptr<PositionalArgument> getPositional(const int index) const;

    virtual void Exec(const GlobalArgRegistry& globalArgs) const { return; }
    virtual void Help(const std::string& appname = "") const;

    virtual ~Command() = default;
  };

}  // namespace ChronoCLI

#endif