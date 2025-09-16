#ifndef CHRONOCLI_ARGUMENTPARSER_HPP
#define CHRONOCLI_ARGUMENTPARSER_HPP

#include <list>
#include <map>
#include <optional>
#include <string>
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

    // TODO: Upgrade type conversion logic
    template <typename T>
    const T m_convert(const std::string& value) {
      if constexpr (std::is_same_v<T, std::string>) return value;

      if constexpr (std::is_same_v<T, int>) return std::stoi(value);
      if constexpr (std::is_same_v<T, double>) return std::stod(value);
      if constexpr (std::is_same_v<T, float>) return std::stof(value);
      if constexpr (std::is_same_v<T, bool>) return value == "true" || value == "1";

      throw ParserError::TypeConvertError(value, typeid(T).name());
    }

    template <typename T>
    const T m_get(const std::string& key, bool isGlobal) {
      auto& m = m_getTargetMap(isGlobal);
      auto it = m.find(key);
      if (it == m.end()) throw CommandError::MissingArgument(key);
      return m_convert<T>(it->second);
    }

    template <typename T>
    const std::list<T> m_getList(const std::string& key, const std::string& delim, bool isGlobal) {
      auto& m = m_getTargetMap(isGlobal);
      auto it = m.find(key);
      if (it == m.end()) throw CommandError::MissingArgument(key);

      std::list<T> l;
      size_t pos = it->second.find(delim);

      while (pos != std::string::npos) {
        std::string token = it->second.substr(0, pos);
        l.push_back(m_convert<T>(token));
        it->second.erase(0, pos + delim.length());
        pos = it->second.find(delim);
      }
      l.push_back(m_convert<T>(it->second));  // Get the last element
      return l;
    }

   public:
    ArgumentParser(int argc, const char* argv[]);

    bool HasKey(const std::string& key) const;
    bool HasGlobalKey(const std::string& key) const;
    bool HasCommand() const;
    const std::string GetCommandName() const;

    template <typename T>
    const T GetKey(const std::string& key) {
      if (m_commandName.has_value()) return m_get<T>(key, false);
      throw ParserError::ParserError("No command is given for command options");
    }

    template <typename T>
    const T GetGlobalKey(const std::string& key) { return m_get<T>(key, true); }

    template <typename T>
    const std::list<T> GetList(const std::string& key, const std::string& delim) {
      return m_getList<T>(key, delim, false);
    }

    template <typename T>
    const std::list<T> GetGlobalList(const std::string& key, const std::string& delim) {
      return m_getList<T>(key, delim, true);
    }

    const std::string GetAppName() const { return m_appName; }
    const std::vector<std::string> GetPositionalArgs() const { return m_positionalArgs; }
  };

}  // namespace ChronoCLI

#endif