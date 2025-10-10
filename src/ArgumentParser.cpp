#include "ArgumentParser.hpp"

using namespace ChronoCLI;

std::map<std::string, std::string>& ArgumentParser::m_getTargetMap(bool isGlobal) {
  return isGlobal ? m_globalArgs : m_args;
}

void ArgumentParser::m_parseOption(std::string& arg, bool isGlobal) {
  auto& m = isGlobal ? m_globalArgs : m_args;

  size_t eqPos = arg.find("=");
  if (eqPos != std::string::npos) {
    // Key value arguments
    m[arg.substr(0, eqPos)] = arg.substr(eqPos + 1);
  } else {
    // Flags
    m[arg] = "true";
  }
}

std::string& ArgumentParser::m_get(const std::string& key, bool isGlobal) {
  std::map<std::string, std::string>::iterator it;

  std::map<std::string, std::string>& m = m_getTargetMap(isGlobal);
  size_t skpos = key.find("|");

  if (skpos != std::string::npos) {
    it = m.find(key.substr(0, skpos));
    if (it == m.end()) {
      it = m.find(key.substr(skpos + 1));
    }
  } else {
    it = m.find(key);
  }

  if (it == m.end()) throw CommandError::MissingArgument(key);
  return it->second;
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

    m_parseOption(arg, true);
    ++pos;
  }

  // Process command options
  while (pos < argc) {
    std::string arg = argv[pos];

    if (!arg.empty() && (arg.substr(0, 1) == "-")) {
      m_parseOption(arg, false);
    } else {
      m_positionalArgs.push_back(argv[pos]);
    }

    ++pos;
  }
}

bool ArgumentParser::hasKey(const std::string& key) const {
  size_t skpos = key.find("|");
  if (skpos != std::string::npos) {
    return (m_args.find(key.substr(0, skpos)) != m_args.end()) || (m_args.find(key.substr(skpos + 1)) != m_args.end());
  }
  return m_args.find(key) != m_args.end();
}

bool ArgumentParser::hasGlobalKey(const std::string& key) const {
  size_t skpos = key.find("|");
  if (skpos != std::string::npos) {
    return (m_globalArgs.find(key.substr(0, skpos)) != m_globalArgs.end()) || (m_globalArgs.find(key.substr(skpos + 1)) != m_globalArgs.end());
  }
  return m_globalArgs.find(key) != m_globalArgs.end();
}

bool ArgumentParser::hasCommand() const {
  return m_commandName.has_value();
}

const std::string ArgumentParser::getCommandName() const {
  if (m_commandName.has_value()) return m_commandName.value();
  return "";
}