#pragma once
#ifndef CHRONOCLI_ARGUMENT_HPP
#define CHRONOCLI_ARGUMENT_HPP

#include <list>
#include <optional>

#include "Exception.hpp"

namespace ChronoCLI {

  /**
   * @brief Represents a command line argument
   *
   * Supports type conversion to common types (string, int, double, float, bool)
   */
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
    /**
     * @brief Construct a new Argument object
     * @param key The argument key (e.g. --file)
     * @param shortKey The short argument key (e.g. -f)
     * @param required Whether the argument is required
     * @param description A brief description of the argument
     * @throws Exception if the key or shortkey are invalid
     */
    Argument(const std::string& key, const std::string& shortkey, bool required, const std ::string& description);

    /**
     * @brief Get the argument key name (e.g. --file)
     */
    std::string getKeyName() const;

    /**
     * @brief Get the argument shortkey name (e.g. -f)
     */
    std::string getShortkeyName() const;

    /**
     * @brief Get the argument description
     */
    std::string getDesc() const { return m_description; }

    /**
     * @brief Set the argument value
     * @param value The argument value as a string
     */
    void setValue(const std::string& value) { m_value = value; }

    /**
     * @brief Check if the argument has a value
     */
    bool isSet() const { return !m_value.empty(); }

    /**
     * @brief Check if the argument is required
     */
    bool isRequired() const { return m_isRequired; }

    /**
     * @brief Check if the argument has a shortkey
     */
    bool hasShortKey() const { return m_shortkey.has_value(); }

    /**
     * @brief Get the argument value converted to the specified type
     * @tparam T The target type (string, int, double, float, bool)
     * @throws CommandError::MissingArgument if the argument is required but not set
     * @throws ParserError::TypeConvertError if the conversion fails
     */
    template <typename T>
    T getValue() {
      if (m_value.empty()) {
        if (m_isRequired) throw CommandError::MissingArgument(getKeyName());
        return m_convert<T>("");
      }
      return m_convert<T>(m_value);
    }

    /**
     * @brief Get the argument value converted to a list of specified type
     * @tparam T The target type (string, int, double, float, bool)
     * @param delim The delimiter used to split the value into a list
     * @throws CommandError::MissingArgument if the argument is required but not set
     * @throws ParserError::TypeConvertError if the conversion fails
     */
    template <typename T>
    std::list<T> getList(const std::string& delim) {
      if (m_value.empty()) {
        if (m_isRequired) throw CommandError::MissingArgument(getKeyName());
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

  /**
   * @brief Represents a positional command line argument (e.g. <filename>)
   *
   * Inherits from Argument but does not use key or shortkey
   */
  class PositionalArgument : public Argument {
   private:
    std::string m_placeholder;

   public:
    /**
     * @brief Construct a new PositionalArgument object
     * @param placeholder The placeholder name (e.g. filename)
     * @param required Whether the argument is required
     * @param description A brief description of the argument
     */
    PositionalArgument(const std::string& placeholder, bool required, const std::string& description) : Argument("", "", required, description), m_placeholder(placeholder) {}

    /**
     * @brief Get the argument key name (e.g. <filename>)
     */
    std::string getKeyName() const { return "<" + m_placeholder + ">"; }
  };

}  // namespace ChronoCLI

#endif
