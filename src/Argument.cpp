#include "Argument.hpp"

using namespace ChronoCLI;

Argument::Argument(const std::string& key, const std::string& shortkey, bool required, const std ::string& description) : m_description(description), m_isRequired(required) {
  if ((key.substr(0, 1) == "-") || (key.substr(0, 1) == "_")) throw Exception("Invalid value for argument key");
  if (key == "help") throw Exception("Cannot use 'help' as a key for custom arguments");
  if (key.size() == 1) throw Exception("Minimum 2 characters required for argument key");
  m_key = key;

  if ((shortkey.substr(0, 1) == "-") || (shortkey.substr(0, 1) == "_")) throw Exception("Invalid value for argument short key");
  if (shortkey == "h") throw Exception("Cannot use 'h' as a short key for custom arguments");
  if (shortkey.size() > 3) throw Exception("Maximum 3 character string considered as a short key");
  if (!shortkey.empty()) m_shortkey = shortkey;
}

std::string Argument::GetKeyName() const {
  return "--" + m_key;
}

std::string Argument::GetShortkeyName() const {
  if (m_shortkey.has_value()) {
    return "-" + m_shortkey.value();
  }
  return "";
}
