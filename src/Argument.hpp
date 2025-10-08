#pragma once
#ifndef CHRONOCLI_ARGUMENT_HPP
#define CHRONOCLI_ARGUMENT_HPP

#include <list>
#include <memory>
#include <optional>

#include "Exception.hpp"

namespace ChronoCLI {

  class ArgumentBase {
   protected:
    std::string m_key;
    std::string m_description;
    bool m_isRequired = false;

   public:
    ArgumentBase(const std::string& key, const std::string& description, bool required = false) : m_key(key), m_description(description), m_isRequired(required) {}

    virtual std::string getKey() const;
    virtual std::string getDesc() const;
    bool isRequired() const;

    virtual ~ArgumentBase() = default;
  };

  class ShortKeyBase {
   protected:
    std::optional<std::string> m_shortkey;

   public:
    ShortKeyBase(const std::string& shortkey);
    std::string getShortKey() const;
    bool hasShortKey() const;
  };

  class PlaceholderBase {
   protected:
    std::optional<std::string> m_placeholder;

   public:
    PlaceholderBase(const std::string& placeholder);
    std::string getPlaceholder() const;
    bool hasPlaceholder() const;
  };

  class ValuedBase {
   protected:
    std::optional<std::string> m_value;

    void m_setValue(const std::string& data);

    template <typename T>
    T m_convert(const std::string& value) {
      if constexpr (std::is_same_v<T, std::string>) return value;
      if constexpr (std::is_same_v<T, int>) return std::stoi(value);
      if constexpr (std::is_same_v<T, double>) return std::stod(value);
      if constexpr (std::is_same_v<T, float>) return std::stof(value);
      if constexpr (std::is_same_v<T, bool>) return value != "" || value != "false" || value != "0";
      throw ParserError::TypeConvertError(value, typeid(T).name());
    }

   public:
    bool hasValue() const;

    template <typename T>
    T getValue() {
      if (!hasValue()) return m_convert<T>("");
      return m_convert<T>(m_value.value());
    }

    template <typename T>
    std::list<T> getList(const std::string& delim) {
      std::list<T> temp;
      if (!hasValue()) return temp;
      std::string v = m_value.value();
      size_t dPos = v.find(delim);

      while (dPos != std::string::npos) {
        temp.push_back(m_convert<T>(v.substr(0, dPos)));
        v.erase(0, dPos + delim.length());
        dPos = v.find(delim);
      }

      return temp;
    }
  };

  class FlagArgument : public ArgumentBase, public ShortKeyBase {
   private:
    bool m_isset = false;

    FlagArgument(
        const std::string& key,
        const std::string& description,
        const std::string& shortkey = "",
        bool required = false) : ArgumentBase(key, description, required),
                                 ShortKeyBase(shortkey) {}

   public:
    static std::shared_ptr<FlagArgument> Optional(const std::string& key, const std::string& description, const std::string& shortkey = "") {
      return std::make_shared<FlagArgument>(key, description, shortkey, false);
    }

    static std::shared_ptr<FlagArgument> Required(const std::string& key, const std::string& description, const std::string& shortkey = "") {
      return std::make_shared<FlagArgument>(key, description, shortkey, true);
    }

    std::string getKey() const override;
    void setFlag();
    bool isSet() const;
  };

  class PositionalArgument : public ArgumentBase, public ValuedBase, public PlaceholderBase {
   private:
    PositionalArgument(
        const std::string& key,
        const std::string& description,
        const std::string& placeholder = "",
        bool required = false) : ArgumentBase(key, description, required),
                                 PlaceholderBase(placeholder) {}

   public:
    static std::unique_ptr<PositionalArgument> Optional(const std::string& key, const std::string& description, const std::string& placeholder = "") {
      return std::make_unique<PositionalArgument>(key, description, placeholder, false);
    }

    static std::unique_ptr<PositionalArgument> Required(const std::string& key, const std::string& description, const std::string& placeholder = "") {
      return std::make_unique<PositionalArgument>(key, description, placeholder, true);
    }
  };

  class KeywordArgument : public ArgumentBase, public ValuedBase, public ShortKeyBase, public PlaceholderBase {
   private:
    KeywordArgument(
        const std::string& key,
        const std::string& description,
        const std::string& shortkey = "",
        const std::string& placeholder = "",
        bool required = false) : ArgumentBase(key, description, required),
                                 ShortKeyBase(shortkey),
                                 PlaceholderBase(placeholder) {}

   public:
    static std::shared_ptr<KeywordArgument> Optional(const std::string& key, const std::string& description, const std::string& shortkey = "", const std::string& placeholder = "") {
      return std::make_shared<KeywordArgument>(key, description, shortkey, placeholder, false);
    }

    static std::shared_ptr<KeywordArgument> Required(const std::string& key, const std::string& description, const std::string& shortkey = "", const std::string& placeholder = "") {
      return std::make_shared<KeywordArgument>(key, description, shortkey, placeholder, true);
    }

    std::string getKey() const override;
  };

}  // namespace ChronoCLI

#endif