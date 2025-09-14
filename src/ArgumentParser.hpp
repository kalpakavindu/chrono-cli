#ifndef CHRONOCLI_ARGUMENTPARSER_HPP
#define CHRONOCLI_ARGUMENTPARSER_HPP

#include <list>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace ChronoCLI {

  class ArgumentParser {
   private:
    std::string m_appName;
    std::optional<std::string> m_commandName;
    std::map<std::string, const std::string> m_args;
    std::vector<const std::string> m_positionalArgs;

    template <typename T>
    T m_convert(const std::string& value) const;

   public:
    ArgumentParser(int argc, const char* argv[]);

    bool HasKey(const std::string& key) const;
    bool HasCommand() const;

    template <typename T>
    T Get(const std::string& key) const;

    template <typename T>
    std::list<T> GetList(const std::string& key, const std::string& delim) const;

    const std::string& GetAppName() const;
    const std::string& GetCommandName() const;
    const std::vector<const std::string>& GetPositionalArgs() const;
  };

}  // namespace ChronoCLI

#endif