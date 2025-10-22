#pragma once
#ifndef CHRONOCLI_ARGUMENT_HPP
#define CHRONOCLI_ARGUMENT_HPP

#include <list>
#include <optional>

#include "Exception.hpp"

namespace ChronoCLI {

  class ArgumentBase {
   protected:
    std::string m_key;
    std::string m_desc;
    bool m_isRequired = false;
    std::optional<std::string> m_value;
    std::optional<std::string> m_placeHolder;

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
    ArgumentBase(const std::string& desc, const std::string& key = "", const std::string& placeHolder = "", bool isRequired = false);

    std::string getDesc() const;
    bool isRequired() const;
    bool isSet() const;
    std::string getPlaceHolder() const;
    bool hasPlaceHolder() const;

    template <typename T>
    T getValue() const {
      if (!m_value.has_value()) {
        if (m_isRequired) throw CommandError::MissingArgument(m_key);
        return m_convert<T>("");
      }
      return m_convert<T>(m_value.value());
    }

    template <typename T>
    std::list<T> getList(const std::string& delim) const {
      std::list<T> temp;

      if (!m_value.has_value()) {
        if (m_isRequired) throw CommandError::MissingArgument(m_key);
        return temp;
      }

      std::string v = m_value.value();
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

  class Argument : public ArgumentBase {
   private:
    std::optional<std::string> m_shortKey;
    bool m_isFlag = false;
    Argument(const std::string& key, const std::string& description, const std::string& shortKey = "", const std::string& placeHolder = "", bool isRequired = false, bool isFlag = false);

   public:
    static Argument* Optional(const std::string& key, const std::string& description, const std::string& shortKey = "", const std::string& placeHolder = "") {
      return new Argument(key, description, shortKey, placeHolder, false, false);
    }

    static Argument* Required(const std::string& key, const std::string& description, const std::string& shortKey = "", const std::string& placeHolder = "") {
      return new Argument(key, description, shortKey, placeHolder, true, false);
    }

    static Argument* Flag(const std::string& key, const std::string& description, const std::string& shortKey = "") {
      return new Argument(key, description, shortKey, "", false, true);
    }

    static Argument* RequiredFlag(const std::string& key, const std::string& description, const std::string& shortKey = "") {
      return new Argument(key, description, shortKey, "", true, true);
    }

    void setValue(const std::string& value = "");
    std::string getKey() const;
    std::string getShortKey() const;
    bool hasShortKey() const;
    bool isFlag() const;
  };

  class Positional : public ArgumentBase {
   private:
    unsigned int m_id;

   public:
    Positional(unsigned int id, const std::string& description, const std::string placeHolder, bool isRequired = false) : ArgumentBase(description, "", placeHolder, isRequired), m_id(id) {}

    static Positional* Optional(unsigned int id, const std::string& description, const std::string placeHolder) {
      return new Positional(id, description, placeHolder, false);
    }

    static Positional* Required(unsigned int id, const std::string& description, const std::string placeHolder) {
      return new Positional(id, description, placeHolder, true);
    }

    void setValue(const std::string& value);
    unsigned int getId() const;
  };

}  // namespace ChronoCLI

#endif