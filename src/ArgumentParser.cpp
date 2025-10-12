#include "ArgumentParser.hpp"

using namespace ChronoCLI;

std::string ArgumentParser::getAppName() const {
  if (m_appname.empty()) return "";
  return m_appname;
}

std::string ArgumentParser::getCommandName() const {
  if (m_cmdName.has_value()) return m_cmdName.value();
  return "";
}

bool ArgumentParser::hasCommand() const {
  return m_cmdName.has_value();
}

bool ArgumentParser::hasOption(const std::string& key) const {
  if (m_optMap.find(key) != m_optMap.end()) return true;
  return false;
}

bool ArgumentParser::hasGlobalOption(const std::string& key) const {
  if (m_gOptMap.find(key) != m_gOptMap.end()) return true;
  return false;
}

int ArgumentParser::positionalCount() const {
  return m_posVec.size();
}

std::string ArgumentParser::getPositional(int index) const {
  if (index >= m_posVec.size()) return "";
  return m_posVec[index];
}

std::string ArgumentParser::getOption(const std::string& key) const {
  auto it = m_optMap.find(key);
  if (it == m_optMap.end()) return "";
  return it->second;
}

std::string ArgumentParser::getGlobalOption(const std::string& key) const {
  auto it = m_gOptMap.find(key);
  if (it == m_gOptMap.end()) return "";
  return it->second;
}

std::map<std::string, std::string> ArgumentParser::getOptions() const {
  return m_optMap;
}

std::map<std::string, std::string> ArgumentParser::getGlobalOptions() const {
  return m_gOptMap;
}

std::vector<std::string> ArgumentParser::getPositionals() const {
  return m_posVec;
}

void ArgumentParser::m_parseOption(std::string& arg, bool isGlobal) {
  size_t eqPos = arg.find("=");
  if (eqPos == std::string::npos) {
    if (isGlobal) {
      m_gOptMap.emplace(arg, "1");
    } else {
      m_optMap.emplace(arg, "1");
    }
  } else {
    if (isGlobal) {
      m_gOptMap.emplace(arg.substr(0, eqPos), arg.substr(eqPos + 1));
    } else {
      m_optMap.emplace(arg.substr(0, eqPos), arg.substr(eqPos + 1));
    }
  }
}

ArgumentParser::ArgumentParser(int argc, const char* argv[]) {
  if (argc == 0) return;

  m_appname = argv[0];

  int stPos = 1;
  while (stPos < argc) {
    std::string token = argv[stPos];
    if (token.substr(0, 1) == "-") {
      m_parseOption(token, true);
      ++stPos;
    } else {
      m_cmdName = token;
      ++stPos;
      break;
    }
  }

  while (stPos < argc) {
    std::string token = argv[stPos];
    if (token.substr(0, 1) == "-") {
      m_parseOption(token);
    } else {
      m_posVec.push_back(token);
    }
    ++stPos;
  }
}