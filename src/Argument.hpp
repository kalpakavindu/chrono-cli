#pragma once
#ifndef CHRONOCLI_ARGUMENT_HPP
#define CHRONOCLI_ARGUMENT_HPP

#include <list>
#include <optional>

#include "Exception.hpp"

namespace ChronoCLI {

  class Argument {
   private:
    template <typename T>
    const T m_convert(const std::string& value) {
      if constexpr (std::is_same_v<T, std::string>) return value;
      if constexpr (std::is_same_v<T, int>) return std::stoi(value);
      if constexpr (std::is_same_v<T, double>) return std::stod(value);
      if constexpr (std::is_same_v<T, float>) return std::stof(value);
      if constexpr (std::is_same_v<T, bool>) return value == "true" || value == "1";
      throw ParserError::TypeConvertError(value, typeid(T).name());
    }

   protected:
    std::string m_key;
    std::string m_description;
    std::optional<std::string> m_shortkey;
    bool m_isRequired;
    std::string m_value;

   public:
    Argument(const std::string& key, const std::string& shortkey, bool required, const std ::string& description);

    std::string GetKeyName() const;
    std::string GetShortkeyName() const;
    std::string GetDescription() const { return m_description; }

    void Set(const std::string& value) { m_value = value; }
    bool IsSet() const { return !m_value.empty(); }
    bool IsRequired() const { return m_isRequired; }
    bool HasShortKey() const { return m_shortkey.has_value(); }

    template <typename T>
    T Get() {
      if (m_value.empty()) {
        if (m_isRequired) throw CommandError::MissingArgument(GetKeyName() + "|" + GetShortkeyName());
        return m_convert<T>("");
      }
      return m_convert<T>(m_value);
    }

    template <typename T>
    std::list<T> GetList(const std::string& delim) {
      if (m_value.empty()) {
        if (m_isRequired) throw CommandError::MissingArgument(GetKeyName() + "|" + GetShortkeyName());
        return m_convert<T>("");
      }

      std::list<T> l;
      std::string v = m_value;  // Make a copy so that the original value never edited
      size_t pos = v.find(delim);

      while (pos != std::string::npos) {
        std::string token = v.substr(0, pos);
        l.push_back(m_convert<T>(token));
        v.erase(0, pos + delim.length());
        pos = v.find(delim);
      }
      l.push_back(m_convert<T>(v));  // Append last element
      return l;
    }
  };

  class PositionalArgument : public Argument {
   private:
    std::string m_placeholder;

   public:
    PositionalArgument(const std::string& placeholder, bool required, const std::string& description) : Argument("", "", required, description), m_placeholder(placeholder) {}

    std::string GetKeyName() const { return "<" + m_placeholder + ">"; }
  };

}  // namespace ChronoCLI

#endif
