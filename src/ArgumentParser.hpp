#pragma once
#ifndef CHRONOCLI_ARGUMENTPARSER_HPP
#define CHRONOCLI_ARGUMENTPARSER_HPP

#include <list>
#include <map>
#include <optional>
#include <vector>

#include "Exception.hpp"

namespace ChronoCLI {

  class ArgumentParser {
   private:
    std::string m_appName;
    std::optional<std::string> m_commandName;
    std::map<std::string, std::string> m_args;
    std::map<std::string, std::string> m_globalArgs;
    std::vector<std::string> m_positionalArgs;

    void m_parseOption(std::string& arg, bool isGlobal);
    std::map<std::string, std::string>& m_getTargetMap(bool isGlobal);
    std::string& m_get(const std::string& key, bool isGlobal);

   public:
    ArgumentParser(int argc, const char* argv[]);

    bool HasKey(const std::string& key) const;
    bool HasGlobalKey(const std::string& key) const;
    bool HasCommand() const;
    const std::string GetCommandName() const;

    std::string GetValue(const std::string& key) {
      return m_get(key, false);
    }

    std::string GetGlobalValue(const std::string& key) {
      return m_get(key, true);
    }

    const std::string GetAppName() const { return m_appName; }
    const std::vector<std::string> GetPositionalArgs() const { return m_positionalArgs; }
  };

}  // namespace ChronoCLI

#endif