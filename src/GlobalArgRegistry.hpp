#pragma once
#ifndef CHRONOCLI_GLOBAL_ARG_REGISTRY
#define CHRONOCLI_GLOBAL_ARG_REGISTRY

#include <map>
#include <memory>

#include "Argument.hpp"

namespace ChronoCLI {

  class GlobalArgRegistry {
   private:
    std::map<std::string, Argument*> m_argMap;

   public:
    void RegisterArg(Argument* arg);
    bool setOption(const std::string& key, const std::string& value);

    std::optional<Argument> findByKey(const std::string& key) const;
    bool hasArg(const std::string& key) const;
  };

}  // namespace ChronoCLI

#endif