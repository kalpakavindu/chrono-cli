#pragma once
#ifndef CHRONOCLI_ARGUMENT_HPP
#define CHRONOCLI_ARGUMENT_HPP

#include <list>
#include <string>

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
    std::string m_value;
    bool m_required;

   public:
    Argument(const std::string& key, bool required = false) : m_key(key), m_required(required) {}

    virtual bool Validate() const { return !m_value.empty(); }
    void SetValue(std::string& value);

    const std::string& GetKeyName() const { return m_key; }
    bool IsRequired() const { return m_required; }
    bool IsSet() const { return m_value.empty(); }

    template <typename T>
    T GetValue() {
      if (m_value.empty()) throw CommandError::MissingArgument(m_key);
      return m_convert<T>(m_value);
    }

    template <typename T>
    std::list<T> GetList(const std::string& delim) {
      if (m_value.empty()) throw CommandError::MissingArgument(m_key);

      std::list<T> l;
      std::string v = m_value;  // Make a copy so that the original value never edited
      size_t pos = v.find(delim);

      while (pos != std::string::npos) {
        std::string token = v.substr(0, pos);
        l.push_back(m_convert<T>(token));
        v.erase(0, pos + delim.length());
        pos = v.find(delim);
      }
      l.push_back(m_convert<T>(v));  // Get the last element
      return l;
    }
  };

}  // namespace ChronoCLI

#endif
