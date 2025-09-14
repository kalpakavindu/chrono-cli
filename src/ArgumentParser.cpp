#include "ArgumentParser.hpp"

#include "Exception.hpp"

using namespace ChronoCLI;

template <typename T>
T ArgumentParser::m_convert(const std::string& value) const {
  if constexpr (std::is_same_v<T, std::string>) return value;
  if constexpr (std::is_same_v<T, int>) return std::stoi(value);
  if constexpr (std::is_same_v<T, double>) return std::stod(value);
  if constexpr (std::is_same_v<T, float>) return std::stof(value);
  if constexpr (std::is_same_v<T, bool>) return value == "true" || value == "1";
  throw Error::RuntimeError(value, typeid(T).name());
}

ArgumentParser::ArgumentParser(int argc, const char* argv[]) {
  // UNDONE: Implementation of argument parsing logic
}

bool ArgumentParser::HasKey(const std::string& key) const {
  return m_args.find(key) != m_args.end();
}

bool ArgumentParser::HasCommand() const {
  return m_commandName.has_value();
}

const std::string& ArgumentParser::GetAppName() const {
  return m_appName;
}

const std::string& ArgumentParser::GetCommandName() const {
  if (m_commandName.has_value()) return m_commandName.value();

  throw Error::RuntimeError("No command were given");
}

const std::vector<const std::string>& ArgumentParser::GetPositionalArgs() const {
  return m_positionalArgs;
}

template <typename T>
T ArgumentParser::Get(const std::string& key) const {
  auto it = m_args.find(key);
  if (it != m_args.end()) return m_convert<T>(it->second);
  throw Error::MissingArgument(key);
}

template <typename T>
std::list<T> ArgumentParser::GetList(const std::string& key, const std::string& delim) const {
  auto it = m_args.find(key);

  if (it != m_args.end()) {
    std::list<T> result;
    size_t pos = it->second.find(delim);

    while (pos != std::string::npos) {
      token = it->second.substr(0, pos);
      try {
        result.push_back(m_convert<T>(token));
      } catch (ParserError::TypeConversionError& e) {
        e.print();
      }
      it.second.erase(0, pos + delim.length());
      pos = it->second.find(delim);
    }

    return result;
  }

  throw Error::MissingArgument(key);
}