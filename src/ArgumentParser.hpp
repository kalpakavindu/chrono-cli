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
    std::map<std::string, std::string> m_args;
    std::map<std::string, std::string> m_globalArgs;
    std::vector<const std::string> m_positionalArgs;

    void m_parseOption(std::map<std::string, std::string>& m, std::string& arg);

    template <typename T>
    T m_convert(const std::string& value) const;

    template <typename T>
    T m_get(std::map<std::string, std::string>& m, const std::string& key);

    template <typename T>
    T m_getList(std::map<std::string, std::string>& m, const std::string& key, const std::string& delim);

   public:
    ArgumentParser(int argc, const char* argv[]);

    bool HasKey(const std::string& key) const;
    bool HasGlobalKey(const std::string& key) const;
    bool HasCommand() const;
    const std::string& GetCommandName() const;

    template <typename T>
    T GetKey(const std::string& key) const { return m_get<T>(m_args, key); }

    template <typename T>
    T GetGlobalKey(const std::string& key) const { return m_get<T>(m_globalArgs, key); };

    template <typename T>
    std::list<T> GetList(const std::string& key, const std::string& delim) const { return m_getList<T>(m_args, key, delim); }

    template <typename T>
    std::list<T> GetGlobalList(const std::string& key, const std::string& delim) const { return m_getList<T>(m_globalArgs, key, delim); }

    const std::string& GetAppName() const { return m_appName; }
    const std::vector<const std::string>& GetPositionalArgs() const { return m_positionalArgs; }
  };

}  // namespace ChronoCLI

#endif