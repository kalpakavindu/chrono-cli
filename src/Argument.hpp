#pragma once
#ifndef CHRONOCLI_ARGUMENT_HPP
#define CHRONOCLI_ARGUMENT_HPP

#include <list>
#include <optional>

#include "Exception.hpp"

namespace ChronoCLI {

  /**
   * @class ChronoCLI::ArgumentBase
   * @brief Base class for arguments
   *
   * This class holds the core functions and properties of arguments.
   */
  class ArgumentBase {
   protected:
    std::string m_key;
    std::string m_desc;
    bool m_isRequired = false;
    std::optional<std::string> m_value;
    std::optional<std::string> m_placeHolder;
    std::optional<std::string> m_defaultValue;

    template <typename T>
    T m_convert(const std::string& value) const {
      if constexpr (std::is_same_v<T, std::string>) return value;
      if constexpr (std::is_same_v<T, int>) return std::stoi(value);
      if constexpr (std::is_same_v<T, double>) return std::stod(value);
      if constexpr (std::is_same_v<T, float>) return std::stof(value);
      if constexpr (std::is_same_v<T, bool>) return value != "" || value != "false" || value != "0";
      throw ParserError::TypeConvertError(value, typeid(T).name());
    }

    inline std::string m_trim(std::string str) {
      str.erase(0, str.find_first_not_of(" \t\n"));
      str.erase(str.find_last_not_of(" \t\n") + 1);
      return str;
    }

    void m_setValue(const std::string& value) {
      m_value = m_trim(value);
    }

   public:
    /**
     * @brief Populates the members of ArgumentBase class
     *
     * This constructor initializes all internal members with given values.
     *
     * @param desc Argument description.
     * @param key Argument key. Defaults to an empty string.
     * @param placeHolder Argument placeholder. Defaults to an empty string.
     * @param defaultValue Optional default value.
     * @param isRequired Whether the argument is required or not. Defaults to false.
     *
     * @throws ChronoCLI::Exception When given an invalid key or placeholder.
     */
    ArgumentBase(
        const std::string& desc,
        const std::string& key = "",
        const std::string& placeHolder = "",
        const std::string& defaultValue = "",
        bool isRequired = false);

    /**
     * @brief Get argument description.
     */
    std::string getDesc() const;

    /**
     * @brief Get default value
     */
    std::string getDefaultValue() const;

    /**
     * @brief Check whether the argument has default value
     */
    bool hasDefaultValue() const;

    /**
     * @brief Check whether the argument is required or not.
     */
    bool isRequired() const;

    /**
     * @brief Check whether the argument value is set or not.
     */
    bool isSet() const;

    /**
     * @brief Get argument placeholder.
     *
     * This returns an empty string if the placeholder is not given at initialization.
     */
    std::string getPlaceHolder() const;

    /**
     * @brief Check whether the argument placeholder is given or not.
     */
    bool hasPlaceHolder() const;

    /**
     * @brief Get the value of the argument.
     *
     * This returns the value of the argument after converting it's type to the given type.
     *
     * @tparam T The type of the value that need to be returned.
     * @throws ChronoCLI::CommandError::MissingArgument If the argument is required and value isn't set.
     */
    template <typename T>
    T getValue() const {
      if (m_value.has_value()) {
        return m_convert<T>(m_value.value());
      }

      if (m_defaultValue.has_value()) {
        return m_convert<T>(m_defaultValue.value());
      }

      if (m_isRequired) throw CommandError::MissingArgument(m_key);
      return m_convert<T>("");
    }

    /**
     * @brief Get the value of the argument as a std::list.
     *
     * This returns the value of the argument after splitting it to tokens by a given delimeter and converting their type to the given type.
     *
     * @tparam T The type of the std::list that need to be returned.
     *
     * @param delim Split key
     *
     * @throws ChronoCLI::CommandError::MissingArgument If the argument is required and value isn't set.
     */
    template <typename T>
    std::list<T> getList(const std::string& delim) const {
      std::list<T> temp;

      if (!m_value.has_value()) {
        if (!m_defaultValue.has_value()) {
          if (m_isRequired) throw CommandError::MissingArgument(m_key);
          return temp;
        }
      }

      std::string v = m_value.has_value() ? m_value.value() : m_defaultValue.value();
      size_t dPos = v.find(delim);

      while (dPos != std::string::npos) {
        temp.push_back(m_convert<T>(v.substr(0, dPos)));
        v.erase(0, dPos + delim.length());
        dPos = v.find(delim);
      }
      temp.push_back(m_convert<T>(v));  // Wouldn't miss the last part

      return temp;
    }
  };

  /**
   * @class ChronoCLI::Argument
   * @brief This class represents a normal argument that has a key.
   *
   * This class can be used to instantiate keyword arguments and flag arguments.
   *
   * @inherits ArgumentBase
   */
  class Argument : public ArgumentBase {
   private:
    std::optional<std::string> m_shortKey;
    bool m_isFlag = false;
    Argument(
        const std::string& key,
        const std::string& description,
        const std::string& shortKey = "",
        const std::string& placeHolder = "",
        const std::string& defaultValue = "",
        bool isRequired = false,
        bool isFlag = false);

