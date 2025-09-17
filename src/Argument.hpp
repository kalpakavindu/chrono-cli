#pragma once
#ifndef CHRONOCLI_ARGUMENT_HPP
#define CHRONOCLI_ARGUMENT_HPP

#include <string>

namespace ChronoCLI {

  class Argument {
   protected:
    std::string m_key;
    std::string m_value;
    bool m_required;

   public:
    Argument(const std::string& key, bool required = false) : m_key(key), m_required(required) {}
    virtual bool Validate() const { return !m_value.empty(); }

    void SetValue(const std::string& value);

    const std::string& GetKey() const { return m_key; }
    const std::string& GetValue() const { return m_value; }
    bool IsRequired() const { return m_required; }
  };

}  // namespace ChronoCLI

#endif
