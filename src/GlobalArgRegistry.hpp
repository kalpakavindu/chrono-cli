#pragma once
#ifndef CHRONOCLI_GLOBAL_ARG_REGISTRY
#define CHRONOCLI_GLOBAL_ARG_REGISTRY

#include <map>
#include <memory>

#include "Argument.hpp"

namespace ChronoCLI {

  class GlobalArgRegistry {
   private:
    std::map<std::string, std::shared_ptr<FlagArgument>> m_flgArgMap;
    std::map<std::string, std::shared_ptr<KeywordArgument>> m_keyArgMap;

   public:
    void RegisterOption(std::shared_ptr<FlagArgument> arg);
    void RegisterOption(std::shared_ptr<KeywordArgument> arg);
    bool setOption(const std::string& key, const std::string& value);

    const std::shared_ptr<FlagArgument> findFlag(const std::string& key) const;
    const std::shared_ptr<KeywordArgument> findOption(const std::string& key) const;
    bool hasOption(const std::string& key) const;
  };

}  // namespace ChronoCLI

#endif