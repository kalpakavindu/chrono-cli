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
  throw ParserError::TypeConvertError(value, typeid(T).name());
}

template <typename T>
T ArgumentParser::m_get(std::map<std::string, std::string>& m, const std::string& key) {
  auto it = m.find(key);
  if (it != m.end()) return m_convert<T>(it->second);
  throw CommandError::MissingArgument(key);
}

template <typename T>
T ArgumentParser::m_getList(std::map<std::string, std::string>& m, const std::string& key, const std::string& delim) {
  auto it = m.find(key);

  if (it != m.end()) {
    std::list<T> result;
    size_t pos = it->second.find(delim);

    while (pos != std::string::npos) {
      std::string token = it->second.substr(0, pos);
      result.push_back(m_convert<T>(token));
      it->second.erase(0, pos + delim.length());
      pos = it->second.find(delim);
    }

    return result;
  }

  throw CommandError::MissingArgument(key);
}

void ArgumentParser::m_parseOption(std::map<std::string, std::string>& m, std::string& arg) {
  size_t eqPos = arg.find("=");
  if (eqPos != std::string::npos) {
    // Key value arguments
    m[arg.substr(0, eqPos)] = arg.substr(eqPos + 1);
  } else {
    // Flags
    m[arg] = "true";
  }
}

ArgumentParser::ArgumentParser(int argc, const char* argv[]) {
  m_appName = argv[0];

  int pos = 1;

  // Process global options
  while (pos < argc) {
    std::string arg = argv[pos];

    if (!arg.empty() && (arg.substr(0, 1) != "-")) {
      // First arg not starting with '-' is a command
      m_commandName = arg;
      ++pos;  // Set the cursor to the first command argument
      break;
    }

    m_parseOption(m_globalArgs, arg);
    ++pos;
  }

  // Process command options
  while (pos < argc) {
    std::string arg = argv[pos];

    if (!arg.empty() && (arg.substr(0, 1) == "-")) {
      m_parseOption(m_args, arg);
    } else {
      m_positionalArgs.push_back(argv[pos]);
    }

    ++pos;
  }
}

bool ArgumentParser::HasKey(const std::string& key) const {
  return m_args.find(key) != m_args.end();
}

bool ArgumentParser::HasGlobalKey(const std::string& key) const {
  return m_globalArgs.find(key) != m_args.end();
}

bool ArgumentParser::HasCommand() const {
  return m_commandName.has_value();
}

const std::string ArgumentParser::GetCommandName() const {
  if (m_commandName.has_value()) return m_commandName.value();

  throw ParserError::ParserError("No command were given");
}