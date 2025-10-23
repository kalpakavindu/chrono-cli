#pragma once
#ifndef CHRONOCLI_GLOBAL_ARG_REGISTRY
#define CHRONOCLI_GLOBAL_ARG_REGISTRY

#include <map>

#include "Argument.hpp"

namespace ChronoCLI {

  class GlobalArgRegistry {
   private:
    std::map<std::string, Argument*> m_argMap;

   public:
    GlobalArgRegistry() {}

    void RegisterArgument(Argument* arg);
    bool setOption(const std::string& key, const std::string& value);

    Argument* findByKey(const std::string& key) const;
    bool hasArg(const std::string& key) const;
    size_t size() const;
    std::map<std::string, Argument*> getMap() const;

    ~GlobalArgRegistry();
  };

}  // namespace ChronoCLI

#endif