   public:
    /**
     * @brief Factory method to create an Optional Argument instance.
     *
     * This method will return a pointer to a heap allocated instance of the `Argument` class.
     *
     * @param key Key name for the argument.
     * @param description Description for the argument.
     * @param shortKey Optional shortkey for the argument.
     * @param placeHolder Optional placeholder for the argument.
     * @param defaultValue Optional default value.
     */
    static Argument* Optional(const std::string& key, const std::string& description, const std::string& shortKey = "", const std::string& placeHolder = "", const std::string& defaultValue = "") {
      return new Argument(key, description, shortKey, placeHolder, defaultValue, false, false);
    }

    /**
     * @brief Factory method to create a Required Argument instance.
     *
     * This method will return a pointer to a heap allocated instance of the `Argument` class.
     *
     * @param key Key name for the argument.
     * @param description Description for the argument.
     * @param shortKey Optional shortkey for the argument.
     * @param placeHolder Optional placeholder for the argument.
     * @param defaultValue Optional default value.
     */
    static Argument* Required(const std::string& key, const std::string& description, const std::string& shortKey = "", const std::string& placeHolder = "", const std::string& defaultValue = "") {
      return new Argument(key, description, shortKey, placeHolder, defaultValue, true, false);
    }

    /**
     * @brief Factory method to create an Optional Flag instance.
     *
     * This method will return a pointer to a heap allocated instance of the `Argument` class.
     *
     * @param key Key name for the flag argument.
     * @param description Description for the flag argument.
     * @param shortKey Optional shortkey for the flag argument.
     */
    static Argument* Flag(const std::string& key, const std::string& description, const std::string& shortKey = "") {
      return new Argument(key, description, shortKey, "", "", false, true);
    }

    /**
     * @brief Factory method to create a Required Flag instance.
     *
     * This method will return a pointer to a heap allocated instance of the `Argument` class.
     *
     * @param key Key name for the flag argument.
     * @param description Description for the flag argument.
     * @param shortKey Optional shortkey for the flag argument.
     */
    static Argument* RequiredFlag(const std::string& key, const std::string& description, const std::string& shortKey = "") {
      return new Argument(key, description, shortKey, "", "", true, true);
    }

    /**
     * @brief Set a value to the argument.
     *
     * This method will set the passed value to the argument. Calling this without passing any value will set the argument value to `1` if it's a flag, otherwise does nothing.
     *
     * @param value The string value to be set. Defaults to an empty string.
     */
    void setValue(const std::string& value = "");

    /**
     * @brief Get the key name of the argument.
     *
     * This method will return the key name of the argument appending `--` to the start.
     * e.g. `key` -> `--key`
     */
    std::string getKey() const;

    /**
     * @brief Get the shortkey name of the argument.
     *
     * This method will return the shortkey name of the argument appending `-` to the start.
     * e.g. `k` -> `-k`
     * If shortkey not given, this returns an empty string.
     */
    std::string getShortKey() const;

    /**
     * @brief Check whether the argument has a shortkey.
     */
    bool hasShortKey() const;

    /**
     * @brief Check whether the argument is a flag argument.
     */
    bool isFlag() const;
  };

  /**
   * @class ChronoCLI::Positional
   * @brief This class represents a positional argument that doesn't have a key.
   *
   * This class can be used to instantiate positional arguments.
   *
   * @inherits ArgumentBase
   */
  class Positional : public ArgumentBase {
   private:
    unsigned int m_id;
    Positional(
        unsigned int id,
        const std::string& description,
        const std::string placeHolder,
        const std::string& defaultValue,
        bool isRequired = false) : ArgumentBase(description, "", placeHolder, defaultValue, isRequired), m_id(id) {}

   public:
    /**
     * @brief Factory method to create an Optional Positional instance.
     *
     * @param id Id for the argument.
     * @param description Description for the argument.
     * @param placeHolder Placeholder for the argument.
     * @param defaultValue Optional default value.
     */
    static Positional* Optional(unsigned int id, const std::string& description, const std::string placeHolder, const std::string& defaultValue = "") {
      return new Positional(id, description, placeHolder, defaultValue, false);
    }

    /**
     * @brief Factory method to create a Required Positional instance.
     *
     * @param id Id for the argument.
     * @param description Description for the argument.
     * @param placeHolder Placeholder for the argument.
     * @param defaultValue Optional default value.
     */
    static Positional* Required(unsigned int id, const std::string& description, const std::string placeHolder, const std::string& defaultValue = "") {
      return new Positional(id, description, placeHolder, defaultValue, true);
    }

    /**
     * @brief Set a value to the argument.
     *
     * @param value The string value to be set.
     */
    void setValue(const std::string& value);

    /**
     * @brief Get the id of the argument.
     */
    unsigned int getId() const;
  };

}  // namespace ChronoCLI

#endif