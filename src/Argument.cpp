#include "Argument.hpp"

using namespace ChronoCLI;

// Class: ArgumentBase

std::string ArgumentBase::getKey() const {
  return m_key;
}

std::string ArgumentBase::getDesc() const {
  return m_description;
}

bool ArgumentBase::isRequired() const {
  return m_isRequired;
}

// --------------------------

// Class: ShortKeyBase

ShortKeyBase::ShortKeyBase(const std::string& shortkey) {
  if (shortkey == "") return;
  if (shortkey.size() > 4) throw Exception("ArgDefError", "Maximum 4 characters allowed for shortkeys");
  if (m_shortkey.has_value()) throw Exception("ArgDefError", "Shortkeys can not be redefined");
  m_shortkey = shortkey;
}

std::optional<std::string> ShortKeyBase::getShortKey() const {
  std::optional<std::string> temp;
  if (m_shortkey.has_value()) {
    temp = "-" + m_shortkey.value();
  }
  return temp;
}

// --------------------------

// Class: PlaceholderBase

PlaceholderBase::PlaceholderBase(const std::string& placeholder) {
  if (placeholder == "") return;
  if (placeholder.size() > 12) throw Exception("ArgDefError", "Maximum 12 characters allowed for placeholders");
  if (m_placeholder.has_value()) throw Exception("ArgDefError", "Placeholders can not be redefined");
  m_placeholder = placeholder;
}

std::optional<std::string> PlaceholderBase::getPlaceholder() const {
  std::optional<std::string> temp;
  if (m_placeholder.has_value()) {
    temp = "<" + m_placeholder.value() + ">";
  }
  return temp;
}

// --------------------------

// Class: ValuedBase

void ValuedBase::m_setValue(const std::string& data) {
  m_value = data;
}

bool ValuedBase::hasValue() const {
  return m_value.has_value();
}

// --------------------------

// Class: FlagArgument

std::string FlagArgument::getKey() const {
  return "--" + m_key;
}

void FlagArgument::setFlag() {
  m_isset = true;
}

bool FlagArgument::isSet() const {
  return m_isset;
}

// --------------------------

// Class: KeywordArgument

std::string KeywordArgument::getKey() const {
  return "--" + m_key;
}

// --------------------------

// Class: PositionalArgument

// --------------------------