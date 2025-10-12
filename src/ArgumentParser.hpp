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
    std::string m_appname;
    std::optional<std::string> m_cmdName;
    std::map<std::string, std::string> m_optMap;
    std::map<std::string, std::string> m_gOptMap;
    std::vector<std::string> m_posVec;

    void m_parseOption(std::string& arg, bool isGlobal = false);

   public:
    ArgumentParser(int argc, const char* argv[]);

    std::string getAppName() const;
    std::string getCommandName() const;
    std::string getOption(const std::string& key) const;
    std::string getGlobalOption(const std::string& key) const;
    std::string getPositional(int index) const;

    std::map<std::string, std::string> getOptions() const;
    std::map<std::string, std::string> getGlobalOptions() const;
    std::vector<std::string> getPositionals() const;

    bool hasCommand() const;
    bool hasOption(const std::string& key) const;
    bool hasGlobalOption(const std::string& key) const;
    int positionalCount() const;
  };

}  // namespace ChronoCLI

#endif