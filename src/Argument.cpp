#include "Argument.hpp"

using namespace ChronoCLI;

ArgumentCommons::ArgumentCommons(const std::string& desc, const std::string& key, const std::string& placeHolder, bool isRequired) : m_desc(desc), m_isRequired(isRequired) {
  if (!(key.empty())) {
    if (key.substr(0, 1) == "-") throw Exception("ArgInitError", "Key must not start with '-'");
    m_key = m_trim(key);
  }

  if (!(placeHolder.empty())) {
    if (placeHolder.length() > 10) throw Exception("ArgInitError", "Placeholder should have maximum of 10 characters only");
    m_placeHolder = m_trim(placeHolder);
  }
}

std::string ArgumentCommons::getDesc() const {
  return m_desc;
}

bool ArgumentCommons::isSet() const {
  return m_value.has_value();
}

bool ArgumentCommons::isRequired() const {
  return m_isRequired;
}

std::string ArgumentCommons::getPlaceHolder() const {
  if (m_placeHolder.has_value()) {
    return "<" + m_placeHolder.value() + ">";
  }
  return "";
}

bool ArgumentCommons::hasPlaceHolder() const {
  return m_placeHolder.has_value();
}

Argument::Argument(
    const std::string& key,
    const std::string& description,
    const std::string& shortKey,
    const std::string& placeHolder,
    bool isRequired,
    bool isFlag) : ArgumentCommons(description, key, placeHolder, isRequired), m_isFlag(isFlag) {
  if (shortKey != "") {
    if (shortKey.length() > 5) throw Exception("ArgInitError", "ShortKey must have maximum 5 characters");
    if (shortKey.substr(0, 1) == "-") throw Exception("ArgInitError", "Shortkey must not start with '-'");
    m_shortKey = m_trim(shortKey);
  }
}

std::string Argument::getKey() const {
  return "--" + m_key;
}

std::string Argument::getShortKey() const {
  if (m_shortKey.has_value()) {
    return "-" + m_shortKey.value();
  }
  return "";
}

bool Argument::isFlag() const {
  return m_isFlag;
}

bool Argument::hasShortKey() const {
  return m_placeHolder.has_value();
}

void Argument::setValue(const std::string& value) {
  if (value != "") {
    m_setValue(value);
  } else {
    if (m_isFlag) {
      m_setValue("1");
    }
  }
}

unsigned int Positional::getId() const {
  return m_id;
}

void Positional::setValue(const std::string& value) {
  if (value != "" || !value.empty()) {
    m_setValue(value);
  }
}